#ifndef MATRIXF_H
#define MATRIXF_H

/**
 * @file matrix.h
 * @author your name (jvoi@itu.dk)
 * @brief A matrix module for handling matrices.
 * @version 0.1
 * @date 2019-04-11
 * 
 * @copyright WingCorp (c) 2019
 * 
 */

#include "./../array/array.h"

typedef struct _Matrixf Matrixf;

Matrixf* matrixf_id(int size);

Matrixf* matrixf_initFun(int size, float* (initFun(int, int)));

Matrixf* matrixf_swapRow(Matrixf* matrix, int r_1, int r_2);

Matrixf* matrixf_scaleRow(Matrixf* matrix, int r, float scalar);

Matrixf* matrixf_addRow(Matrixf* matrix, float scalar,  int r_1, int r_2);

/**
 * @brief 
 * 
 * @param matrix The matrix to find the eigenvalues for.
 * @return Dynamic<di32, dref> containing the number of eigenvalues and the eigenvalues.
 */
Dynamic/*<di32, dref>*/ matrixf_eigenvalues(Matrixf* matrix);

Dynamic/*<di32, dref>*/ matrixf_eigenvectors(Matrixf* matrix, int lambda_count, float* eigenvalues);

float* matrixf_diagonalize();

#endif