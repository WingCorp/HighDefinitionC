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
 * @brief Set an Empty set object.
 * 
 * @return Set* 
 */
Set* set_empty();

/**
 * @brief Set initialization with a fixed size and initFunction.
 * 
 * @param size 
 * @param initFun 
 * @return Set* 
 */
Set* set_init(int size, Comparable *(initFun)(int));

Set* set_init(Iterator* iterator);

Set* set_add(Comparable item);

Set* set_contains(Comparable item);

Iterator* set_iterator(Set* set);

#endif