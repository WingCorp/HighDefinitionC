#ifndef MATRIXF_H
#define MATRIXF_H

/**
 * @file matrix.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief A matrix module for handling matrices.
 * @version 0.1
 * @date 2019-04-11
 * 
 * @copyright WingCorp (c) 2019
 * 
 */

#include <stdbool.h>
#include <stdarg.h>

#include "./../option/option.h"
#include "./../vectorf/vectorf.h"

typedef struct _Matrixf Matrixf;

Matrixf* matrixf_id(int size);

Matrixf* matrixf_initFun(int size, float (*initFun(int, int)));

Matrixf* matrixf_fromRows(int rows, Vectorf* row, ...);

Matrixf* matrixf_fromColumns(int columns, Vectorf* column, ...);

Matrixf* matrixf_swapRow(Matrixf* matrix, int r_1, int r_2);

Matrixf* matrixf_scaleRow(Matrixf* matrix, int r, float scalar);

Matrixf* matrixf_addRow(Matrixf* matrix, float scalar,  int r_1, int r_2);

Matrixf* matrixf_rowEchelon(Matrixf* matrix);

Matrixf* matrixf_reducedRowEchelon(Matrixf* matrix);

bool matrixf_isConsistent(Matrixf* matrix);

Option/*<dref<Matrixf> option>*/ matrixf_parametricSolution(Matrixf* matrix);

double matrixf_calculateDeterminant(Matrixf* matrix);

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