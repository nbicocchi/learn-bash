#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *source;

    if (argc != 2) {
        fprintf(stdout, "usage: %s filename\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (!(source = fopen(argv[1], "r"))) {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    fseek(source, 0L, SEEK_END);
    fprintf(stdout, "size=%ld bytes\n", ftell(source));
    fclose(source);
    exit(EXIT_SUCCESS);
}
