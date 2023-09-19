#include <stdio.h>

long matrix_edge(unsigned rows, unsigned cols, int m[][cols]) {
    int i;
    long sum = 0;

    /* first row */
    for (i = 0; i < cols; i++) {
        sum += m[0][i];
    }

    /* last row */
    for (i = 0; i < cols; i++) {
        sum += m[rows - 1][i];
    }

    /* first column */
    for (i = 1; i < rows - 1; i++) {
        sum += m[i][0];
    }

    /* last column */
    for (i = 1; i < rows - 1; i++) {
        sum += m[i][cols - 1];
    }

    return sum;
}

int main(void) {
    int m[4][4] = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16},
    };

    printf("matrix edge sum = %ld\n", matrix_edge(4, 4, m));
}