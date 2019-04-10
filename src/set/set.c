#include "set.h"
#include "./../tree/tree.h"

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

bool set_contains(Set* set, Comparable item)
{
    return tree_contains(set->tree, item);
}

Set* set_init(int size, Comparable *(initFun)(int))
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

Iterator* set_iterator(Set* set)
{
    tree_iterator(set->tree);
}

void set_destroy(Set* set)
{
    tree_destroy(set->tree);
    free(set);
}
