#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/check.h>

#define _USE_MATH_DEFINES

void calculation(
        char* a,
        float* xx,
        float* yy,
        float* RR,
        float* x,
        float* y,
        float* R,
        int i)
{
    char ignore[] = "circle( ,)";
    float per, area;

    *xx = atof(strtok(a, ignore));
    *yy = atof(strtok(NULL, ignore));
    *RR = atof(strtok(NULL, ignore));

    x[i] = *xx;
    y[i] = *yy;
    R[i] = *R;

    per = 2 * M_PI * *RR;
    area = M_PI * *RR * *RR;

    printf("x = %.2f   y = %.2f   R = %.2f\n", *xx, *yy, *RR);
    printf("perimetr = %.2f\narea = %.2f\n\n", per, area);
}

void intersections(float* x, float* y, float* R, int number)
{
    int inter;
    printf("\nIntersects:");
    for (int i = 0; i < number; i++) {
        inter = 0;
        printf("\n circle %d intersects: ", i + 1);
        for (int j = 0; j < number; j++) {
            double distance = sqrt(pow(x[j] - x[i], 2) + pow(y[j] - y[i], 2));

            if (distance == 0 && R[i] == R[j] && j != i) {
                inter++;
                printf("%d  ", j + 1);
            }
            if (R[i] + R[j] >= distance && R[i] + distance >= R[j]
                && distance + R[j] >= R[i] && j != i) {
                inter++;
                printf("%d  ", j + 1);
            }
        }
    }
    if (inter == 0) {
        printf("no intersects");
    }
    printf("\n");
}

int main()
{
    FILE* file1;
    FILE* file;

    file1 = fopen("geometry.txt", "r");

    if (!file1) {
        printf("Error: can't open file. Check name of file\n");
        return 0;
    }

    int l = 0, c = 0, e = 0, error = 0, i = 0;

    float* x = (float*)malloc(i * sizeof(float));
    float* y = (float*)malloc(i * sizeof(float));
    float* R = (float*)malloc(i * sizeof(float));

    while (1) {
        e = fgetc(file1);
        if (e == EOF) {
            if (feof(file1) != 0) {
                break;
            }
        }
        c++;
    }
    l = c;
    fclose(file1);

    int number = 1;
    char a[l], b[6] = "circle";
    file = fopen("geometry.txt", "r");

    while (fgets(a, l + 1, file)) {
        printf("%d. %s", number, a);

        int open_bracket = check_str(a, b, &error);

        int close_bracket = check_find_close_bracket(a, &l);

        int first_num_elm = check_first_num(a, &open_bracket, &error);

        int second_num_elm = check_second_num(a, &first_num_elm, &error);

        int last_num_elm
                = check_last_num(a, &second_num_elm, &close_bracket, &error);

        close_bracket = check_close_bracket(a, &l, &last_num_elm, &error);

        check_unexp_token(a, &l, &close_bracket, &error);

        if (error == 0) {
            float xx = 0, yy = 0, RR = 0;
            calculation(a, &xx, &yy, &RR, x, y, R, i);
            i++;
        }

        error = 0;
        number++;
    }

    intersections(x, y, R, i);
    free(x);
    free(y);
    free(R);

    return 0;
}
