#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strdup_inverted(const char *s) {
    unsigned long i, len;
    char *s_inv;

    len = strlen(s);
    s_inv = calloc((len + 1), sizeof(*s_inv));
    for (i = 0; i < len; i++) {
        s_inv[len - i - 1] = s[i];
    }
    return s_inv;
}

char **invert_all(char *strings[]) {
    unsigned long i, n_strings;
    char **strings_inverted;

    for (n_strings = 0; strings[n_strings]; n_strings++);

    strings_inverted = calloc(n_strings + 1, sizeof(*strings_inverted));
    for (i = 0; i < n_strings; i++) {
        strings_inverted[i] = strdup_inverted(strings[n_strings - i - 1]);
    }
    return strings_inverted;
}

int main(void) {
    char **p, **strings_inverted;
    char *strings[] = {
            "monday",
            "tuesday",
            "wednesday",
            "thursday",
            "friday",
            "saturday",
            "sunday",
            NULL,
    };

    strings_inverted = invert_all(strings);

    for (p = strings; *p; p++) {
        printf("%s\n", *p);
    }

    printf("\n");

    for (p = strings_inverted; *p; p++) {
        printf("%s\n", *p);
    }
}