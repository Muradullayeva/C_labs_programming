# include "matrix_ops.h"
#include <stdlib.h>

double** matrix_operation(const double **A, const double **B, int n, char op) {
    double **C = (double**)malloc(n * sizeof(double*));

    if (!C) return NULL;

    for (int i = 0; i < n; i++) {
        C[i] = (double*)malloc(n * sizeof(double));
    }
    if (op == '+') {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] + B[i][j];
    } else if ( op == '-') {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] - B[i][j];
    } else if ( op == '*') {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                double sum = 0.0;
                for (int k = 0; k < n; k++)
                    sum += A[i][k] * B[k][j];
                C[i][j] = sum;
            }
    }
    return C;
}

