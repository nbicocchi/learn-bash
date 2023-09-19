#include <stdio.h>
#include <math.h>

int main() {
    unsigned n = 255;

    /* print bit numbers */
    for (unsigned i = 0; i < 32; i++) {
        printf("%3d", i);
    }
    printf("\n");

    /* print and count active bits */
    for (unsigned i = 0; i < 32; i++) {
        unsigned mask = (unsigned) pow(2, i);
        if ((n & mask) == mask) {
            printf("%3d", 1);
        } else {
            printf("%3d", 0);
        }
    }
}
