#include <stdio.h>

int main() {
    unsigned n = 100;
    double somma_inversi = 0.0;

    for (int i = 1; i <= n; i++) {
        somma_inversi += 1 / (double)i;
    }
    printf("somma inversi = %lf\n", somma_inversi);
}