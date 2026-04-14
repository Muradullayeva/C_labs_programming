# include "matrix_ops.h"
#include <stdlib.h>

double **matrix_sum(const double **A, const double **B, int n){
    int i, j;
    double **c;
    c = (double**)malloc(n*sizeof(double*));
    for(i = 0;i<n;i++){
        c[i] = (double*)malloc(n*sizeof(double));
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            c[i][j]=A[i][j]+B[i][j];
        }
    }
    return c;
}

double **matrix_min(const double **A, const double **B, int n){
    int i, j;
    double **c;
    c = (double**)malloc(n*sizeof(double*));
    for(i = 0;i<n;i++){
        c[i] = (double*)malloc(n*sizeof(double));
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            c[i][j]=A[i][j]-B[i][j];
        }
    }
    return c;
}

double **matrix_umn(const double **A, const double **B, int n){
    int i, j, k;
    double **c;
    c = (double**)malloc(n*sizeof(double*));
    for(i = 0;i<n;i++){
        c[i] = (double*)malloc(n*sizeof(double));
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            c[i][j] = 0;
            for (k = 0; k < n; k++){
                c[i][j] += A[i][k] + B[k][j];

            }
        }
    }
    return c;
}
