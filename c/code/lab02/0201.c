#include <stdio.h>

#define SIZE 9

void reversei(int *dst, const int *src, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}

void show_array(int *src, unsigned long size) {
    for (unsigned long i = 0; i < size; i++) {
        printf("%3d", src[i]);
    }
    printf("\n");
}

int main(void) {
    int src[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dst[SIZE];

    reversei(dst, src, SIZE);
    show_array(src, SIZE);
    show_array(dst, SIZE);
}