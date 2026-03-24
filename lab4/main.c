#include <stdio.h>
# include <triangle.h>

int main () {
    double a, b, c;
    printf (" Введите длины сторон треугольника: ");
    scanf ("%lf %lf %lf", &a, &b, &c);
    if (! is_valid_triangle (a,b,c)) {
        printf (" Треугольника с такими сторонами не сущесмвует.\n ");
        return 1;
    }
    double P = perimetr (a,b,c);
    double S = area (a,b,c);
    printf(" Периметр: %.2f\n ", P);
    printf (" Площадь: %.2f\n ", S);
    return 0;
}