#include "task.h"
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>

#include "./../dynamic/dynamic.h"
#include "./../queue/queue.h"
#include "./../list/list.h"
#include "./../dictionary/dictionary.h"
#include "./../lambda/lambda.h"


Queue **queues;
int n_queues = -1;
pthread_t *threads;
pthread_mutex_t *queue_locks;
bool *should_execute;

void lockAllQueues()
{
    int i;
    for (i = 0; i < n_queues; i++)
    {
        pthread_mutex_lock(&queue_locks[i]);
    }
}

void unlockAllQueues()
{
    int i;
    for (i = 0; i < n_queues; i++)
    {
        pthread_mutex_unlock(&queue_locks[i]);
    }
}

int minQueue()
{
    int min = INT_MAX;
    int minQ = -1;
    int i;
    for (i = 0; i < n_queues; i++)
    {
        int size = queue_size(queues[i]);
        printf("minQueue: queue_size(queues[%d]) returned %d\n", i, size);
        if (size == 0)
        {
            printf("minQ returning %d\n", i);
            return i;
        }
        if (size < min)
        {
            min = size;
            minQ = i;
        }
    }
    if (minQ == -1)
    {
        failwith("Could not determine minimum queue, make sure queues are initialized.");
    }
    // printf("minQ returning %d\n", minQ);
    return minQ;
}

int maxQueue()
{
    int max = INT_MIN;
    int maxQ = -1;
    int i;
    for (i = 0; i < n_queues; i++)
    {
        int size = queue_size(queues[i]);
        if (size == 0)
        {
            return i;
        }        
        if (size > max)
        {
            max = size;
            maxQ = i;
        }
    }
    if (maxQ == -1)
    {
        failwith("Could not determine maximum queue, make sure queues are initialized.");
    }
    return maxQ;
}

typedef enum _TaskType
{
    OPERATION,
    LAMBDA
} TaskType;

typedef struct _Task
{
    TaskType type;
    Lambda* lambda;
    List* arguments;
    Dynamic (*operation)();
    Dynamic *result;
    pthread_mutex_t *mutex;
    bool completed;
} Task;

void enqueue(Task* t) {
    // printf("initializing task mutex\n");
    pthread_mutex_init(t->mutex, NULL);
    pthread_mutex_lock(t->mutex);
    // printf("finding min queue\n");
    int minQ = minQueue();
    // printf("locking task mutex queue\n");
    queue_add(queues[minQ], dref(t));
    pthread_mutex_unlock(&queue_locks[minQ]);
    printf("enqueued a new task!\n");
}

Task* asynco(Dynamic (*operation)())
{
    Task* t = malloc(sizeof(Task));
    t->type = OPERATION;
    t->mutex = malloc(sizeof(pthread_mutex_t));
    t->operation = operation;
    t->completed = false;
    enqueue(t);
    return t;
}

Task* asyncl(Lambda* lambda, List* arguments)
{
    Task* t = malloc(sizeof(Task));
    t->type = LAMBDA;
    t->mutex = malloc(sizeof(pthread_mutex_t));
    t->lambda = lambda;
    t->arguments = arguments;
    t->completed = false;
    enqueue(t);
    return t;
}

void executeTask(Task* task)
{
    if (!task->completed)
    {
        Dynamic result;
        switch (task->type)
        {
        case OPERATION:
            result = task->operation();
            break;
        case LAMBDA:
            result = invoke(task->lambda, task->arguments);
            break;
        default:
            failwith("Unmatched Task type\n");
            break;
        }
        Dynamic *result_ptr = malloc(sizeof(Dynamic));
        result_ptr->type = result.type;
        result_ptr->value = result.value;
        task->result = result_ptr;
        task->completed = true;
        pthread_mutex_unlock(task->mutex);
    }
}

