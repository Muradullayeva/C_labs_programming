# include "functions.h"
# include <stdarg.h>
# include <float.h>

double sum (int count, ...) {  //ф-ия для суммы
    va_list args;
    double result = 0.0;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        result += va_arg(args, double);
    }
    va_end(args);
    return result;
}

double max (int count, ...) {  // ф-ия для поиска max
    va_list args;
    double result = - DBL_MAX;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        double current = va_arg(args, double); //current- текущей элемент
        if (current > result) {
            result = current;
        }
    }
    va_end(args);
    return result;
}

double min (int count, ...) {
    va_list args;
    double result = DBL_MAX;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        double current = va_arg(args, double);
        if (current < result) {
            result = current;
        }
    }
    va_end(args);
    return result;
}

double average (int count, ...) {
    va_list args;
    double total = 0.0; //total- суммы
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(args, double);
    }
    va_end(args);
    if (count > 0) {
        return (total / count);
    } else {
        return 0.0;
    }
}