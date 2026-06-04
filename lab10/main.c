#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char input[1000];
    int numbers[100];
    int count = 0;
    int sum = 0;
    int max;

    printf("Введите числа через пробел: ");

    // Ввод строки
    fgets(input, sizeof(input), stdin);

    // Разбиваем строку на числа
    char *token = strtok(input, " \n");
    while (token != NULL && count < 100) {
        numbers[count] = atoi(token);
        count++;
        token = strtok(NULL, " \n");
    }

    // Проверка: есть ли числа
    if (count == 0) {
        printf("Числа не введены!\n");
        return 1;
    }

    // Находим максимум и сумму
    max = numbers[0];
    for (int i = 0; i < count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
        sum = sum + numbers[i];
    }

    // Среднее арифметическое
    double average = (double)sum / count;

    // Вывод результатов
    printf("Максимальное число: %d\n", max);
    printf("Среднее арифметическое: %.2f\n", average);

    return 0;
}





