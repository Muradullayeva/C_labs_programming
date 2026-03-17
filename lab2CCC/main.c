#include <stdio.h>

int main() {
    int N=4;
    double matrix [N][N];
    int i,j;
    double sumMain = 0, sumSec = 0;
    printf ("Введите 16 чисел для матрицы NxN: \n ");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%lf", &matrix [i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        sumMain += matrix [i][i];
        sumSec += matrix [i][N - 1 -i ]; //Расчитать побочных 2 диагональ
    }
    printf (" Сумма главной диагонали: %.2lf \n", sumMain);
    printf (" Сумма побочной диагонали: %.2lf \n", sumSec);

    double mat [2][2], result [2][2];
    printf(" Введите 4 числа для матрицы 2x2: \n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%lf", &mat [i][j]);
        }
    }

    result[0][0] = mat [0][0] * mat [0][0] + mat [0][1] * mat [1][0];
    result [0][1] = mat [0][0] * mat [0][1] + mat [0][1] * mat [1][1];
    result [1][0] = mat [1][0] * mat [0][0] + mat [1][1] * mat [1][0];
    result [1][1] = mat [1][0] * mat [0][1] + mat [1][1] * mat [1][1];
    printf (" Квадрат матрицы 2x2: \n ");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf ("%lf", result [i][j]);
            printf(" ");
        }
        printf ("\n");
    }
    return 0;
}
