#include <stdio.h>
#include <stdlib.h>

void fill_matrix(unsigned rows, unsigned cols, int **m) {
    unsigned i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            m[i][j] = (int) (i * j);
        }
    }
}

void show_matrix(unsigned rows, unsigned cols, int **m) {
    unsigned i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(unsigned rows, unsigned cols, int **m) {
    unsigned i;

    for (i = 0; i < rows; i++) {
        free(m[i]);
    }

    free(m);
}

int **allocate_matrix(unsigned rows, unsigned cols) {
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

#define ROWS 10
#define COLS 10

int main(void) {
    int **m;

    m = allocate_matrix(ROWS, COLS);
    fill_matrix(ROWS, COLS, m);
    show_matrix(ROWS, COLS, m);
    free_matrix(ROWS, COLS, m);
}




