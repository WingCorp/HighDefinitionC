#ifndef ITERATOR_H
#define ITERATOR_H

#include "./../dynamic/dynamic.h"
#include "./../option/option.h"

typedef struct _Iterator
{
    int position;
    int length;
    Dynamic* data;
} Iterator;

/**
 * @brief Initializes a new iterator from a Dynamic pointer.
 * 
 * @param data The data to iterate from.
 * @param length The length of the data.
 * @return Iterator An iterator struct.
 */
Iterator iterator(Dynamic* data, int length);

/**
 * @brief Whether an iterator holds another value.
 * 
 * @param iterator 
 * @return bool a bool value.
 */
bool iterator_hasNext(Iterator iterator);

/**
 * @brief Retrieves the next value from the iterator.
 * 
 * @param iterator the iterator to get the value from.
 * @return Option some if there is a value, none if there isn't.
 */
Option iterator_next(Iterator iterator);

/**
 * @brief Destroys the iterator and the values that the iterator is reading from.
 * 
 * @param iterator the iterator to destroy.
 */
void iterator_destroy(Iterator iterator);

#endif
