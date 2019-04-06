#ifndef MAP2_H
#define MAP2_H
/**
 * @file map2.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief map2, return of the map module
 * 
 * Capable of mapping over 2 iterators at the same time.
 * 
 * @version 0.1
 * @date 2018-11-06
 *
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"

Iterator* map2(Iterator* lit, Iterator* rit, Dynamic (*mapper) (Dynamic, Dynamic));

#endif