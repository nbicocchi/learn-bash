#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    FILE *f1, *f2;
    char c1, c2;
    unsigned long r1, r2;
    int byte_counter = 0, line_counter = 0;

    if (argc != 3) {
        fprintf(stdout, "usage: %s file1 file2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!(f1 = fopen(argv[1], "r"))) {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    if (!(f2 = fopen(argv[2], "r"))) {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    do {
        r1 = fread(&c1, 1, 1, f1);
        r2 = fread(&c2, 1, 1, f2);

        byte_counter++;

        if (r1 > 0 && r2 == 0) {
            fprintf(stdout, "%s longer than %s\n", argv[1], argv[2]);
            break;
        }

        if (r1 == 0 && r2 < 0) {
            fprintf(stdout, "%s longer than %s\n", argv[2], argv[1]);
            break;
        }

        if (c1 != c2) {
            fprintf(stdout, "difference @byte %d, @line %d\n", byte_counter, line_counter);
            break;
        }

        if (c1 == '\n') {
            line_counter++;
        }

        if (r1 == 0 && r2 == 0) {
            fprintf(stdout, "%s equals %s\n", argv[1], argv[2]);
            break;
        }
    } while (TRUE);

    fclose(f1);
    fclose(f2);
    exit(EXIT_SUCCESS);
}
