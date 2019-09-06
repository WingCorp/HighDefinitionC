#include "./../test.h"
#include "./../assert.h"
#include "./../../src/array/array.h"
#include "./../../src/list/list.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/foreach/foreach.h"
#include "./../../src/fold/fold.h"
#include "./../../src/map/map.h"
#include "./../../src/str/str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printdi32(Dynamic di)
{
    printf("%d\n", i32(di));
}

int list_consTwiceIsListOfLengthTwo()
{
    List* list = list_empty();
    printf("Cons 1 on list\n");
    List* consd1 = list_cons(list, di32(1));
    Option consv1 = list_head(consd1);
    Dynamic consv1Val = consv1.value;
    printdi32(consv1Val);
    printf("Cons 2 on list\n");
    List* consd2 = list_cons(consd1, di32(2));
    printf("Create iterator of list\n");
    Iterator* it = list_iterator(list);
    printf("Loop through list\n");
    foreach(it, printdi32);
    return  assertTrue("condsv1 is Some", consv1.type) && assertIntEquals(2, list_length(consd2));
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

int list_concatenateWorks()
{
    char* start = "HAPPY ";
    List* s = list_initFromIterator(str_iterator(start));

    char* end = "BIRTHDAY";
    List* e = list_initFromIterator(str_iterator(end));
    
    List* combined = list_concatenate(s, e);

    Iterator* l = list_iterator(combined);
    
    char* expected = "HAPPY BIRTHDAY";
    
    char* actual = str(fold(l, dstr(""), *str_concat_c_d));
    return assertStringEquals(expected, actual);
}

int main()
{
    test_declareAndRun("list_empty() actually returns empty list", list_emptyListReturnsEmpty);
    test_declareAndRun("list_cons extends list by one element", list_consExtendsListByOneElement);
    test_declareAndRun("list_cons twice extends list by two elements", list_consTwiceIsListOfLengthTwo);
    test_declareAndRun("list_iterator works as intended, tested with foreach, map and fold", list_iteratorWorks);
    test_declareAndRun("list_concatenate actually works properly!", list_concatenateWorks);
    return 0;
}