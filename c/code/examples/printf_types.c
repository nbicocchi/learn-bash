#include <stdio.h>

int main() {
    /* interi con segno */
    char c = 'a';
    int d = 1;
    long ld = 1;
    long long lld = 1;

    /* interi senza segno */
    unsigned char cu = 'a';
    unsigned int u = 1;
    unsigned long lu = 1;
    unsigned long long llu = 1;

    /* virgola mobile */
    float f = 1.0;
    double lf = 1.0;
    long double Lf = 1.0;

    printf("%c\n", c);
    printf("%d\n", d);
    printf("%ld\n", ld);
    printf("%lld\n", lld);

    printf("%cu\n", cu);
    printf("%u\n", u);
    printf("%lu\n", lu);
    printf("%llu\n", llu);

    printf("%f\n", f);
    printf("%lf\n", lf);
    printf("%Lf\n", Lf);
}