#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read(FILE *source) {
    char buffer[10];

    memset(buffer, 0, sizeof(buffer));
    fread(buffer, 1, sizeof(buffer), source);
    fprintf(stdout, "%s\n", buffer);
    fprintf(stdout, "ftell(): %ld\n", ftell(source));
}

int main() {
    char source_file[] = "../examples/printf_types.c";
    FILE *source;

    source = fopen(source_file, "rb");
    if (!source) {
        perror(source_file);
        exit(EXIT_FAILURE);
    }

    fseek(source, 0L, SEEK_SET);
    read(source);

    fseek(source, 1L, SEEK_SET);
    read(source);

    fseek(source, 1L, SEEK_CUR);
    read(source);

    fseek(source, -20L, SEEK_END);
    read(source);

    rewind(source);
    read(source);

    fclose(source);
    exit(EXIT_SUCCESS);
}