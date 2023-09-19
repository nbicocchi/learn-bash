#include <stdio.h>
#include <stdlib.h>

int *reversei(const int *src, unsigned size) {
    unsigned i;
    int *dst;

    dst = malloc(size * sizeof(*dst));
    if (!dst) return NULL;

    for (i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
    return dst;
}

#define SIZE 9

int main(void) {
    int src[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *dst;
    int i;

    dst = reversei(src, SIZE);

    for (i = 0; i < SIZE; i++) {
        printf("%d ", dst[i]);
    }
}