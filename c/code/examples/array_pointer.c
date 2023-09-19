#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *allocate_matrix_single(int rows, int cols) {
    int *m;

    m = malloc((unsigned long) (rows * cols) * sizeof(*m));
    return m;
}

int **allocate_matrix_double(unsigned rows, unsigned cols) {
    int **m;
    unsigned i;

    m = malloc((unsigned long) (rows) * sizeof(*m));
    if (m == NULL) return NULL;

    for (i = 0; i < rows; i++) {
        m[i] = malloc((unsigned long) (cols) * sizeof(**m));
        if (m[i] == NULL) return NULL;
    }

    return m;
}

void fill_matrix_static(unsigned rows, unsigned cols, int m[][cols]) {
    unsigned i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            m[i][j] = (int) ((i + 1) * (j + 1));
        }
    }
}

void fill_matrix_single(unsigned rows, unsigned cols, int *m) {
    unsigned i, j, offset;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            offset = i * cols + j;
            m[offset] = (int) ((i + 1) * (j + 1));
        }
    }
}

void fill_matrix_double(unsigned rows, unsigned cols, int **m) {
    unsigned i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            m[i][j] = (int) ((i + 1) * (j + 1));
        }
    }
}

void show_matrix_static(unsigned rows, unsigned cols, int m[][cols]) {
    unsigned i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

void show_matrix_single(unsigned rows, unsigned cols, int *m) {
    unsigned i, j, offset;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            offset = i * cols + j;
            printf("%4d", m[offset]);
        }
        printf("\n");
    }
}

void show_matrix_double(unsigned rows, unsigned cols, int **m) {
    unsigned i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

#define ROWS 3
#define COLS 3

int main(void) {
    //int v[ROWS][COLS];
    //fill_matrix_static(ROWS, COLS, v);

    //int *v = allocate_matrix_single(ROWS, COLS);
    //fill_matrix_single(ROWS, COLS, v);

    int **v = allocate_matrix_double(ROWS, COLS);
    fill_matrix_double(ROWS, COLS, v);

    show_matrix_static(ROWS, COLS, v);
    show_matrix_single(ROWS, COLS, v);
}
