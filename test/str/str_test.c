#include "./../../src/str/str.h"
#include "./../assert.h"
#include "./../test.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/stack/stack.h"
#include "./../../src/array/array.h"

#include <stdio.h>
#include <stdlib.h>

int str_contains_test()
{
    char* lol = "lol";
    char* o = "o";
    bool actual = str_contains(lol, o);
    return assertTrue("o is contained in lol", actual);
}

int str_not_contains_test()
{
    char* lol = "lol";
    char* r = "r";
    bool actual = str_contains(lol, r);
    return assertTrue("r is not contained in lol", !actual);
}

int str_contains_long_test()
{
    char* text = "Jon@DESKTOP-U4NQMPA:/mnt/b/Source/C/HighDefinitionC$ ./out/test/str_test.o";
    char* match = "DESKTOP-U4NQMPA";
    return assertTrue("Long match found in long word", str_contains(text, match));
}


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

int str_sub_test()
{
    char* word = "word";
    char* expected = "ord";
    char* ord = str_sub(word, 1, 4);
    return assertStringEquals(expected, ord);
}

int str_replace_test()
{
    char* goofy = "Goofy";
    char* expected = "G00fy";
    char* g00fy = str_replace(goofy, "oo", "00");
    return assertStringEquals(expected, g00fy);
}

int str_copy_test()
{
    char* word = "WORD";
    return assertStringEquals(word, str_copy(word));
}

int str_split_test()
{
    char* to_split = "YES, NO";
    Array* split = str_split(to_split, ", ");
    printf("%s\n", str(array_item(split, 0)));
    printf("%s\n", fragments[1]);
    return (!assertStringContains(fragments[0], ", ")) && (!assertStringContains(fragments[1], ", "))
        && assertStringEquals(fragments[0], "YES") && assertStringEquals(fragments[1], "NO");
}

int main()
{
    test_declareAndRun("Concatenate string works as expected", str_concat_test);
    test_declareAndRun("Join string works as expected", str_join_test);
    test_declareAndRun("o is contained in lol test", str_contains_test);
    test_declareAndRun("r is not contained in lol test", str_not_contains_test);
    test_declareAndRun("long contains test, let's stretch those loops!", str_contains_long_test);
    test_declareAndRun("str_sub test", str_sub_test);
    test_declareAndRun("str_replace test", str_replace_test);
    test_declareAndRun("str_copy_test", str_copy_test);
    test_declareAndRun("str_split removes delimiter and splits properly", str_split_test);
    return 0;
}
