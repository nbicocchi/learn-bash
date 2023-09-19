#include <stdio.h>
#include <stdlib.h>

int main() {
    char target_file[] = "print_scanf_test.txt";
    char str[] = "Hello World!";
    char buffer_long[1024];
    char buffer_short[16];
    FILE *target;

    target = fopen(target_file, "w");
    if (!target) {
        perror(target_file);
        exit(EXIT_FAILURE);
    }

    /* standard printf */
    printf("printf: %s\n", str);

    /* file printf */
    fprintf(stdout, "fprintf: %s\n", str);

    /* file printf */
    fprintf(target, "fprintf: %s\n", str);
    fclose(target);

    /* string printf */
    snprintf(buffer_long, 1024, "sprintf: %s", str);
    snprintf(buffer_short, 16, "sprintf: %s", str);

    fprintf(stdout, "%s\n", buffer_long);
    fprintf(stdout, "%s\n", buffer_short);

    exit(EXIT_SUCCESS);
}