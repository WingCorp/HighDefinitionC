#include "./../../src/stack/stack.h"
#include "./../assert.h"
#include "./../test.h"
#include "./../../src/primitive/primitive.h"
#include <stdio.h>
#include <ctype.h>

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
    stack_push(stack, pi32(val));
    Option opt = stack_pop(stack);
    stack_destroy(stack);
    return
        assertTrue("opt.type == SOME", opt.type == SOME)
        &&
        assertIntEquals(val, i32(opt.value));
}

Primitive squareInts(Primitive intPrim)
{
    return pi32(i32(intPrim) * i32(intPrim));
}

int stack_mapToSquares()
{
    Stack* stack = stack_init(3);
    stack_push(stack, pi32(1));
    stack_push(stack, pi32(2));
    stack_push(stack, pi32(3));
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

Primitive sumInts(Primitive acc, Primitive intPrim)
{
    return pi32(i32(acc) + i32(intPrim));
}

int stack_foldToSquaredSum()
{
    Stack* stack = stack_init(10);
    int i;
    for(i = 0; i < 10; i++)
    {
        stack_push(stack, pi32(i + 1));
    }
    Stack* squaredStack = stack_map(stack, squareInts);
    stack_destroy(stack);
    int expectedSum = 385;
    Primitive sum = pi32(0);
    sum = stack_fold(squaredStack, sum, sumInts);
    return assertIntEquals(expectedSum, i32(sum));
}

Primitive convertStringsToF(Primitive stringsRef)
{
    void* sRef = ref(stringsRef);
    char** strings = *((char***) (sRef));
    strings[0] = "f";
    strings[1] = "f";
    return pref(&strings);
}

int stack_mapStrings()
{
    Stack* stack = stack_init(1);
    
    char* stringsA[2];
    stringsA[0] = "WassUP";
    stringsA[1] = "wassup";
    
    char* stringsB[2];
    stringsB[0] = "ABCD";
    stringsB[1] = "abcd";

    Primitive stringsARef = pref(&stringsA);
    Primitive stringsBRef = pref(&stringsB);

    stack_push(stack, stringsARef);
    stack_push(stack, stringsBRef);

    Stack* mappedStack = stack_map(stack, convertStringsToF);
    stack_destroy(stack);
    char** bStrings = *((char***) ref(stack_pop(mappedStack).value));
    char* f = bStrings[0];
    return assertStringEquals("f", f);
}

int main()
{
    test_declareAndRun("Stack with ints initializes properly", stack_initWorks);
    test_declareAndRun("Stack with 10 capacity has 0 after being destroyed", stack_destroyWorks);
    test_declareAndRun("Pushing the int 10 onto stack and then popping returns Option of Some(10)", stack_pushPopTest);
    test_declareAndRun("Stack maps integers to their squares correctly", stack_mapToSquares);
    test_declareAndRun("Stack maps integers to squares and sums them using fold, works correctly", stack_foldToSquaredSum);
    // test_declareAndRun("Stack with advanced datatype can still map", stack_mapStrings); TODO: FIX THIS.
    return 1;
}