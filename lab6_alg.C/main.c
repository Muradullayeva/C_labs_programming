#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point {
    double x;
    double y;
    int num;
} POINT;

POINT p[100000];
int hull[100000];
int hull_count = 0;
int n = 0;

// Сравнение для qsort (сортировка по X, затем по Y)
int cmp_x(const void *a, const void *b) {
    POINT *pa = (POINT *)a;
    POINT *pb = (POINT *)b;
    if (pa->x < pb->x) return -1;
    if (pa->x > pb->x) return 1;
    if (pa->y < pb->y) return -1;
    if (pa->y > pb->y) return 1;
    return 0;
}

// Ориентация: >0 – точка c слева от вектора ab, <0 – справа
double is_right(POINT a, POINT b, POINT c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Расстояние от точки c до прямой ab
double distance(POINT a, POINT b, POINT c) {
    double area = fabs(is_right(a, b, c));
    double ab = hypot(b.x - a.x, b.y - a.y);
    return area / ab;
}

// Поиск самой удалённой точки с заданной стороны (side = +1 или -1)
int find_farthest(POINT a, POINT b, int start, int end, int side) {
    int farthest = -1;
    double max_dist = -1;
    for (int i = start; i <= end; i++) {
        double sign = is_right(a, b, p[i]);
        if (side * sign > 0) {
            double dist = distance(a, b, p[i]);
            if (dist > max_dist) {
                max_dist = dist;
                farthest = i;
            }
        }
    }
    return farthest;
}

// Рекурсивная часть QuickHull
void quick_hull(POINT a, POINT b, int start, int end, int side) {
    if (start > end) return;

    int farthest = find_farthest(a, b, start, end, side);
    if (farthest == -1) return;

    hull[hull_count++] = p[farthest].num;

    // Динамические массивы для разделения точек
    POINT *left_temp = (POINT*)malloc((end - start + 1) * sizeof(POINT));
    POINT *right_temp = (POINT*)malloc((end - start + 1) * sizeof(POINT));
    if (!left_temp || !right_temp) {
        printf("Memory allocation error\n");
        exit(1);
    }

    int left_count = 0, right_count = 0;
    for (int i = start; i <= end; i++) {
        if (i == farthest) continue;
        if (is_right(a, p[farthest], p[i]) > 0)
            left_temp[left_count++] = p[i];
        if (is_right(p[farthest], b, p[i]) > 0)
            right_temp[right_count++] = p[i];
    }

    // Перезаписываем исходный диапазон: сначала левые, потом правые
    int idx = start;
    for (int i = 0; i < left_count; i++)
        p[idx++] = left_temp[i];
    int left_end = idx - 1;
    for (int i = 0; i < right_count; i++)
        p[idx++] = right_temp[i];
    int right_end = idx - 1;

    free(left_temp);
    free(right_temp);

    // Рекурсивно строим оболочку для двух новых рёбер (с тем же side)
    quick_hull(a, p[farthest], start, left_end, side);
    quick_hull(p[farthest], b, start + left_count, right_end, side);
}

int main() {
    FILE *In, *Out;
    char filename[] = "IN.txt";  // Имя файла в папке с программой

    // Открываем входной файл для чтения
    In = fopen(filename, "r");
    if (In == NULL) {
        printf("Error: Cannot open file '%s' in current directory\n", filename);
        printf("Make sure the file exists in the same folder as the program\n");
        return 1;
    }

    // Чтение точек
    n = 0;
    int num;
    double x, y;
    while (fscanf(In, "%d%lf%lf", &num, &x, &y) == 3) {
        if (n >= 100000) break;
        p[n].num = num;
        p[n].x = x;
        p[n].y = y;
        n++;
    }
    fclose(In);

    printf("Read %d points from file '%s'\n", n, filename);

    if (n < 3) {
        printf("Error: Need at least 3 points (only %d points read)\n", n);
        return 1;
    }

    // Сортировка по X
    qsort(p, n, sizeof(POINT), cmp_x);
    printf("Points sorted by X coordinate\n");

    int leftmost = 0;
    int rightmost = n - 1;

    hull_count = 0;
    hull[hull_count++] = p[leftmost].num;
    hull[hull_count++] = p[rightmost].num;

    // Разделяем точки на верхние и нижние относительно прямой (leftmost - rightmost)
    POINT *upper = (POINT*)malloc(n * sizeof(POINT));
    POINT *lower = (POINT*)malloc(n * sizeof(POINT));
    int upper_count = 0, lower_count = 0;

    for (int i = 1; i < n - 1; i++) {
        double sign = is_right(p[leftmost], p[rightmost], p[i]);
        if (sign > 0)
            upper[upper_count++] = p[i];
        else if (sign < 0)
            lower[lower_count++] = p[i];
    }

    printf("Upper points: %d, Lower points: %d\n", upper_count, lower_count);

    // Копируем обратно в p: сначала верхние, потом нижние
    int idx = 1;
    for (int i = 0; i < upper_count; i++)
        p[idx++] = upper[i];
    int upper_end = idx - 1;
    for (int i = 0; i < lower_count; i++)
        p[idx++] = lower[i];
    int lower_end = idx - 1;

    free(upper);
    free(lower);

    // Рекурсивное построение выпуклой оболочки
    if (upper_count > 0)
        quick_hull(p[leftmost], p[rightmost], 1, upper_end, 1);   // верхняя часть: side = +1

    if (lower_count > 0)
        quick_hull(p[leftmost], p[rightmost], upper_end + 1, lower_end, -1); // нижняя часть: side = -1

    // Открываем ТОТ ЖЕ файл для записи (перезапись)
    Out = fopen(filename, "w");
    if (Out == NULL) {
        printf("Error: Cannot open file '%s' for writing\n", filename);
        return 1;
    }

    // Записываем результат
    fprintf(Out, "Convex hull (%d points):\n", hull_count);
    for (int i = 0; i < hull_count; i++) {
        fprintf(Out, "%d ", hull[i]);
        if ((i + 1) % 10 == 0) fprintf(Out, "\n");
    }
    fprintf(Out, "\n");

    fclose(Out);

    // Вывод результата на экран
    printf("\n=== RESULT ===\n");
    printf("Convex hull (%d points): ", hull_count);
    for (int i = 0; i < hull_count; i++) {
        printf("%d ", hull[i]);
    }
    printf("\n");
    printf("Result written to file '%s'\n", filename);
    printf("Original data has been replaced with hull points\n");

    return 0;
}