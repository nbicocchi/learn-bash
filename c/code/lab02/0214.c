#include <stdio.h>

unsigned my_strlen(const char *src) {
    unsigned i = 0;
    for (; src[i]; i++);
    return i;
}

int main(void) {
    printf("%d\n", my_strlen("Rosso di sera bel tempo si spera..."));
}