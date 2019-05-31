#ifndef VECTORF_H
#define VECTORF_H

/**
 * @file vectorf.h
 * @author Jon Voigt Tøttrup (jon@zendata.dk)
 * @brief A module for handling vector-calculus
 * @version 0.1
 * @date 2019-05-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdarg.h>
#include "./../iterator/iterator.h"

typedef struct _Vectorf {
    int size;
    float* values;
} Vectorf;

/**
 * @brief Create a zero-vector of a given size.
 * 
 * @param size The size of the vector.
 * @return Vectorf* The resulting vector.
 */
Vectorf* vectorf_zero(int size);

/**
 * @brief Initialize a vector by a function.
 * 
 * @param size The total size of the vector.
 * @param initFun The initialization function.
 * @return Vectorf* The resulting vector.
 */
Vectorf* vectorf_initFun(int size, float (*initFun(int)));

/**
 * @brief Initialize a vector by varargs.
 * 
 * @param size The size of the vector.
 * @param f The first value of the vector.
 * @param ... The remaining values of the vector.
 * @return Vectorf* The resulting vector.
 */
Vectorf* vectorf_from(int size, float f, ...);

/**
 * @brief Initialize a vector by an iterator.
 * 
 * @param Iterator<f32> iterator The iterator containing the values packed as df32s.
 * @return Vectorf* The resulting vector.
 */
Vectorf* vectorf_init(Iterator* iterator);

/**
 * @brief Release a vector from memory.
 * 
 * @param vector A pointer to a vector.
 */
void vectorf_destroy(Vectorf* vector);

/**
 * @brief Add two vectors together.
 * 
 * @param v The first vector to add.
 * @param u The second vector to add.
 * @return Vectorf* The resulting vector.
 */
Vectorf* vectorf_add(Vectorf* v, Vectorf* u);

/**
 * @brief Scale a vector.
 * 
 * @param scalar The scalar to scale by.
 * @param vector The vector to scale.
 * @return Vectorf* The resulting vector.
 */
Vectorf* vectorf_scale(float scalar, Vectorf* vector);

/**
 * @brief Scale two vectors before adding them together.
 * 
 * @param s The scalar to apply to the first vector.
 * @param v The first vector.
 * @param t The scalar to apply to the second vector.
 * @param u The second vector.
 * @return Vectorf* The produced vector.
 */
Vectorf* vectorf_sadd(float s, Vectorf* v, float t, Vectorf* u);

/**
 * @brief Returns the magnitude of a vector.
 * 
 * @param v The vector.
 * @return float The magnitude.
 */
float vectorf_mag(Vectorf* v);

/**
 * @brief Returns the dot product of two vectors.
 * 
 * @param v The first vector.
 * @param u The second vector.
 * @return float The dot product.
 */
float vectorf_dot(Vectorf* v, Vectorf* u);

/**
 * @brief Return the angle between two vectors.
 * 
 * @param v The first vector.
 * @param u The second vector.
 * @return float The angle between the vectors.
 */
float vectorf_angle(Vectorf* v, Vectorf* u);

/**
 * @brief Returns the cross product of two vectors.
 * 
 * @param v The first vector.
 * @param u The second vector.
 * @return Vectorf* The cross product.
 */
Vectorf* vectorf_cross(Vectorf* v, Vectorf* u);

/**
 * @brief Create an iterator from a vector.
 * 
 * @param v The vector.
 * @return Iterator* The resulting iterator.
 */
Iterator* vectorf_iterator(Vectorf* v);

/**
 * @brief Retrieve a value from the vector.
 * 
 * @param index Index of value to retrieve.
 * @return float The retrieved value.
 */
float vectorf_get(Vectorf* v, int index);

/**
 * @brief Set a value in a vector.
 * 
 * @param v The vector.
 * @param index The index of the value;
 * @param value The value;
 */
void vectorf_set(Vectorf* v, int index, float value);

#endif