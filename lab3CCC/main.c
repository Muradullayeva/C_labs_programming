#include <stdio.h>
#include <string.h>

int main() {
    char str[81];
    printf("Введите строку (не более 80 символов): ");
    fgets(str, sizeof(str), stdin);
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    for (int i = 0; str[i]!='\0'; i++) {
        if (str[i] == 'a') {
            str[i] = 'A';
        }else if (str[i] == 'b') {
            str[i] = 'B';
        }
    }
    printf("Резултат: %s\n", str);
    return 0;
}