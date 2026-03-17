#include <stdio.h>
#include <math.h>

int main() {
        double a, b, c;
        int continue_program = 1;

    while ( continue_program ) {
        printf("Введите коэффициенты a, b, c: ");
        scanf("%lf %lf %lf", &a, &b, &c);
        double D = b*b - 4*a*c;
        if ( D < 0 ) {
            printf(" Нет действительных корней ");
        } else {
            double x1 = (-b + sqrt(D)) / (2 * a);
            double x2 = (-b - sqrt(D)) / (2 * a);
            printf(" Корни: x1 = %f, x2 = %f\n", x1, x2);
        }printf ("\n Хотите решить еще одно уравнения? (1 - да, 0 - нет):" );
        scanf("%d", &continue_program);
    }
    printf(" Программа завершена. До свидания!\n ");
    return 0;
}