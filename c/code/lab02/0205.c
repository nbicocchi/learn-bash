#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1024

void capitalize(char *dst, const char *src) {
    unsigned long len;

    len = strlen(src);
    if (len > 0) dst[0] = src[0];
    for (unsigned long i = 1; i < len; i++) {
        dst[i] = src[i - 1] == ' ' ? (char) toupper(src[i]) : (char) tolower(src[i]);
    }
    dst[len] = '\0';
}

int main(void) {
    char src[SIZE] = "give a man a fish and you feed him for a day; teach a man to fish and you feed him for a lifetime.";
    char dst[SIZE];

    capitalize(dst, src);
    printf("src=%s\n", src);
    printf("dst=%s\n", dst);
}