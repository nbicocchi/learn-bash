#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX 8192

int main(int argc, char *argv[]) {
    FILE *source = stdin;
    char buffer[LINE_MAX];
    int lines;

    if (argc < 2 || argc > 3) {
        fprintf(stdout, "Usage: %s n [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    lines = atoi(argv[1]);
    if (argc == 3) {
        source = fopen(argv[2], "r");
        if (!source) {
            perror("open()");
            exit(EXIT_FAILURE);
        }
    }

    while (((fgets(buffer, LINE_MAX, source)) != NULL) && (lines-- > 0)) {
        fputs(buffer, stdout);
    }

    fclose(source);
    exit(EXIT_SUCCESS);
}