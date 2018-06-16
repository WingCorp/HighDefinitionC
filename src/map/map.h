#ifndef MAP_H
#define MAP_H

/**
 * @brief The 'map' monad, as known from FP.
 * 
 * @file map.h
 * @author WingCorp
 * @date 2018-06-16
 */

#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"

/**
 * @brief maps every value from an iterator with a mapper function.
 * 
 * ATTENTION: this function will allocate memory to the mapped values.
 * To free memory of old values or of mapped values, use iterator_destroy.
 * 
 * @param iterator the iterator to map.
 * @param mapper the mapper function, must have signature: Dynamic <name>(Dynamic <arg>)
 * @return Iterator a new iterator for the new values.
 */
Iterator map(Iterator iterator, Dynamic (*mapper) (Dynamic));

#endif
