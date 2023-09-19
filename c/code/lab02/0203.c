#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 128

void rotate(char *dst, const char *src, char shift) {
    unsigned long len;

    len = strlen(src);
    for (unsigned long i = 0; i < len; i++) {
        if (islower(src[i])) {
            dst[i] = src[i] + shift <= 'z' ? src[i] + shift : src[i] + shift - ('z' - 'a') - 1;
        } else if (isupper(src[i])) {
            dst[i] = src[i] + shift <= 'Z' ? src[i] + shift : src[i] + shift - ('Z' - 'A') - 1;
        } else {
            dst[i] = src[i];
        }

    }
    dst[len] = '\0';
}

int main(void) {
    char src[SIZE] = "nicolaz";
    char dst[SIZE];

    rotate(dst, src, 2);
    printf("src=%s\n", src);
    printf("dst=%s\n", dst);
}