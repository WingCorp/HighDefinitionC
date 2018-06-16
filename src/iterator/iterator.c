#include "iterator.h"
#include <stdlib.h>

Iterator iterator(Dynamic* data, int length)
{
    return (Iterator) { .position = 0, .length = length, .data = data };
}

bool iterator_hasNext(Iterator iterator)
{
    return iterator.position >= iterator.length;
}

Option iterator_next(Iterator iterator)
{
    if(iterator.position < iterator.length)
    {
        Dynamic toReturn = iterator.data[iterator.position];
        iterator.position += 1;
        return some(toReturn);
    }
    else
    {
        return none();
    }
}

void iterator_destroy(Iterator iterator)
{
    free(iterator.data);
}
