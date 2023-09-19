#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *source = stdin;
    int c, bytes = 0, lines = 0;

    if (argc > 2) {
        fprintf(stdout, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        source = fopen(argv[1], "r");
        if (!source) {
            perror("open()");
            exit(EXIT_FAILURE);
        }
    }

    while ((c = fgetc(source)) != EOF) {
        bytes++;
        if (c == '\n') lines++;
    }

    fprintf(stdout, "bytes=%d, lines=%d\n", bytes, lines);

    fclose(source);
    exit(EXIT_SUCCESS);
}