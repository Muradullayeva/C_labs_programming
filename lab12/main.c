#include <stdio.h>
#include <time.h>
#include <string.h>

int is_leap (int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month (int month, int year) {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap(year)) return 29 ;
    return days[month - 1];
}

int get_weekday (int year, int month, int day) {
    struct tm t = {0};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_isdst = -1;
    mktime(&t);
    return t.tm_wday;
}

void print_month (int year, int month){
    // массив из символьных элементов
    const char *month_names[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    printf("\n %s %d\n", month_names[month-1], year);
    printf(" Mo Tu We Th Fr St Sn \n");
    int wday = get_weekday(year, month, 1);
    int offset = (wday + 6)%7;
    for (int i = 1; i <= offset; i++) {
        printf("   ");
    }
    int days = days_in_month(month, year);
    for (int d = 1; d <= days; d++) {
        printf("%2d ", d);
        if ((offset + d) % 7 == 0) {
            printf("\n");
        }
    }
    if ((offset + days) %7!= 0) {
        printf("\n");
    }
}

void print_year (int year) {
    for (int m = 1; m <= 12; m++) {
        print_month(year, m);
    }
}

int main() {
    char input[30];
    printf("Введите дату (гггг.мм.дд., ггггг.мм, ггггг. или now): ");
    fgets(input, sizeof(input), stdin);
    input [strcspn(input, "\n")] = 0;
    if (strcmp(input, "now") == 0) {
        time_t t = time(NULL);
        struct tm *now = localtime(&t);
        int year = now->tm_year + 1900;
        int month = now->tm_mon + 1;
        int day = now->tm_mday;
        int wday = now->tm_wday;
        const char *weekdays[]= {" Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        printf(" Текущая дата: %04d - %02d - %02d\n", year, month, day);
        printf("День недели: %s\n", weekdays[wday]);
        return 0;
    }

    int year, month, day;
    int dots = 0;
    for (int i = 0; input[i]; i++)
        if (input[i] == '.') dots++;
    if (dots == 2) {
        sscanf (input, "%d.%d.%d", &year, &month, &day);
        int wday = get_weekday(year, month, day);
        const char *weekdays[]= {" Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        printf("%04d-%02d-%02d - %s\n", year, month, day, weekdays[wday]);
    }else if (dots == 1) {
        sscanf (input, "%d.%d", &year, &month);
        print_month(year, month);
    }else if (dots == 0) {
        sscanf (input, "%d", &year);
        print_year(year);
    }else {
        printf("Неверный формат\n");
    }
    return 0;
}