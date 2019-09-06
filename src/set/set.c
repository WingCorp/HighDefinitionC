#include "set.h"
#include "./../tree/tree.h"
#include "./../comparable/comparable.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct _Set 
{
    Tree* tree;
} Set;

Set* set_empty()
{
    Set* set = malloc(sizeof(Set));
    set->tree = tree_init();
    return set;
}

void set_add(Set* set, Comparable item)
{
    tree_put(set->tree, item, item.value);
}

void set_add_d(Set* set, Dynamic item)
{
    tree_put(set->tree, comparable(item), item);
}

void set_add_i32(Set* set, int item)
{
    tree_put(set->tree, comparable(di32(item)), di32(item));
}

void set_add_i64(Set* set, long item)
{
    tree_put(set->tree, comparable(di64(item)), di64(item));
}

void set_add_chr(Set* set, char item)
{
    tree_put(set->tree, comparable(dchr(item)), dchr(item));
}

void set_add_str(Set* set, char* item)
{
    tree_put(set->tree, comparable(dstr(item)), dstr(item));
}

bool set_contains(Set* set, Comparable item)
{
    return tree_contains(set->tree, item);
}

Set* set_initFun(int size, Comparable *(initFun)(int))
{
    Set* set = set_empty();
    int i;
    for(i = 0; i < size; i++)
    {
        set_add(set, *initFun(i));
    }
    return set;
}

Set* set_init(Iterator* iterator)
{
    Set* set = set_empty();
    Option itemOpt = iterator_next(iterator);
    while(itemOpt.type == SOME)
    {
        set_add(set, comparable(itemOpt.value));
        itemOpt = iterator_next(iterator);
    }
    return set;
}

Set* set_from(int size, Comparable comp, ...)
{
    va_list args;
    va_start(args, comp);
    Set* set = set_empty();
    set_add(set, comp);
    int i;
    for (i = 1; i < size; i++)
    {
        Comparable arg = va_arg(args, Comparable);
        set_add(set, arg);
    }
    va_end(args);
    return set;
}

Set* set_from_ds(int size, Dynamic comp, ...)
{
    va_list args;
    va_start(args, comp);
    Set* set = set_empty();
    set_add(set, comparable(comp));
    int i;
    for (i = 1; i < size; i++)
    {
        Dynamic arg = va_arg(args, Dynamic);
        set_add(set, comparable(arg));
    }
    va_end(args);
    return set;
}

Set* set_from_i32s(int size, int value, ...)
{
    va_list args;
    va_start(args, value);
    Set* set = set_empty();
    set_add(set, comparable(di32(value)));
    int i;
    for (i = 1; i < size; i++)
    {
        int arg = va_arg(args, int);
        set_add(set, comparable(di32(arg)));
    }
    va_end(args);
    return set;
}

Set* set_from_i64s(int size, long value, ...)
{
    va_list args;
    va_start(args, value);
    Set* set = set_empty();
    set_add(set, comparable(di64(value)));
    int i;
    for (i = 1; i < size; i++)
    {
        long arg = va_arg(args, long);
        set_add(set, comparable(di64(arg)));
    }
    va_end(args);
    return set;
}

Set* set_from_chrs(int size, char value, ...)
{
    va_list args;
    va_start(args, value);
    Set* set = set_empty();
    set_add(set, comparable(dchr(value)));
    int i;
    for (i = 1; i < size; i++)
    {
        char arg = va_arg(args, int);
        set_add(set, comparable(dchr(arg)));
    }
    va_end(args);
    return set;
}

Set* set_from_strs(int size, char* value, ...)
{
    va_list args;
    va_start(args, value);
    Set* set = set_empty();
    set_add(set, comparable(dstr(value)));
    int i;
    for (i = 1; i < size; i++)
    {
        char* arg = va_arg(args, char*);
        set_add(set, comparable(dstr(arg)));
    }
    va_end(args);
    return set;
}

Iterator* set_iterator(Set* set)
{
    return tree_iterator(set->tree);
}

void set_destroy(Set* set)
{
    tree_destroy(set->tree);
    free(set);
}
