#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 16

int copy_by_byte_blocks(FILE *source, FILE *target) {
    size_t nread, nwrite;
    unsigned char buffer[BUFFER_SIZE];
    do {
        nread = fread(buffer, 1, sizeof(buffer), source);
        nwrite = 0;
        if (nread) {
            nwrite = fwrite(buffer, 1, nread, target);
        }
    } while ((nread > 0) && (nread == nwrite));

    if (nread != nwrite) return FALSE;
    return TRUE;
}

int main() {
    char source_file[] = "../examples/example.c";
    char target_file[] = "example.c";
    char cwd[PATH_MAX];
    FILE *source, *target;

    /* show working directory */
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }

    source = fopen(source_file, "rb");
    if (!source) {
        perror(source_file);
        exit(EXIT_FAILURE);
    }

    target = fopen(target_file, "wb");
    if (!target) {
        fclose(source);
        perror(target_file);
        exit(EXIT_FAILURE);
    }

    if (!copy_by_byte_blocks(source, target)) {
        perror("opy_by_byte_blocks()");
        exit(EXIT_FAILURE);
    }

    printf("[OK] %s -> %s\n", source_file, target_file);

    fclose(source);
    fclose(target);
    exit(EXIT_SUCCESS);
}