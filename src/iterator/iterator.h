#ifndef ITERATOR_H
#define ITERATOR_H

#include "./../dynamic/dynamic.h"
#include "./../option/option.h"

typedef struct _Iterator Iterator;

/**
 * @brief Initializes a new iterator from a Dynamic pointer.
 * 
 * @param data The data to iterate from.
 * @param length The length of the data.
 * @return Iterator An Iterator struct.
 */
Iterator* iterator_init_eager(Dynamic* data, int length);

/**
 * @brief Initializes a new iterator from an int -> Dynamic function.
 * 
 * @param nextFun A function that takes the position of the iterator
 *                and returns the corresponding Dynamic.
 * @param length The length of the iterator.
 * @return Iterator* An Iterator struct.
 */
Iterator* iterator_init_lazy(Dynamic (*nextFun)(int), int length);

/**
 * @brief Whether an iterator holds another value.
 * 
 * @param iterator 
 * @return bool a bool value.
 */
bool iterator_hasNext(Iterator* iterator);

/**
 * @brief Retrieves the next value from the iterator.
 * 
 * @param iterator the iterator to get the value from.
 * @return Option some if there is a value, none if there isn't.
 */
Option iterator_next(Iterator* iterator);

/**
 * @brief How many entries that remain in the iterator.
 * 
 * @param iterator 
 * @return int 
 */
int iterator_remaining(Iterator* iterator);

/**
 * @brief Resets iterator.
 * 
 * @param iterator the iterator.
 */
void iterator_reset(Iterator* iterator);

/**
 * @brief Destroys the iterator and the values that the iterator is reading from.
 * 
 * @param iterator the iterator to destroy.
 */
void iterator_destroy(Iterator* iterator);

#endif
