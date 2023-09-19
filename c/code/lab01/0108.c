#include <stdio.h>

int main() {
    int somma = 0, n = 10;

    for (int i = 1; i <= n; i += 2) {
        somma += i;
    }
    printf("somma=%d\n", somma);
}