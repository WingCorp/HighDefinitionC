#include "./../test.h"
#include "./../assert.h"
#include "../../src/dictionary/dictionary.h"
#include "../../src/lambda/lambda.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lambda_2Plus2Returns4()
{
    Lambda* plusTwo = lambda("a -> a + 2", dict_empty());
    Dynamic four = go(plusTwo, di32(2));
    return assertIntEquals(4, i32(four));
}

int main()
{
    test_declareAndRun("lambda 2 + 2 = 4", lambda_2Plus2Returns4);
    return 0;
}