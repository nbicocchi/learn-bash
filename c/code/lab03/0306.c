#include <stdio.h>
#include <math.h>

struct complex {
    double real;
    double imaginary;
};

void complex_product(struct complex *r, const struct complex *c1, const struct complex *c2) {
    r->real = (c1->real * c2->real) - (c1->imaginary * c2->imaginary);
    r->imaginary = (c1->real * c2->imaginary) + (c1->imaginary * c2->real);
}


#define SIZE 128

int main(void) {
    struct complex c1 = {.real=1, .imaginary=1};
    struct complex c2 = {.real=1, .imaginary=3};
    struct complex c3;

    /* call complex_product and show the result */
    complex_product(&c3, &c1, &c2);
    printf("%lf+%lfi x %lf+%lfi = %lf+%lfi\n", c1.real, c1.imaginary, c2.real, c2.imaginary, c3.real, c3.imaginary);
}