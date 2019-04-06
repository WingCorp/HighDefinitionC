#ifndef PAIR_H
#define PAIR_H

/**
 * @file pair.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief A Pair module for packing two dynamics together.
 *        Useful for returning two values from a function.
 * @version 0.1
 * @date 2019-04-06
 * 
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../dynamic/dynamic.h"

typedef struct _Pair
{
    DynType left_type;
    DynType right_type;
    Dynamic left;
    Dynamic right;
} Pair;

/**
 * @brief Creates a new pair from two dynamic values.
 * 
 * @param left The left value.
 * @param right The right value.
 * @return Pair The constructed pair.
 */
Pair pair_of(Dynamic left, Dynamic right);

#endif