#include "./../../src/stack/stack.h"
#include "./../assert.h"
#include "./../test.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/foreach/foreach.h"
#include "./../../src/fold/fold.h"
#include "./../../src/map/map.h"
#include <stdio.h>
#include <stdlib.h>

int stack_initWorks()
{
    int stackCap = 10;
    Stack* stack = stack_init(stackCap);
    int assertions = 
        assertIntEquals(stackCap, stack_capacity(stack))
        &&
        assertIntEquals(0, stack_size(stack));
    stack_destroy(stack);
    return assertions;
}

int stack_destroyWorks()
{
    int stackCap = 10;
    Stack* stack = stack_init(stackCap);
    stack_destroy(stack);
    return assertIntEquals(0, stack_capacity(stack));
}

int stack_pushPopTest()
{
    int stackCap = 5;
    Stack* stack = stack_init(stackCap);
    int val = 10;
    stack_push(stack, di32(val));
    Option opt = stack_pop(stack);
    stack_destroy(stack);
    return
        assertTrue("opt.type == SOME", opt.type == SOME)
        &&
        assertIntEquals(val, i32(opt.value));
}

Dynamic squareInts(Dynamic intDyn)
{
    return di32(i32(intDyn) * i32(intDyn));
}

int stack_mapToSquares()
{
    Stack* stack = stack_init(3);
    stack_push(stack, di32(1));
    stack_push(stack, di32(2));
    stack_push(stack, di32(3));
    Stack* squaredStack = stack_map(stack, squareInts);
    stack_destroy(stack);
    int nine = i32(stack_pop(squaredStack).value);
    int four = i32(stack_pop(squaredStack).value);
    int one = i32(stack_pop(squaredStack).value);
    return
        assertIntEquals(9, nine)
        &&
        assertIntEquals(4, four)
        &&
        assertIntEquals(1, one);
}

Dynamic sumInts(Dynamic acc, Dynamic intDyn)
{
    return di32(i32(acc) + i32(intDyn));
}

int stack_foldToSquaredSum()
{
    Stack* stack = stack_init(10);
    int i;
    for(i = 0; i < 10; i++)
    {
        stack_push(stack, di32(i + 1));
    }
    Stack* squaredStack = stack_map(stack, squareInts);
    stack_destroy(stack);
    int expectedSum = 385;
    Dynamic sum = di32(0);
    sum = stack_fold(squaredStack, sum, sumInts);
    return assertIntEquals(expectedSum, i32(sum));
}

int stack_resizingWorks()
{
    Stack* stack = stack_init(1);

    stack_push(stack, di32(1));
    stack_push(stack, di32(2));
    stack_push(stack, di32(500));
    stack_push(stack, di32(52));

    int stackSizeCorrect = assertIntEquals(4, stack_size(stack));

    stack_pop(stack);
    stack_pop(stack);
    stack_pop(stack);
    stack_pop(stack);
    return stackSizeCorrect && assertIntEquals(0, stack_size(stack));
}

void printdi32(Dynamic d)
{
    printf("%d\n", i32(d));
}

Dynamic add(Dynamic a, Dynamic d)
{
    return (di32(i32(a) + i32(d)));
}

int stack_iteratorWorks()
{
    Stack* stack = stack_init(5);
    stack_push(stack, di32(1));
    stack_push(stack, di32(1));
    stack_push(stack, di32(1));
    stack_push(stack, di32(1));
    stack_push(stack, di32(1));
    Iterator* it = stack_iterator(stack);
    foreach(it, printdi32);
    Dynamic sum;
    sum = fold(it, di32(0), add);
    return assertIntEquals(5, i32(sum));
}

int main()
{
    test_declareAndRun("Stack with ints initializes properly", stack_initWorks);
    test_declareAndRun("Stack with 10 capacity has 0 after being destroyed", stack_destroyWorks);
    test_declareAndRun("Pushing the int 10 onto stack and then popping returns Option of Some(10)", stack_pushPopTest);
    test_declareAndRun("Stack maps integers to their squares correctly", stack_mapToSquares);
    test_declareAndRun("Stack maps integers to squares and sums them using fold, works correctly", stack_foldToSquaredSum);
    test_declareAndRun("Iterator from stack works as intended", stack_iteratorWorks);
    test_declareAndRun("Stack grows when values are added", stack_resizingWorks);
    return 0;
}