#ifndef COMPARABLE_H
#define COMPARABLE_H

/**
 * @file comparable.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief A wrapper for Dynamics that allow them to be compared,
 *        given, that they are the same type.
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../dynamic/dynamic.h"

typedef struct _Comparable
{
    Dynamic value;
} Comparable;

/**
 * @brief Creates a Comparable from a Dynamic
 * 
 * Fails if the dynamic cannot be converted to a Comparable.
 * 
 * @param dynamic The dynamic value.
 * @return Comparable The value, wrapped in a Comparable.
 */
Comparable comparable(Dynamic dynamic);

/**
 * @brief Compares two Comparables
 * 
 * @param a 
 * @param b 
 * @return int 0 if a == b, 1 if a > b, -1 if a < b
 */
int compare(Comparable a, Comparable b);

#endif
