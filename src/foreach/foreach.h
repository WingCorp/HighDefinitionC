#ifndef FOREACH_H
#define FOREACH_H

/**
 * @brief The foreach function.
 * 
 * @file foreach.h
 * @author WingCorp
 * @date 2018-06-16
 */

#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"

/**
 * @brief Performs an action on every value from an iterator using an action function.
 *  
 * @param iterator the iterator to loop through.
 * @param action the action function, must have signature: void <name>(Dynamic <arg>)
 */
void foreach(Iterator* iterator, void (*action) (Dynamic));

#endif