#include <stdio.h>

int main() {
    int a = 101, b = 112, c = 77;
    int max;

    if ((a >= b) && (a >= c)) {
        max = a;
    } else if ((b >= a) && (b >= c)) {
        max = b;
    } else {
        max = c;
    }

    printf("max=%d\n", max);
}