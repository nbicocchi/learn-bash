#include <stdio.h>

int main() {
    int exp = 1, n = 8;

    for (int i = 0; i < n; i++) {
        exp *= 2;
    }
    printf("2^%d=%d\n", n, exp);
}