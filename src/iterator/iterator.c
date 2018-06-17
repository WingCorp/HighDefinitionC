#include "iterator.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _Iterator
{
    int position;
    int length;
    Dynamic* data;
} Iterator;

Iterator* iterator_init(Dynamic* data, int length)
{
    printf("initializing iterator of length: %d\n", length);
    Iterator* iterator = malloc(sizeof(Iterator));
    iterator->position = 0;
    iterator->length = length;
    iterator->data = data;
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
        Dynamic toReturn = iterator->data[iterator->position];
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
    free(iterator->data);
    free(iterator);
}
