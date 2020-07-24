#include "./../../src/str/str.h"
#include "./../../src/set/set.h"
#include "./../assert.h"
#include "./../test.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/foreach/foreach.h"
#include "./../../src/fold/fold.h"
#include "./../../src/map/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dynamic countOnes(Dynamic acc, Dynamic i)
{
    if (i32(i) == 1)
    {
        return di32(i32(acc) + 1);
    }
    else return acc;
}

int set_setOfIntsWork()
{
    Set* s = set_fromIntegers(5, 0, 1, 2, 3, 4);
    set_addInteger(s, 1);
    Iterator* i = set_iterator(s);
    int expected = 1;
    int actual = i32(fold(i, di32(0), *countOnes));
    return assertIntEquals(expected, actual);
}

Dynamic countHAs(Dynamic acc, Dynamic s)
{
    if (str_equals(str(s), "HA"))
    {
        return di32(i32(acc) + 1);
    }
    else return acc;
}

int set_setOfStringsWork()
{
    Set* s = set_fromStrings(3, "HA", "JA", "NEJ");
    set_addString(s, "HA");
    Iterator* i = set_iterator(s);
    int expected = 1;
    int actual = i32(fold(i, di32(0), *countHAs));
    return assertIntEquals(expected, actual);
}

int main()
{
    test_declareAndRun("Adding the same integer multiple times to a set results in only one occurence in set", set_setOfIntsWork);
    test_declareAndRun("Adding the same string multiple times to a set results in only one occurence in set", set_setOfIntsWork);
    return 0;
}