void *execute(void *threadid)
{
    pthread_t tid;
    tid = (pthread_t) threadid;
    pthread_mutex_t *own_lock = &queue_locks[tid];
    printf("[%ld]: thread started.\n", tid);
    while (true)
    {
        if (should_execute[tid])
        {
            //waits until something is put into the queue.
            // printf("[%ld]: peeking own queue...\n", tid);
            Dynamic opt = queue_peek(queues[tid]);
            if (isSome(opt))
            {
                printf("[%ld]: found task in own queue!\n", tid);
                //Something is in our queue, we should try locking it and polling.
                pthread_mutex_lock(own_lock);
                opt = queue_poll(queues[tid]);
                if (isNone(opt))
                {
                    printf("[%ld]: someone stole my task! :(\n", tid);
                    pthread_mutex_unlock(own_lock);
                    continue;
                }
                printf("[%ld]: executing task from own queue...\n", tid);
                Dynamic d = coerce(opt);
                Task *task = (Task *)ref(d);
                executeTask(task);
                //Task executed, unlock the queue.
                pthread_mutex_unlock(own_lock);
                continue;
            }
            // printf("[%ld]: own queue empty, trying to steal...\n", tid);
            //Own queue is empty, see if we can steal from another queue.
            int maxQ;
            int acquired;
            do
            {
                maxQ = maxQueue();
                acquired = pthread_mutex_trylock(&queue_locks[maxQ]);
            } while (acquired != 0);
            // printf("[%ld]: attempting to steal from %d's queue...\n", tid, maxQ);
            // We should now be the sole owner of the lock of the maxQ.
            // Now, we should quickly try to poll a task from the queue and execute it.
            opt = queue_poll(queues[maxQ]);
            if (isSome(opt))
            {
                printf("[%ld]: stole task from %d's qeuue!\n", tid, maxQ);
                Dynamic d = coerce(opt);
                Task *task = (Task *)ref(d);
                executeTask(task);
            }
            // Whether there was something in the queue or not, it's time to let go of it
            // and return to checking our own queue.
            pthread_mutex_unlock(&queue_locks[maxQ]);
        }
        else
        {
            printf("[%ld]: thread stopped.\n", tid);
            pthread_exit(EXIT_SUCCESS);
            return NULL;
        }
    }
    printf("[%ld]: thread stopped.\n", tid);
    pthread_exit(EXIT_SUCCESS);
    return NULL;
}

void task_enable(int parallelism)
{
    printf("Enabling task-based asynchronous execution...\n");
    if (parallelism < 1)
    {
        failwith("Cannot setup tasks with parallelism less than 1\n");
    }
    //Setup queues.
    queues = malloc(sizeof(Queue *) * parallelism);

    n_queues = parallelism;
    int i;
    for (i = 0; i < n_queues; i++)
    {
        queues[i] = queue_init(100);
    }

    //Setup threads, one for each queue.
    threads = malloc(sizeof(pthread_t *) * parallelism);
    queue_locks = malloc(sizeof(pthread_mutex_t) * parallelism);
    should_execute = malloc(sizeof(bool) * parallelism);

    for (i = 0; i < n_queues; i++)
    {

        should_execute[i] = true;
        int mutex_rc = pthread_mutex_init(&queue_locks[i], NULL);
        if (mutex_rc != 0)
        {
            failwithf("(145) task.c Could not initialize pthread_mutex for queue lock %d\n", i);
        }

        threads[i] = (pthread_t) i;

        int thread_rc = pthread_create(&threads[i], NULL, execute, (void*)threads[i]);
        int detach_rc = pthread_detach(threads[i]);
        if (thread_rc != 0)
        {
            failwithf("(152) task.c: Could not create posix thread %d\n", i);
        }
        if (detach_rc != 0)
        {
            failwithf("(153) task.c: Could not detach posix thread %d.\n", i);
        }
    }
    printf("Success!\n");
}

void task_disable()
{
    printf("Disabling task based execution...\n");
    int i;
    for (i = 0; i < n_queues; i++)
    {
        should_execute[i] = false;
    }
    sleep(2);
    for (i = 0; i < n_queues; i++)
    {
        int acquired = pthread_mutex_lock(&queue_locks[i]);
        if (acquired != 0) {
            failwithf("Could not acquire mutex lock for queue %d\n", acquired);
        }
        queue_destroy(queues[i]);
        pthread_mutex_destroy(&queue_locks[i]);
    }
    printf("Success!\n");
}



Dynamic await(Task* task)
{
    pthread_mutex_lock(task->mutex);
    return *(task->result);
}
