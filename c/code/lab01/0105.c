#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = -5;

    if (n >= 0) {
        printf("%d positivo\n", n);
    } else {
        printf("%d negativo\n", n);
    }

    if (n % 2 == 0) {
        printf("%d pari\n", n);
    } else {
        printf("%d dispari\n", n);
    }
}