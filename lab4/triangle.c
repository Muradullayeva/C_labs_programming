# include <triangle.h>
# include <math.h>

int is_valid_triangle(double a, double b, double c){
    return (a + b > c) && (a + c > b) && (c + b > a);
}
double perimetr(double a, double b, double c) {
    return a + b + c;
}
double area(double a, double b, double c) {
    double p=perimetr(a, b, c)/ 2.0;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}