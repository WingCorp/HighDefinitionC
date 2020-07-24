#include "./../test.h"
#include "./../assert.h"
#include "../../src/dictionary/dictionary.h"
#include "../../src/list/list.h"
#include "../../src/lambda/lambda.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dynamic plus_two(Dict* _, List* args)
{
    int unpacked = i32(coerce(list_head(args)));
    return some(di32(unpacked + 2));
}

int lambda_2Plus2Returns4()
{
    Lambda* plusTwo = lambda(plus_two, dict_empty());
    Dynamic four = coerce(invoke(plusTwo, list_from(1, di32(2))));
    return assertIntEquals(4, i32(four));
}

int main()
{
    test_declareAndRun("lambda 2 + 2 = 4", lambda_2Plus2Returns4);
    return 0;
}