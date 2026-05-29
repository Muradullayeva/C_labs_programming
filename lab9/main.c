#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[256];           // массив для хранения строки
    double numbers[100];       // массив для чисел
    char operations[100];      // массив для операций + или -
    int num_count = 0;         // сколько чисел нашли
    int op_count = 0;          // сколько операций нашли

    printf("Введите выражение: ");
    fgets(input, sizeof(input), stdin);  // читаем строку

    // Убираем символ новой строки в конце
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
        i++;
    }

    // Парсим строку
    char *ptr = input;  // указатель на текущую позицию

    while (*ptr == ' ') ptr++;

    numbers[num_count++] = strtod(ptr, &ptr);

    // Читаем операции и числа
    while (*ptr != '\0') {
        // Пропускаем пробелы
        while (*ptr == ' ') ptr++;

        // Если нашли + или -
        if (*ptr == '+' || *ptr == '-') {
            operations[op_count++] = *ptr;  // сохраняем операцию
            ptr++;                          // переходим к следующему символу

            // Пропускаем пробелы после операции
            while (*ptr == ' ') ptr++;

            // Читаем число
            numbers[num_count++] = strtod(ptr, &ptr);
        } else {
            break;  // если не операция, конец строки
        }
    }

    // Вычисляем результат
    double result = numbers[0];  // начинаем с первого числа

    for (i = 0; i < op_count; i++) {
        if (operations[i] == '+') {
            result = result + numbers[i + 1];
        } else {
            result = result - numbers[i + 1];
        }
    }

    printf("Результат: %.2f\n", result);

    return 0;
}