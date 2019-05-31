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

#include "./../array/array.h"

typedef struct _Vectorf Vectorf;

Vectorf* vectorf_zero(int size);

Vectorf* vectorf_initFun(int size, float* (initFun(int)));



#endif