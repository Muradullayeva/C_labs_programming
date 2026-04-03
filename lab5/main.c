#include <stdio.h>
#include <stdlib.h>
#include "matrix_ops.h"
#include <locale.h>

double** allocate_matrix(int n) {
    setlocale(LC_ALL, "RUS");
    double **mat = (double**)malloc(n * sizeof(double*));
    if (mat == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        mat[i] = (double*)malloc(n * sizeof(double));
        if (mat[i] == NULL) {
            for (int k = 0; k < n; k++) {
                free(mat[k]);
            }
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void free_matrix(double** mat, int n) {
    if (mat == NULL) {
        for (int i = 0; i < n; i++) {
            free(mat[i]);
        }
        free(mat);
    }
}

void input_matrix(double** mat, int n, const char* name) {
    printf("\n Введите элемент матрицы %s (%dx %d): \n", name, n, n);
    for (int i = 0; i < n; i++) {
        printf ("Строка %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }
}

void print_matrix(double** mat, int n, const char* name) {
    printf ("\n Матрица %s:\n ", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf ("%8.2f", mat[i][j]);
        }
        printf ("\n");
    }
}

int main() {
    int n;
    char op;
    printf(" Введите размер квадратных матриц n: ");
    if (scanf("%d", &n) != 1 || n <=0 ) {
        printf (" Ошибка: некорректный размер! \n");
        return 1;
    }
    double** A = allocate_matrix(n);
    double** B = allocate_matrix(n);
    if (A == NULL || B == NULL) {
        printf(" Ошибка выделения памяти! \n");
        if (A) free_matrix(A, n);
        if (B) free_matrix(B, n);
        return 1;
    }
    printf ("\n Ввод матрицы A");
    input_matrix(A, n, "A");
    printf ("\n Ввод матрицы B");
    input_matrix(B, n, "B");
    printf ("\n Выбор операции: ('+', '-', '*': ");
    scanf(" %c", &op);

    if (op != '+' && op != '-' && op != '*' ) {
        printf(" Ошибка операции! \n");
        free_matrix(A, n);
        free_matrix(B, n);
        return 1;
    }
    double** C = matrix_operation (A, B, n, op);
    printf("\n Результат: \n");
    print_matrix(C, n, "Результат");
    return 0;
}