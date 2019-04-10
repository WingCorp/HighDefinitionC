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
    Dict* dict = dict_from(2, pair(dui64(hash("One")), di32(1)), pair(dui64(hash("Zero")), di32(0)));
    Option one = dict_get_s(dict, "One");
    int lolVal = i32(coerce(one));
    Option zero = dict_get_s(dict, "Zero");
    int shtVal = i32(coerce(zero));
    return assertIntEquals(1, lolVal) && assertIntEquals(0, shtVal);
}

int dict_putUntilResize()
{
    Dict* dict = dict_empty();
    dict_put_s(dict, "What", dref("Ever"));
    Option opt = dict_get_s(dict, "What");
    char* optVal = ref(coerce(opt));

    char* keys[4] = {"a", "b", "c", "d"};    
    int i;
    for(i = 0; i < 4; i++)
    {
        dict_put_s(dict, keys[i], di32(i));
    }
    
    return assertStringEquals("Ever", optVal) && assertIntEquals(5, dict_size(dict));
}

int main()
{
    test_declareAndRun("dict_empty() creates an empty dictionary", dict_emptyCreatesEmptyDict);
    test_declareAndRun("dict_from() creates a new dictionary from the given parameters", dict_createDictFromParams);
    test_declareAndRun("dict_put() multiple times will resize dictionary", dict_putUntilResize);
    return 0;
}