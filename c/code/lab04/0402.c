#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverses(const char *src) {
    unsigned long i, size;
    char *dst;

    size = strlen(src);
    dst = malloc(size * sizeof(*dst));
    if (!dst) return NULL;

    for (i = 0; i < size; i++) {
        dst[size - 1 - i] = src[i];
    }
    dst[size] = '\0';
    return dst;
}

#define SIZE 128

int main(void) {
    char src[SIZE] = "Rosso di sera, bel tempo si spera";
    char *dst;

    dst = reverses(src);
    printf("%s\n", dst);
}