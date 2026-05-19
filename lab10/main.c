#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARRAY(arr, n) ({ \
    int max = (arr)[0];\
    for (int i = 1; i < (n); i++){\
       if ((arr)[i]> max)\
          max = (arr)[i];\
    }\
    max;\
})

int main() {
    char input[1000];
    int numbers [100];
    int count = 0;
    printf(" Введите числа через пробел: ");
    if  (fgets(input, sizeof (input), stdin) == NULL) {
        printf (" Ошибка ввода");
        return 1;
    }
    char *token = strtok(input, " \n");
    while (token != NULL && count < 100) {
        int num = atoi(token);
        numbers[count] = num;
        count++;
        token = strtok(NULL, " \n");
    }

    int max_value = MAX_ARRAY(numbers, count);
    
    printf (" Максимальное число: %d", max_value);
    return 0;
}





