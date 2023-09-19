#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void copy_by_char(FILE *source, FILE *target) {
    int ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, target);
    }
}

void copy_by_line(FILE *source, FILE *target) {
    char buffer[LINE_MAX];
    while ((fgets(buffer, LINE_MAX, source)) != NULL) {
        fputs(buffer, target);
    }
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

    source = fopen(source_file, "r");
    if (!source) {
        perror(source_file);
        exit(EXIT_FAILURE);
    }

    target = fopen(target_file, "w");
    if (!target) {
        fclose(source);
        perror(target_file);
        exit(EXIT_FAILURE);
    }

    copy_by_line(source, target);
    //copy_by_char(source, target);

    printf("[OK] %s -> %s\n", source_file, target_file);

    fclose(source);
    fclose(target);
    exit(EXIT_SUCCESS);
}