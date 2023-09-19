#include <stdio.h>

void diagonals(int *rdp, int *rds, unsigned cols, const int m[][cols]) {
    unsigned row;
    for (row = 0; row < cols; row++) {
        rdp[row] = m[row][row];
        rds[row] = m[cols - 1 - row][row];
    }
}

#define SIZE 4

int main(void) {
    int i;
    int rdp[SIZE], rds[SIZE];
    int m[SIZE][SIZE] = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16},
    };

    diagonals(rdp, rds, SIZE, m);

    /* show rdp */
    printf("\nrdp = ");
    for (i = 0; i < SIZE; i++) {
        printf("%5d", rdp[i]);
    }

    /* show rds */
    printf("\nrds = ");
    for (i = 0; i < SIZE; i++) {
        printf("%5d", rds[i]);
    }
}