#include "./../../src/queue/queue.h"
#include "./../assert.h"
#include "./../test.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/foreach/foreach.h"
#include "./../../src/fold/fold.h"
#include "./../../src/map/map.h"
#include <stdio.h>
#include <stdlib.h>

int queue_initWorks()
{
    int queueCap = 10;
    Queue* queue = queue_init(queueCap);
    int assertions = 
        assertIntEquals(queueCap, queue_capacity(queue))
        &&
        assertIntEquals(0, queue_size(queue));
    queue_destroy(queue);
    return assertions;
}

int queue_destroyWorks()
{
    int queueCap = 10;
    Queue* queue = queue_init(queueCap);
    queue_destroy(queue);
    return assertIntEquals(0, queue_capacity(queue));
}

int queue_addPollTest()
{
    int queueCap = 5;
    Queue* queue = queue_init(queueCap);
    int val = 10;
    queue_add(queue, di32(val));
    Option opt = queue_poll(queue);
    queue_destroy(queue);
    return
        assertTrue("opt.type == SOME", opt.type == SOME)
        &&
        assertIntEquals(val, i32(opt.value));
}

Dynamic squareInts(Dynamic intDyn)
{
    return di32(i32(intDyn) * i32(intDyn));
}

int queue_mapToSquares()
{
    Queue* queue = queue_init(3);
    queue_add(queue, di32(1));
    queue_add(queue, di32(2));
    queue_add(queue, di32(3));
    Queue* squaredqueue = queue_map(queue, squareInts);
    queue_destroy(queue);
    int one = i32(queue_poll(squaredqueue).value);
    int four = i32(queue_poll(squaredqueue).value);
    int nine = i32(queue_poll(squaredqueue).value);
    return
        assertIntEquals(1, one)
        &&
        assertIntEquals(4, four)
        &&
        assertIntEquals(9, nine);
}

Dynamic sumInts(Dynamic acc, Dynamic intDyn)
{
    return di32(i32(acc) + i32(intDyn));
}

int queue_foldToSquaredSum()
{
    Queue* queue = queue_init(10);
    int i;
    for(i = 0; i < 10; i++)
    {
        queue_add(queue, di32(i + 1));
    }
    Queue* squaredqueue = queue_map(queue, squareInts);
    queue_destroy(queue);
    int expectedSum = 385;
    Dynamic sum = di32(0);
    sum = queue_fold(squaredqueue, sum, sumInts);
    return assertIntEquals(expectedSum, i32(sum));
}

int queue_resizingWorks()
{
    Queue* queue = queue_init(1);
    

    queue_add(queue, di32(1));
    queue_add(queue, di32(2));
    queue_add(queue, di32(500));
    queue_add(queue, di32(52));

    int queueSizeCorrect = assertIntEquals(4, queue_size(queue));

    queue_poll(queue);
    queue_poll(queue);
    queue_poll(queue);
    queue_poll(queue);
    return queueSizeCorrect && assertIntEquals(0, queue_size(queue));
}

void printdi32(Dynamic d)
{
    printf("%d\n", i32(d));
}

Dynamic add(Dynamic a, Dynamic d)
{
    return (di32(i32(a) + i32(d)));
}

int queue_iteratorWorks()
{
    Queue* queue = queue_init(5);
    queue_add(queue, di32(1));
    queue_add(queue, di32(1));
    queue_add(queue, di32(1));
    queue_add(queue, di32(1));
    queue_add(queue, di32(1));
    Iterator* it = queue_iterator(queue);
    foreach(it, printdi32);
    Dynamic sum;
    sum = fold(it, di32(0), add);
    return assertIntEquals(5, i32(sum));
}

int main()
{
    test_declareAndRun("queue with ints initializes properly", queue_initWorks);
    test_declareAndRun("queue with 10 capacity has 0 after being destroyed", queue_destroyWorks);
    test_declareAndRun("Pushing the int 10 onto queue and then popping returns Option of Some(10)", queue_addPollTest);
    test_declareAndRun("Queue maps integers to their squares correctly", queue_mapToSquares);
    test_declareAndRun("Queue maps integers to squares and sums them using fold, works correctly", queue_foldToSquaredSum);
    test_declareAndRun("Iterator from queue works as intended", queue_iteratorWorks);
    test_declareAndRun("Queue grows when values are added", queue_resizingWorks);
    return 0;
}