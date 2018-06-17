#ifndef LIST_H
#define LIST_H

/**
 * @brief Immutable linked list module.
 * 
 * @file linkedList.h
 * @author your name
 * @date 2018-06-17
 */

#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"
#include "./../option/option.h"

typedef struct _List List;

/**
 * @brief Creates a new, empty list.
 * 
 * @return List* an empty list.
 */
List* list_empty();


/**
 * @brief Cons a new value to the end of the list and return the list.
 * 
 * @param list the list to cons
 * @param val the value to cons
 * @return List the new list
 */
List* list_cons(List* list, Dynamic val);

/**
 * @brief Concatenates two lists together.
 * 
 * @param listA the first list
 * @param listB the second list
 * @return List the result of the concatenation.
 */
List* list_concatenate(List* listA, List* listB);

/**
 * @brief Retrieves the head-element from the list.
 * 
 * @param list the list to take the head from.
 * @return Option the head element.
 */
Option list_head(List* list);

/**
 * @brief Retrieves the tail of the list.
 * 
 * @param list the list.
 * @return List the tail of the list.
 */
List* list_tail(List* list);

/**
 * @brief Retrieves the item at given index in given list.
 * 
 * @param list the list
 * @param index the index
 * @return Option some item, if any
 */
Option list_item(List* list, int index);

/**
 * @brief Retrieves the number of elements in the list.
 * 
 * @param list the list.
 * @return int the length of the list in number of elements.
 */
int list_length(List* list);

/**
 * @brief Deallocs the given list.
 * 
 * @param list a list.
 */
void list_destroy(List* list);

/**
 * @brief Creates a new list from an iterator (consumes the iterator).
 * 
 * @param it the iterator to create the list from.
 * @return List* 
 */
List* list_initFromIterator(Iterator* it);

/**
 * @brief Initialize linked list with function.
 * 
 * @param size size of the linked list.
 * @param initFunc function that creates dynamics values from the index in the list.
 * @return List* the new list.
 */
List* list_initFromFunc(int size, Dynamic (*initFunc)(int));

/**
 * @brief Retrieves an iterator from the list;
 * 
 * @param list a list.
 * @return Iterator an iterator for the content of the given list.
 */
Iterator* list_iterator(List* list);

#endif
