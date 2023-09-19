#include <stdio.h>
#include <stdlib.h>

void fill_matrix(unsigned rows, unsigned cols, int *m) {
    unsigned i, j, offset;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            offset = i * cols + j;
            m[offset] = (int)(i * j);
        }
    }
}

void show_matrix(unsigned rows, unsigned cols, int *m) {
    unsigned i, j, offset;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            offset = i * cols + j;
            printf("%4d", m[offset]);
        }
        printf("\n");
    }
}

void free_matrix(int *m) {
    free(m);
}

int *allocate_matrix(int rows, int cols) {
    int *m;

    m = malloc((unsigned long) (rows * cols) * sizeof(*m));
    return m;
}

#define ROWS 10
#define COLS 10

int main(void) {
    int *m;

    m = allocate_matrix(ROWS, COLS);
    fill_matrix(ROWS, COLS, m);
    show_matrix(ROWS, COLS, m);
    free_matrix(m);
}




