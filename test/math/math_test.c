#include "./../../src/math/math.h"
#include "./../assert.h"
#include "./../test.h"

int math_intAbs_test()
{
    int expected = 1;
    int testValue = -1;
    int actual;
    actual = math_intAbs(testValue);
    return assertIntEquals(expected, actual);
}

int main() 
{
    test_declareAndRun("Math abs given negative integer returns positive.", math_intAbs_test);
}
