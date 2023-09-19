#include <stdio.h>

void my_strcat(char *dst, const char *src) {
    int i, j;

    for (i = 0; dst[i]; i++);

    for (j = 0; src[j]; j++, i++) {
        dst[i] = src[j];
    }
    dst[i] = '\0';
}

int main(void) {
    char str1[1024] = "Rosso di sera ";
    char str2[] = "bel tempo si spera...";

    my_strcat(str1, str2);
    printf("str1=%s\n", str1);
    printf("str2=%s\n", str2);
}