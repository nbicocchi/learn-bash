#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 1024

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

int main(int argc, char *argv[]) {
    int i;
    FILE *source;

    if (argc <= 1) {
        copy_by_byte_blocks(stdin, stdout);
    } else {
        for (i = 1; i < argc; i++) {
            if (!(source = fopen(argv[i], "rb"))) {
                perror("open()");
                exit(EXIT_FAILURE);
            }
            copy_by_byte_blocks(source, stdout);
            fclose(source);
        }
    }
    exit(EXIT_SUCCESS);
}
