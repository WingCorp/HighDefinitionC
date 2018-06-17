#include "./../test.h"
#include "./../assert.h"
#include "./../../src/list/list.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/foreach/foreach.h"
#include "./../../src/fold/fold.h"
#include "./../../src/map/map.h"
#include <stdio.h>

int list_emptyListReturnsEmpty()
{
    List* list = list_empty();
    return assertIntEquals(0, list_length(list));
}

int list_consExtendsListByOneElement()
{
    List* list = list_empty();
    List* consd = list_cons(list, di32(1));
    return
        assertTrue("empty list was not same size as consd list", list_length(list) != list_length(consd))
    &&
        assertIntEquals(1, list_length(consd));
}

void printdstr(Dynamic dref)
{
    printf("Print char pointer dest\n");
    printf("%s", *((char**) ref(dref)));
}

int list_consTwiceIsListOfLengthTwo()
{
    // return assertTrue("this test works", false);
    List* list = list_empty();
    printf("Cons hello on list\n");
    List* consd1 = list_cons(list, dref(&"Hello, "));
    printf("Cons world on list\n");
    List* consd2 = list_cons(consd1, dref(&"World!\n"));
    printf("Create iterator off list\n");
    Iterator* it = list_iterator(list);
    printf("Loop through list\n");
    foreach(it, printdstr);
    return assertIntEquals(2, list_length(consd2));
}

void printdi32(Dynamic di)
{
    printf("%d\n", i32(di));
}

Dynamic squared(Dynamic di)
{
    return di32(i32(di) * i32(di));
}

Dynamic sumdi32(Dynamic acc, Dynamic d)
{
    return di32(i32(acc) + i32(d));
}

int list_iteratorWorks()
{
    List* list = list_initFromFunc(10, di32);
    printf("list initialized from function with length: %d\n", list_length(list));
    Iterator* it = list_iterator(list);
    printf("fetched list iterator.\n");
    foreach(it, printdi32);
    Iterator* squaredIt = map(it, squared);
    Dynamic sum = di32(0);
    sum = fold(squaredIt, sum, sumdi32);
    return assertIntEquals(285, i32(sum));
}

int main()
{
    test_declareAndRun("list_empty() actually returns empty list", list_emptyListReturnsEmpty);
    test_declareAndRun("list_cons extends list by one element", list_consExtendsListByOneElement);
    test_declareAndRun("list_cons twice extends list by two elements", list_consTwiceIsListOfLengthTwo);
    test_declareAndRun("list_iterator works as intended, tested with foreach, map and fold", list_iteratorWorks);
    return 0;
}