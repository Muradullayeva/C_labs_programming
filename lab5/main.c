#include <stdio.h>
#include <stdlib.h>
#include "matrix_ops.h"
#include <locale.h>

int main() {
    int n;
    char op;
    printf(" Введите размер квадратных матриц n: ");
    scanf("%d", &n);

    double **A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
    }

    double **B = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        B[i] = (double*)malloc(n * sizeof(double));
    }

    if (!A || !B) {
        printf(" Ошибка выделения памяти! \n");
        return 1;
    }

    printf("\n Введите элементы первой матрицы: \n", n*n);
    for (int i = 0; i < n; i++) {
        printf ("Строка %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\n Введите элементы второй матрицы: \n", n*n);
    for (int i = 0; i < n; i++) {
        printf ("Строка %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &B[i][j]);
        }
    }

    printf("Введите операцию (+,-,*): ");
    scanf(" %c", &op);

    double **C = matrix_operation(A, B, n, op);

    printf ("\n Матрица - результат:\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf ("%8.2f", C[i][j]);
        }
    }

    return 0;

}