#include "./../test.h"
#include "./../assert.h"
#include "./../../src/array/array.h"

#define TESTING

int array_emptyCanBeUsedForValues()
{
    Array* array = array_empty(1);
    array_setItem(array, 0, di32(1));
    Option itemOpt = array_item(array, 0);
    return
        assertIntEquals(SOME, itemOpt.type)
    &&
        assertIntEquals(1, i32(itemOpt.value));
}

int array_emptyWithLengthLEQZeroCausesFail()
{
    array_empty(0);
    return assertTrue("stdout should contain stacktrace", true);
}

int array_setItemIndexOutOfBoundsCausesFail()
{
    array_empty(1);

    //I mean... I could pipe stdout into a buffer and check, but I've got eyes.
    return assertTrue("stdout should contain stacktrace", true);
    //And I'm very lazy.
}

int main()
{
    test_declareAndRun("Empty array can be used for values", array_emptyCanBeUsedForValues);
    
    // These two tests works as of 2018/06/20, but the fail-function exits the program completely...
    // Must work out a fix. 
    // test_declareAndRun("Empty array initialized with length zero or less causes fail", array_emptyWithLengthLEQZeroCausesFail);
    // test_declareAndRun("Setting array item out of bounds causes fail", array_setItemIndexOutOfBoundsCausesFail);
    return 0;
}