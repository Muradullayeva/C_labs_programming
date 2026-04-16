#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    char lastname[20];
    int year;

}humen;

int main() {
    humen a[4], b[4];
    int i, j;
    humen temp;

    for (i = 0; i < 4; i++) {
        printf("Человек %d:\n ", i + 1);
        printf("Имя: "); scanf("%s", a[i].name);
        printf("Фамилия: "); scanf("%s", a[i].lastname);
        printf("Год: "); scanf("%d", &a[i].year);
    }

    for (i = 0; i < 4; i++) {
        b[i] = a[i];
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (b[j].year > b[i].year) {
                temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }

    printf ("По возрастанию года рождения:\n");
    for (i = 0; i < 4; i++) {
        printf("%s %s, %d\n", b[i].name, b[i].lastname, b[i].year);
    }
    return 0;
}