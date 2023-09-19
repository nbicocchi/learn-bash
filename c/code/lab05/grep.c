#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 8192

int main(int argc, char *argv[]) {
    FILE *source = stdin;
    char buffer[LINE_MAX];

    if (argc < 2 || argc > 3) {
        fprintf(stdout, "Usage: %s string [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        source = fopen(argv[2], "r");
        if (!source) {
            perror("open()");
            exit(EXIT_FAILURE);
        }
    }

    while ((fgets(buffer, LINE_MAX, source)) != NULL) {
        if (strstr(buffer, argv[1])) {
            fputs(buffer, stdout);
        }
    }

    fclose(source);
    exit(EXIT_SUCCESS);
}