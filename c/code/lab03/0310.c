#include <stdio.h>

#define ROWS 3
#define COLS 3

void fill_matrix(unsigned rows, unsigned cols, int m[][cols]) {
    unsigned i, j, count = 1;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            m[i][j] = (int)count++;
        }
    }
}

void show_addresses(unsigned rows, unsigned cols, int m[][cols]) {
    unsigned i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%p -> %d\n", &m[i][j], m[i][j]);
        }
        printf("\n");
    }
}

/*
 * If this function correctly prints the matrix, its elements have to be contiguous in memory
 */
void show_matrix(unsigned rows, unsigned cols, int *m) {
    unsigned i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d", m[i * cols + j]);
        }
        printf("\n");
    }
}

int main(void) {
    int v[ROWS][COLS];

    fill_matrix(ROWS, COLS, v);
    show_matrix(ROWS, COLS, (int *)v);
    show_addresses(ROWS, COLS, v);
}




