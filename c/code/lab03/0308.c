#include <stdio.h>

typedef struct point {
    float x;
    float y;
} point_t;

typedef struct polygon {
    unsigned n;
    point_t *vertices;
} polygon_t;

float compute_area(const polygon_t *p) {
    unsigned i, next;
    float sum = 0.0F;

    for (i = 0; i < p->n; i++) {
        next = (i + 1) % p->n;
        sum += 0.5F * (p->vertices[i].x * p->vertices[next].y) - (p->vertices[i].y * p->vertices[next].x);
    }
    return sum;
}

#define SIZE 3

int main(void) {
    point_t vertices[SIZE] = {
            {.x=0.0F, .y=0.0F},
            {.x=4.0F, .y=0.0F},
            {.x=2.0F, .y=2.0F},
    };
    polygon_t p = {.n=SIZE, .vertices=vertices};
    printf("area=%.3f\n", compute_area(&p));
}