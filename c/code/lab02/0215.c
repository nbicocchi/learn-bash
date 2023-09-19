#include <stdio.h>

int my_strcmp(const char *s1, const char *s2) {
    int i;

    for (i = 0; s1[i] && s2[i]; i++) {
        if (s1[i] != s2[i]) return 1;
    }
    if (s1[i] != s2[i]) {
        return 1;
    }
    return 0;
}

int main(void) {
    printf("%d\n", my_strcmp("Darma", "Darma"));
    printf("%d\n", my_strcmp("Dharma", "Darma"));
}