#include <stdio.h>

void my_strcpy(char *dst, const char *src) {
    int i = 0;
    for (; src[i]; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
}

int main(void) {
    char str1[] = "Rosso di sera bel tempo si spera...";
    char str2[1024];

    my_strcpy(str2, str1);
    printf("str1=%s\n", str1);
    printf("str2=%s\n", str2);
}