# include "matrix_ops.h"

#include <stdio.h>
#include <stdlib.h>

double** matrix_operation (double** A, double** B, int n, char op) {
    double** result = (double**)malloc(n * sizeof(double*));

    if (result == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        result[i] = (double*)malloc(n * sizeof(double));
        if (result[i] == NULL) {
            for (int k = 0; k < n; k++) {
                free(result[k]);
            }
            free(result);
            return NULL;
        }
    }
        if (op == '+') {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    result[i][j] = A[i][j] + B[i][j];
                }
            }
        }
       else if (op == '-') {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    result[i][j] = A[i][j] - B[i][j];
                }
            }
        }
        else if (op == '*') {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0.0;
                    for (int k = 0; k < n; k++) {
                        sum += A[i][k] * B[k][j];
                    }
                    result[i][j] = sum;
                }
            }
        }
        return result;
    }