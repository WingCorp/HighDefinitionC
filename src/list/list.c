#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include "./../option/option.h"
#include "./../iterator/iterator.h"
#include <stdio.h>

struct _Link;

typedef struct _Link
{
    Dynamic value;
    struct _Link* next;
    struct _Link* prev;
} Link;

typedef struct _List
{
    Link* start;
    Link* end;
    int length;
} List;

List* list_empty()
{
    List* listRef = malloc(sizeof(List));
    listRef->length = 0;
    return listRef;
}

List* list_cons(List* list, Dynamic val)
{
    List* outlist = list_empty();
    Link* link = malloc(sizeof(Link));
    link->value = val;
    if(list->start)
    {
        link->prev = list->end;
        link->prev->next = link;
        outlist->start = list->start;
    }
    else
    {
        outlist->start = link;
    }
    outlist->end = link;
    outlist->length = list->length + 1;
    return outlist;
}

List* list_copy(List* list)
{
    List* outList = list_empty();
    Link* currentLink = list->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    return list_cons(outList, currentLink->value);
}

List* list_concatenate(List* listA, List* listB)
{
    List* outList = list_empty();
    Link* currentLink = listA->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    outList = list_cons(outList, currentLink->value);
    currentLink = listB->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    outList = list_cons(outList, currentLink->value);
    return outList;
}

Option list_head(List* list)
{
    if (list->start)
    {
        return some(list->start->value);
    }
    else return none();
}

List* list_tail(List* list)
{
    List* outList = list_empty();
    Link* currentLink = list->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    return outList;
}

Option list_item(List* list, int index)
{
    if (index < 0 || index >= list->length)
    {
        return none();
    }

    bool goReverse = index > (list->length / 2);
    
    int ptr;
    Link* currentLink;

    if (goReverse)
    {
        ptr = list->length - 1;
        currentLink = list->end;
    }
    else
    {
        ptr = 0;
        currentLink = list->start;
    }

    while(ptr != index)
    {
        if (goReverse && currentLink->prev)
        {
            currentLink = currentLink->prev;
            ptr -= 1;
        }
        else if(!goReverse && currentLink->next)
        {
            currentLink = currentLink->next;
            ptr += 1;
        }
        else 
        {
            return none();
        }
    }
    return some(currentLink->value);
}

int list_length(List* list)
{
    return list->length;
}

void list_destroy(List* list)
{
    free(list);
}

List* list_initFromIterator(Iterator* it)
{
    List* list = list_empty();
    while(iterator_hasNext(it))
    {
        list = list_cons(list, iterator_next(it).value);
    }
    return list;
}

List* list_initFromFunc(int size, Dynamic (*initFunc)(int))
{
    int i;
    List* list = list_empty();
    for(i = 0; i < size; i++)
    {
        Dynamic val = (*initFunc)(i);
        list = list_cons(list, val);
    }
    return list;
}

Iterator* list_iterator(List* list)
{
    int length = list->length;
    int i = 0;
    printf("malloc dynArr\n");
    Dynamic* dynArr = malloc(length * sizeof(Dynamic));
    printf("dealloc list->start\n");
    Link* currentLink = list->start;
    printf("currentLink: %p, currentLink->next: %p\n", (void*) currentLink, (void*) currentLink->next);
    printf("while loop:\n");
    while(currentLink->next)
    {
        printf("dealloc list->value\n");
        Dynamic currentValue = currentLink->value;
        printf("set dynArr[%d]\n", i);
        dynArr[i] = currentValue;
        currentLink = currentLink->next;
        i += 1;
    }
    dynArr[i] = currentLink->value;
    return iterator_init(dynArr, length);
}