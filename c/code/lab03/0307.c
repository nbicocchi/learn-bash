#include <stdio.h>
#include <math.h>

typedef struct point {
    float x;
    float y;
} point_t;

float compute_length(const point_t *p, unsigned n) {
    unsigned i;
    float length = 0.0F;

    for (i = 0; i < n - 1; i++) {
        length += hypotf(p[i].x - p[i + 1].x, p[i].y - p[i + 1].y);
    }
    return length;
}

#define SIZE 5

int main(void) {
    point_t vertices[SIZE] = {
            {.x=0.0F, .y=0.0F},
            {.x=4.0F, .y=0.0F},
            {.x=4.0F, .y=4.0F},
            {.x=0.0F, .y=4.0F},
            {.x=0.0F, .y=0.0F},
    };
    printf("length=%.3f\n", compute_length(vertices, SIZE));
}