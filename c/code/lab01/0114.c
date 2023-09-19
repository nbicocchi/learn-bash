#include <stdio.h>

int main() {
    int n = 100;

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            printf("%d divisore di %d\n", i, n);
        }
    }
}