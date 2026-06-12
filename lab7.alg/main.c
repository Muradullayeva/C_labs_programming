#include <stdio.h>
#include <stdlib.h>

// Соответствие символа и 3-битного кода
int encode(char c) {
    switch (c) {
        case 'N': return 0; // 000
        case 'A': return 1; // 001
        case 'C': return 2; // 010
        case 'G': return 4; // 100
        case 'T': return 7; // 111
        default: return -1; // Ошибка (включая \n и прочее)
    }
}

int main(int argc, char *argv[]) {
    char *filename;

    // Если имя файла передано как аргумент - используем его
    // Иначе используем NACGT.txt по умолчанию
    if (argc == 2) {
        filename = argv[1];
    } else {
        filename = "NACGT.txt";
        printf("Using default file: NACGT.txt\n");
    }

    FILE *in = fopen(filename, "r");
    if (!in) {
        perror("Cannot open input file");
        return 1;
    }

    // Открываем выходной бинарный файл
    char outname[256];
    snprintf(outname, sizeof(outname), "%s.bin", filename);
    FILE *out = fopen(outname, "wb");
    if (!out) {
        perror("Cannot create output file");
        fclose(in);
        return 1;
    }

    unsigned long long buffer = 0; // накопитель битов
    int bits_in_buffer = 0;        // сколько битов уже в буфере
    int counts[5] = {0};           // индекс 0:N,1:A,2:C,3:G,4:T
    char ch;
    int total_valid = 0;

    while ((ch = fgetc(in)) != EOF) {
        int code = encode(ch);
        if (code == -1) {
            // Пропускаем всё, кроме A,G,C,T,N (включая \n и прочие символы)
            continue;
        }

        // Подсчёт каждого основания
        switch (ch) {
            case 'N': counts[0]++; break;
            case 'A': counts[1]++; break;
            case 'C': counts[2]++; break;
            case 'G': counts[3]++; break;
            case 'T': counts[4]++; break;
        }
        total_valid++;

        // Добавляем 3 бита в буфер (код уже 0..7)
        buffer = (buffer << 3) | code;
        bits_in_buffer += 3;

        // Если набралось 64 бита (8 байт), записываем в файл
        if (bits_in_buffer >= 64) {
            // Берём старшие 64 бита
            unsigned long long to_write = buffer >> (bits_in_buffer - 64);
            fwrite(&to_write, sizeof(to_write), 1, out);
            // Оставляем в буфере оставшиеся биты
            bits_in_buffer -= 64;
            buffer &= (bits_in_buffer ? ((1ULL << bits_in_buffer) - 1) : 0);
        }
    }

    // Записываем остаток (менее 64 бит), дополняя нулями справа
    if (bits_in_buffer > 0) {
        // Дополняем до 64 битов нулями
        buffer <<= (64 - bits_in_buffer);
        fwrite(&buffer, sizeof(buffer), 1, out);
    }

    fclose(in);
    fclose(out);

    // Вывод статистики
    printf("\n=== STATISTICS ===\n");
    printf("Total valid bases: %d\n", total_valid);
    printf("N (unknown):    %d\n", counts[0]);
    printf("A (adenine):    %d\n", counts[1]);
    printf("C (cytosine):   %d\n", counts[2]);
    printf("G (guanine):    %d\n", counts[3]);
    printf("T (thymine):    %d\n", counts[4]);
    printf("==================\n");
    printf("\nCompressed data written to: %s\n", outname);

    return 0;
}