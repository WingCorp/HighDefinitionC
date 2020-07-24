#include "queue.h"
#include "./../stack/stack.h"

#include <stdlib.h>

typedef struct _Queue
{
    Stack* left;
    Stack* right;
} Queue;

Queue* queue_init(int initialCap)
{
    Queue* q = malloc(sizeof(Queue));
    q->left = stack_init(initialCap);
    q->right = stack_init(initialCap);
    return q;
}

void queue_destroy(Queue* queue)
{
    stack_destroy(queue->left);
    stack_destroy(queue->right);
    free(queue);
}

void queue_add(Queue* queue, Dynamic dyn)
{
    stack_push(queue->left, dyn);
}

void migrate(Queue* queue)
{
    if (stack_size(queue->right) == 0)
    {
        while (stack_size(queue->left) > 0)
        {
            //Coercing is fine here, since we check if the stack is not empty.
            stack_push(queue->right, coerce(stack_pop(queue->left)));
        }
    }
}

Dynamic queue_poll(Queue* queue)
{
    migrate(queue);
    return stack_pop(queue->right);
}

Dynamic queue_peek(Queue* queue)
{
    migrate(queue);
    return stack_peek(queue->right);
}

int queue_size(Queue* queue)
{
    return stack_size(queue->left) + stack_size(queue->right);
}

int queue_capacity(Queue* queue)
{
    return stack_capacity(queue->left) + stack_capacity(queue->right);
}

Iterator* queue_iterator(Queue* queue)
{
    migrate(queue);
    return stack_iterator(queue->right);
}

Queue* queue_map(Queue* queue, Dynamic (*mapper)(Dynamic))
{
    migrate(queue);
    Stack* mappedRight = stack_map(queue->right, mapper);
    Queue* mapped = malloc(sizeof(Queue));
    mapped->left = stack_init(stack_size(mappedRight));
    mapped->right = mappedRight;
    return mapped;
}

Dynamic queue_fold(Queue* queue, Dynamic state, Dynamic (*folder)(Dynamic, Dynamic))
{
    migrate(queue);
    return stack_fold(queue->right, state, folder);
}
