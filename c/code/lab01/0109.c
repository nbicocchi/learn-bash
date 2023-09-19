#include <stdio.h>
#include <math.h>

int main() {
    int n = 101, log_approx;

    log_approx = (int) floor(log10((double) n));
    printf("log approssimato=%d\n", log_approx);
}