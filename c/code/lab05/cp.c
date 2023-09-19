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
    FILE *source, *target;

    if (argc != 3) {
        fprintf(stdout, "Usage: %s src dst\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!(source = fopen(argv[1], "r"))) {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    if (!(target = fopen(argv[2], "w"))) {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    copy_by_byte_blocks(source, target);

    fclose(source);
    fclose(target);

    exit(EXIT_SUCCESS);
}
