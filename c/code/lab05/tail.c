#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 8192

struct buffer {
    int n;
    char **lines;
};

struct buffer *allocate_buffer(int n) {
    struct buffer *buffer = malloc(sizeof(*buffer));
    buffer->n = n;
    buffer->lines = calloc((unsigned long)n, sizeof(*(buffer->lines)));
    return buffer;
}

void add_line_to_buffer(struct buffer *buffer, char *line) {
    int i;
    // free the memory of the oldest line (index=0)
    if (buffer->lines[0]) {
        free(buffer->lines[0]);
    }

    // shifts all lines to free up the space for the newest line (index = n - 1)
    for (i = 0; i < buffer->n - 1; i++) {
        buffer->lines[i] = buffer->lines[i+1];
    }

    // add the newest line
    buffer->lines[buffer->n - 1] = malloc(strlen(line) + 1);
    strcpy(buffer->lines[buffer->n - 1], line);
}

void show_buffer(struct buffer *buffer) {
    int i;
    for (i = 0; i < buffer->n; i++) {
        if (buffer->lines[i]) {
            fprintf(stdout, "%s", buffer->lines[i]);
        }
    }
}

void free_buffer(struct buffer *buffer) {
    int i;
    for (i = 0; i < buffer->n; i++) {
        if (buffer->lines[i]) {
            free(buffer->lines[i]);
        }
    }
    free(buffer);
}

int main(int argc, char *argv[]) {
    FILE *source = stdin;
    struct buffer *buffer;
    char line[LINE_MAX];

    if (argc < 2 || argc > 3) {
        fprintf(stdout, "Usage: %s n [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        source = fopen(argv[2], "r");
        if (!source) {
            perror("open()");
            exit(EXIT_FAILURE);
        }
    }

    buffer = allocate_buffer(atoi(argv[1]));
    while ((fgets(line, LINE_MAX, source)) != NULL) {
        add_line_to_buffer(buffer, line);
    }
    show_buffer(buffer);
    free_buffer(buffer);

    fclose(source);
    exit(EXIT_SUCCESS);
}