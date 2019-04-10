#ifndef SET_H
#define SET_H
/**
 * @file set.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief A Tree-Set implementation.
 * @version 0.1
 * @date 2018-11-05
 *
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../comparable/comparable.h"
#include "./../iterator/iterator.h"

/**
 * @brief The Set struct.
 *        A set of Comparables.
 */
typedef struct _Set Set;

/**
 * @brief Create an Empty set object.
 * 
 * @return Set* A new empty set.
 */
Set* set_empty();

/**
 * @brief Initialize a Set with a fixed size and initFunction.
 * 
 * @param size The size of the new set.
 * @param initFun A function that takes an integer and returns a Set item.
 * @return Set* A new Set.
 */
Set* set_initFun(int size, Comparable *(initFun)(int));

/**
 * @brief Initialize a Set with an iterator of comparable values.
 * 
 * @param iterator An iterator of Comparable values
 * @return Set* A new Set.
 */
Set* set_init(Iterator* iterator);

/**
 * @brief Add an item to a set.
 * 
 * @param set The set.
 * @param item The item to add.
 */
void set_add(Set* set, Comparable item);

/**
 * @brief Determine if a set contains an item.
 * 
 * @param set The set.
 * @param item The item.
 * @return true The set contains the item.
 * @return false The set does not contain the item.
 */
bool set_contains(Set* set, Comparable item);

/**
 * @brief Return an iterator of a set.
 * 
 * @param set The set to iterate over.
 * @return Iterator* The iterator.
 */
Iterator* set_iterator(Set* set);

/**
 * @brief Destroy a set, freeing it from memory.
 * 
 * @param set The set to destroy.
 */
void set_destroy(Set* set);

#endif