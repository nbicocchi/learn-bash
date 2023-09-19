#include <stdio.h>
#include <string.h>

#define SIZE 128

void reverses(char *dst, const char *src) {
    unsigned long len;

    len = strlen(src);
    for (unsigned long i = 0; i < len; i++) {
        dst[len - 1 - i] = src[i];
    }
    dst[len] = '\0';
}

int main(void) {
    char src[SIZE] = "nicola";
    char dst[SIZE];

    reverses(dst, src);
    printf("src=%s\n", src);
    printf("dst=%s\n", dst);
}