#include <stdio.h>

#define TRUE 1
#define FALSE 0

int is_prime(unsigned v) {
    if (v == 0) return FALSE;
    if (v == 1) return TRUE;

    for (unsigned i = 2; i < v; i++) {
        if (v % i == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

int main() {
    for (unsigned i = 0; i < 100; i++) {
        if (is_prime(i)) {
            printf("%u\n", i);
        }
    }
}