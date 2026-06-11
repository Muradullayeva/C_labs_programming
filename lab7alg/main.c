#include <stdio.h>
#include <stdlib.h>

// Соответствие символов триадам (3 бита)
// (0 0 0) = N
// (0 0 1) = A
// (0 1 0) = C
// (1 0 0) = G
// (1 1 1) = T
int char_to_bits(char c) {
    switch (c) {
        case 'N': return 0x0; // 000
        case 'A': return 0x1; // 001
        case 'C': return 0x2; // 010
        case 'G': return 0x4; // 100
        case 'T': return 0x7; // 111
        default: return -1;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <имя_файла_с_днк>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Ошибка открытия файла %s\n", argv[1]);
        return 1;
    }

    // Открываем выходной бинарный файл
    FILE *output = fopen("compressed.bin", "wb");
    if (!output) {
        printf("Ошибка создания compressed.bin\n");
        fclose(input);
        return 1;
    }

    unsigned long long buffer = 0;  // накопитель битов
    int bits_in_buffer = 0;         // сколько битов уже в buffer
    unsigned long long counts[5] = {0}; // A, G, C, T, N
    char bases[] = {'A', 'G', 'C', 'T', 'N'};

    char c;
    while ((c = fgetc(input)) != EOF) {
        // Пропускаем символ перевода строки (012 восьмеричное = \n)
        if (c == '\n') continue;

        int bits = char_to_bits(c);
        if (bits == -1) continue; // пропускаем неизвестные символы

        // Подсчёт оснований
        switch (c) {
            case 'A': counts[0]++; break;
            case 'G': counts[1]++; break;
            case 'C': counts[2]++; break;
            case 'T': counts[3]++; break;
            case 'N': counts[4]++; break;
        }

        // Кладём 3 бита в буфер
        buffer = (buffer << 3) | bits;
        bits_in_buffer += 3;

        // Когда набралось 64 бита (8 байт) — записываем в файл
        if (bits_in_buffer >= 64) {
            bits_in_buffer -= 64;
            // Извлекаем старшие 64 бита
            unsigned long long to_write = buffer >> bits_in_buffer;
            fwrite(&to_write, sizeof(to_write), 1, output);
            // Оставляем остаток
            buffer = buffer & ((1ULL << bits_in_buffer) - 1);
        }
    }

    // Записываем остаток (если есть)
    if (bits_in_buffer > 0) {
        buffer <<= (64 - bits_in_buffer); // выравнивание вправо
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    fclose(input);
    fclose(output);

    // Выводим подсчёт оснований в десятичном виде
    printf("Результаты подсчёта азотистых оснований:\n");
    printf("Аденин (A): %llu\n", counts[0]);
    printf("Гуанин (G): %llu\n", counts[1]);
    printf("Цитозин (C): %llu\n", counts[2]);
    printf("Тимин (T): %llu\n", counts[3]);
    printf("Неопределённый (N): %llu\n", counts[4]);

    printf("\nСжатые данные записаны в compressed.bin\n");
    return 0;
}