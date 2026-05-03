#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int birth_year;
    char gender [10];
    float height;
}person;

int sort_fields[10];
int sort_fields_count=0;

int compare_people (const void * a, const void * b) {
    person * p1 = ( person *) a;
    person * p2 = (person *) b;

    for (int i=0; i < sort_fields_count; i++) {
        int field=sort_fields[i];
        int cmp=0;

        switch (field) {
            case 1:
                cmp=strcmp(p1->name, p2->name);
                break;
            case 2:
                if (p1->birth_year < p2->birth_year) cmp=-1;
                else if (p1->birth_year > p2->birth_year) cmp=1;
                break;
            case 3:
                cmp=strcmp(p1->gender, p2->gender);
                break;
            case 4:
                if (p1->height < p2->height) cmp=-1;
                else if (p1->height > p2->height) cmp=1;
                break;
        }
        if (cmp!=0) return cmp;
    }
    return 0;
}

int main() {
    FILE *f = fopen("people.txt", "r");
    person people [100];
    int count=0;
    char lastName[30], firstName[30];
    while (fscanf (f, " %s %s %d %s %f", lastName, firstName, & people [count].birth_year, people[count].gender, & people [count].height) == 5) {
        sprintf (people [count].name, "%s %s", lastName, firstName);
        count++;
    }
    fclose(f);
    printf("доступные поля для соримровки: \n1-имя/фамилия \n2-год рождения \n3-пол \n4-рост\n");
    printf(" Введите номера полей через пробел. Для завершения введите 0.\n");
    sort_fields_count=0;
    int input;
    while (scanf("%d", & input)==1 && input!=0 && sort_fields_count < 10){
        sort_fields[sort_fields_count++] = input;
    }
    qsort(people, count, sizeof(person), compare_people);

    FILE *out = fopen("sorted_people.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf (out, "%-20s %4d %s %.2f\n", people[i].name, people[i].birth_year, people[i].gender, people[i].height );
    }
    fclose(out);
    printf("\n Результаты сортировки записаны в файл sorted_people.txt, проверяйте файл!");
    return 0;
}