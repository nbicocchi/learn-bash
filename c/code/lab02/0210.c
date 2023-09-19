#include <stdio.h>

#define SIZE 10

void trova_minmax(int *rmin, int *rmax, const int *values, unsigned size) {
    int max = values[0];
    int min = values[0];

    for (unsigned i = 0; i < size; i++) {
        if (values[i] > max) {
            max = values[i];
        }
        if (values[i] < min) {
            min = values[i];
        }
    }
    *rmax = max;
    *rmin = min;
}

int main(void) {
    int rmax, rmin;
    int src[] = {11, 33, 44, 32, 56, 65, 94, 23, 12, 73};

    trova_minmax(&rmin, &rmax, src, SIZE);
    printf("rmin=%d\n", rmin);
    printf("rmax=%d\n", rmax);
}