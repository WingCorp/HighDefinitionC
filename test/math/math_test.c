#include "./../../src/math/math.h"
#include "./../assert.h"
#include "./../test.h"

int math_intAbsTheory(int expected, int testValue)
{
    int actual;
    actual = math_intAbs(testValue);
    return assertIntEquals(expected, actual);
}

int math_intAbsNegGivesPos() { return math_intAbsTheory(1, -1); }
int math_intAbsPosGivesPos() { return math_intAbsTheory(1, 1); }

int main() 
{
    test_declareAndRun("Math abs given negative integer returns positive", math_intAbsNegGivesPos);
    test_declareAndRun("Math abs given positive integer returns positive", math_intAbsPosGivesPos);
}
