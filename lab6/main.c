#include <stdio.h>

int main() {
    FILE *in = fopen("people.txt", "r");
    FILE *out = fopen("after1980.txt", "w");
    char fam[20], im[20], ot[20];
    int god;

    while (fscanf(in, "%s %s %s %d", fam, im, ot, &god) == 4) {
        if ( god > 1980) {
            fprintf(out, "%s %s %s %d\n", fam, im, ot, god);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}