

#ifndef ARRAY_H
#define ARRAY_H

/**
 * @brief Wrapper for dynamic pointers, so that they include length as well.
 * 
 * @file array.h
 * @author WingCorp
 * @date 2018-06-17
 */

#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"
#include "./../option/option.h"

typedef struct _Array Array;

/**
 * @brief Initializes an empty array of a given length.
 * 
 * @param length 
 * @return Array* 
 */
Array* array_empty(int length);

/**
 * @brief Initializes the array with a Dynamic* and a specified length.
 * 
 * Copies all given Dynamic values to a new memory space on heap.
 * 
 * @param dynamics A Dynamic pointer to a primitive array of dynamics.
 * @param length the length of the dynamic array.
 * @return Array* an Array*
 */
Array* array_init(Dynamic* dynamics, int length);

/**
 * @brief Retrieves the length of the array.
 * 
 * @param array the array.
 * @return int the length,
 */
int array_length(Array* array);

/**
 * @brief Get an item from the array.
 * 
 * @param array the array.
 * @param index the index for the array.
 * @return Option an option value, some if index < length and index > 0
 *         else returns none.
 */
Option array_item(Array* array, int index);


/**
 * @brief Sets an item in the array to a new value.
 * 
 * @param array the array.
 * @param index the index to modify.
 * @param value the new value.
 */
void array_setItem(Array* array, int index, Dynamic value);

/**
 * @brief Creates an iterator from the array data.
 * 
 * @param array 
 * @return Iterator* 
 */
Iterator* array_iterator(Array* array);

/**
 * @brief Creates a new array from an iterator (consumes the iterator).
 * 
 * @param it the iterator to create the list from.
 * @return Array* 
 */
Array* array_initFromIterator(Iterator* it);

/**
 * @brief Initialize array with function.
 * 
 * @param length the length of the array.
 * @param initFunc function that inserts dynamic values into the array, based on the index.
 * @return Array* the new array.
 */
Array* list_initFromFunc(int length, Dynamic (*initFunc)(int));

/**
 * @brief Destroys the array, freeing the memory it held.
 * 
 * @param array an array.
 */
void array_destroy(Array* array);

#endif
