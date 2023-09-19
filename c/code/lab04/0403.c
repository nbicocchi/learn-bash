#include <stdio.h>
#include <stdlib.h>

/*
 * 1. La funzione main dichiara la variabile int *dst.
 *
 * 2. La funzione merge deve scrivere all'interno di quella variabile l'indirizzo
 * del buffer allocato dinamicamente al suo interno.
 *
 * 3. Se la funzione merge ricevesse una COPIA di dst non potrebbe modificarne il
 * contenuto, ma modificherebbe solo il contenuto della COPIA ricevuta.
 *
 * 4. Di conseguenza, merge deve ricevere non una copia di dst, ma una copia
 * del suo INDIRIZZO. La variabile adatta a contenere l'indirizzo di un puntatore
 * è un puntatore a puntatore (int **).
 */

void merge(int **dst, const int *a1, unsigned s1, const int *a2, unsigned s2) {
    int index_a1 = 0, index_a2 = 0, index_dst;

    *dst = malloc((s1 + s2) * sizeof(**dst));
    if ((*dst) == NULL) return;

    for (index_dst = 0; index_dst < s1 + s2; index_dst++) {
        if (index_a1 == s1) {
            /* a1 finished, use a2 */
            (*dst)[index_dst] = a2[index_a2++];
        } else if (index_a2 == s2) {
            /* a2 finished, use a1 */
            (*dst)[index_dst] = a1[index_a1++];
        } else if (a1[index_a1] < a2[index_a2]) {
            /* both a1 and a2 not finished, use a1 */
            (*dst)[index_dst] = a1[index_a1++];
        } else {
            /* both a1 and a2 not finished, use a2 */
            (*dst)[index_dst] = a2[index_a2++];
        }
    }
}

#define SIZEA 10
#define SIZEB 10

int main(void) {
    int i;
    int a[SIZEA] = {21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    int b[SIZEB] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *dst;

    merge(&dst, a, SIZEA, b, SIZEB);
    for (i = 0; i < SIZEA + SIZEB; i++) {
        printf("dst[%d] = %d\n", i, dst[i]);
    }
    return 0;
}