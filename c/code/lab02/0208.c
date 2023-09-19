#include <stdio.h>

#define SIZE 32

void fibonacci(unsigned *dst, unsigned n) {
    dst[0] = 0;
    dst[1] = 1;

    for (unsigned i = 2; i < n; i++) {
        dst[i] = dst[i - 1] + dst[i - 2];
    }
}

int main(void) {
    unsigned dst[SIZE];

    fibonacci(dst, SIZE);
    for (unsigned i = 0; i < SIZE; i++) {
        printf("fibonacci(%u) = %u\n", i, dst[i]);
    }

}