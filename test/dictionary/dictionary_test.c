#include "./../../src/dictionary/dictionary.h"
#include "./../assert.h"
#include "./../test.h"

#include <string.h>
#include <stdio.h>

int dict_emptyCreatesEmptyDict()
{
    Dict* dict = dict_empty();
    Option opt = dict_get(dict, 0ul);
    return assertTrue("dict_get() on empty dictionary returns None", opt.type == NONE);
}

int dict_createDictFromParams()
{
    Dict* dict = dict_from(2, pair(dui64(hash("Lol")), di32(1)), pair(dui64(hash("sh*t")), di32(-1)));
    Option lol = dict_get_s(dict, "Lol");
    int lolVal = i32(coerce(lol));
    Option sht = dict_get_s(dict, "sh*t");
    int shtVal = i32(coerce(sht));
    return assertIntEquals(1, lolVal) && assertIntEquals(-1, shtVal);
}

int main()
{
    test_declareAndRun("dict_empty() creates an empty dictionary", dict_emptyCreatesEmptyDict);
    test_declareAndRun("dict_from() creates a new dictionary from the given parameters", dict_createDictFromParams);
    return 0;
}