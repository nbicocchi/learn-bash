#include <stdio.h>

#define SIZE 10

void trova_max(int *rmax, const int *values, unsigned size) {
    int max = values[0];

    for (unsigned i = 0; i < size; i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    *rmax = max;
}

int main(void) {
    int rmax;
    int src[] = {11, 33, 44, 32, 56, 65, 94, 23, 12, 73};

    trova_max(&rmax, src, SIZE);
    printf("rmax=%d\n", rmax);
}