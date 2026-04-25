#include <stdio.h>

#define COUNT 20

typedef struct {
    char name[20];
    char patronymic[20];
    char lastname[20];
    int year;
} humen;

int main() {
    humen a[COUNT], b[COUNT];
    int i, j;
    humen temp;

    FILE *file = fopen("humen.txt", "r");
    if (file == NULL) {
        printf("Ошибка: файл humen.txt не найден!\n");
        return 1;
    }

    // Читаем 4 слова: Имя + Отчество + Фамилия + Год
    for (i = 0; i < COUNT; i++) {
        fscanf(file, "%s", a[i].name);
        fscanf(file, "%s", a[i].patronymic);
        fscanf(file, "%s", a[i].lastname);
        fscanf(file, "%d", &a[i].year);
    }
    fclose(file);

    printf("Загружено %d человек:\n\n", COUNT);
    for (i = 0; i < COUNT; i++) {
        printf("%d. %s %s %s, %d\n", i+1,
               a[i].name, a[i].patronymic, a[i].lastname, a[i].year);
    }

    // Копирование
    for (i = 0; i < COUNT; i++) {
        b[i] = a[i];
    }

    // Сортировка
    for (i = 0; i < COUNT - 1; i++) {
        for (j = 0; j < COUNT - 1 - i; j++) {
            if (b[j].year > b[j+1].year) {
                temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }

    printf("\nПо возрастанию года рождения:\n");
    for (i = 0; i < COUNT; i++) {
        printf("%s %s %s, %d\n",
               b[i].name, b[i].patronymic, b[i].lastname, b[i].year);
    }

    return 0;
}