#include "iterator.h"
#include "./../option/option.h"
#include <stdlib.h>
#include <stdio.h>

typedef union _Source
{
    Dynamic* data;
    Dynamic (*nextFun)(int);
} Source;

typedef enum _Type
{
    EAGER,
    LAZY
} Type;

typedef struct _Iterator
{
    int position;
    int length;
    Source* source;
    Type type;
} Iterator;

Iterator* iterator_init_eager(Dynamic* data, int length)
{
    Iterator* iterator = malloc(sizeof(Iterator));
    iterator->position = 0;
    iterator->length = length;
    iterator->type = EAGER;
    iterator->source = malloc(sizeof(Source));
    iterator->source->data = data;
    return iterator;
}

Iterator* iterator_init_lazy(Dynamic (*nextFun)(int), int length)
{
    Iterator* iterator = malloc(sizeof(Iterator));
    iterator->position = 0;
    iterator->length = length;
    iterator->type = LAZY;
    iterator->source = malloc(sizeof(Source));
    iterator->source->nextFun = nextFun;
    return iterator;
}

bool iterator_hasNext(Iterator* iterator)
{
    return iterator->position < iterator->length;
}

Option iterator_next(Iterator* iterator)
{
    if(iterator->position < iterator->length)
    {
        Dynamic toReturn;
        switch(iterator->type)
        {
            case EAGER:
                toReturn = iterator->source->data[iterator->position];
                break;
            case LAZY:
                toReturn = iterator->source->nextFun(iterator->position);
                break;
        }
        iterator->position += 1;
        return some(toReturn);
    }
    else
    {
        return none();
    }
}

int iterator_remaining(Iterator* iterator)
{
    return iterator->length - iterator->position;
}

void iterator_reset(Iterator* iterator)
{
    iterator->position = 0;
}

void iterator_destroy(Iterator* iterator)
{
    free(iterator);
}
