#include "./../test.h"
#include "./../assert.h"
#include "./../../src/array/array.h"
#include <stdio.h>
#include <string.h>

int array_emptyCanBeUsedForValues()
{
    Array* array = array_empty(1);
    array_setItem(array, 0, di32(1));
    Dynamic itemOpt = array_tryItem(array, 0);
    return
        assertIntEquals(SOME, itemOpt.type)
    &&
        assertIntEquals(1, i32(coerce(itemOpt)));
}


/* Test: Initialize array with length of zero. */
void array_emptyWithLengthLEQZero()
{
    array_empty(0);
}

int assertStdOutContains_array_empty(char* stackTrace)
{
    return assertStringContains(stackTrace, "array_empty") && assertStringContains(stackTrace, "Cannot initialize array of length <= 0!");
}

int array_emptyWithLengthLEQZeroCausesFail()
{
    return test_runInSubProcess(array_emptyWithLengthLEQZero, assertStdOutContains_array_empty);
}
/* --- */


/* Test: setItem in array outside of bounds */
void array_setItemIndexOutOfBounds()
{
    Array* array = array_empty(1);
    array_setItem(array, -1, di32(500));
}

int assertStdOUtContains_array_setItem(char* stackTrace)
{
    return assertStringContains(stackTrace, "array_setItem");
}

int array_setItemIndexOutOfBoundsCausesFail()
{
    return test_runInSubProcess(array_setItemIndexOutOfBounds, assertStdOUtContains_array_setItem);
}

/* --- */

int main()
{
    test_declareAndRun("Empty array can be used for values", array_emptyCanBeUsedForValues);
    test_declareAndRun("Empty array initialized with length zero or less causes fail", array_emptyWithLengthLEQZeroCausesFail);
    test_declareAndRun("Setting array item out of bounds causes fail", array_setItemIndexOutOfBoundsCausesFail);
    return 0;
}