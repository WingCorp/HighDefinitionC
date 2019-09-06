#include "./../../src/str/str.h"
#include "./../assert.h"
#include "./../test.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/stack/stack.h"

#include <stdio.h>
#include <stdlib.h>

int str_concat_test()
{
    char* lol = "lol";
    char* lollol = str_concat(lol, lol);
    return assertStringEquals("lollol", lollol);
}

int str_join_test()
{
    Stack* stack = stack_init(5);
    int i;
    for (i = 0; i <= 5; i++)
    {
        stack_push(stack, di32(i));
    }
    Iterator* iterator = stack_iterator(stack);
    char* expected = "0, 1, 2, 3, 4, 5";
    char* actual = str_join(", ", iterator, *to_str);
    return assertStringEquals(expected, actual);
}

int main()
{
    test_declareAndRun("Concatenate string works as expeced", str_concat_test);
    test_declareAndRun("Join string works as expeced", str_join_test);
    return 0;
}