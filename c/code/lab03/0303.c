#include <stdio.h>

void tabula_recta(char t[][26]) {
    int shift, i;
    for (shift = 0; shift < 26; shift++) {
        for (i = 0; i < 26; i++) {
            t[shift][i] =
                    'a' + shift + i <= 'z' ? (char) ('a' + shift + i) : (char) ('a' + shift + i - ('z' - 'a') - 1);
        }
    }
}

#define SIZE 26

int main(void) {
    int i, j;
    char t[SIZE][SIZE];

    tabula_recta(t);

    /* show tabula recta */
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%2c", t[i][j]);
        }
        printf("\n");
    }
}