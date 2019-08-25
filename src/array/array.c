#include "./array.h"
#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"
#include "./../option/option.h"
#include "./../fail/fail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Array
{
    Dynamic* data;
    int length;
} Array;

Array* array_empty(int length)
{
    if(length <= 0)
    {
        failwith("Cannot initialize array of length <= 0!");
    }
    Array* array = malloc(sizeof(Array));
    array->data = malloc(sizeof(Dynamic) * length);
    array->length = length;
    return array;
}

Array* array_init(Dynamic* dynamics, int length)
{
    Array* array = array_empty(length);
    int i;
    //Copy the values.
    for (i = 0; i < length; i++)
    {
        array->data[i] = dynamics[i];
    }
    return array;
}

int array_length(Array* array)
{
    return array->length;
}

Option array_item(Array* array, int index)
{
    if (index >= 0 && index < array->length)
    {
        return some(array->data[index]);
    }
    else return none();
}

void array_setItem(Array* array, int index, Dynamic value)
{
    if (index >= 0 && index < array->length)
    {
        array->data[index] = value;
    }
    else
    {
        failwith("Cannot set item to index that is out of bounds!");
    }
}

Iterator* array_iterator(Array* array)
{
    return iterator_init_eager(array->data, array->length);
}

Array* array_initFromIterator(Iterator* it)
{
    Array* array = array_empty(iterator_remaining(it));
    int i = 0;
    while(iterator_hasNext(it))
    {
        array->data[i] = iterator_next(it).value;
        i += 1;
    }
    return array;
}

Array* array_initFromFunc(int length, Dynamic (*initFunc)(int))
{
    Array* array = array_empty(length);
    int i;
    for (i = 0; i < length; i++)
    {
        array->data[i] = (*initFunc)(i);
    }
    return array;
}

void array_destroy(Array* array)
{
    free(array->data);
    free(array);
}