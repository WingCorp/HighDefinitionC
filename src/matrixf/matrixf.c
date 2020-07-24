#include "matrixf.h"

#include <stdlib.h>

typedef struct _Matrixf {
    int n; //row length
    int m; //column length
    Vectorf** rows;
} Matrixf;

Matrixf* matrixf_id(int size)
{
    Matrixf* matrix = malloc(sizeof(Matrixf));
    Vectorf** rows = malloc(sizeof(Vectorf*)*size);
    int i;
    for (i = 0; i < size; i++)
    {
        rows[i] = vectorf_zero(size);
        vectorf_set(rows[i], i, 1.0f);
    }
    matrix->n = size;
    matrix->m = size;
    matrix->rows = rows;
    return matrix;
}

Matrixf* matrixf_initFun(int size, float* (initFun(int, int)));

Matrixf* matrixf_swapRow(Matrixf* matrix, int r_1, int r_2);

Matrixf* matrixf_scaleRow(Matrixf* matrix, int r, float scalar);

Matrixf* matrixf_addRow(Matrixf* matrix, float scalar,  int r_1, int r_2);

Matrixf* matrixf_rowEchelon(Matrixf* matrix);

Matrixf* matrixf_reducedRowEchelon(Matrixf* matrix);

bool matrixf_isConsistent(Matrixf* matrix);

Dynamic/*<dref<Matrixf> option>*/ matrixf_parametricSolution(Matrixf* matrix);

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