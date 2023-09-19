#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

typedef struct point {
    float x;
    float y;
} point_t;

typedef struct circle {
    point_t center;
    float radius;
} circle_t;

int isinside(const point_t *p, const circle_t *c) {
    float distance = hypotf(p->x - c->center.x, p->y - c->center.y);
    if (distance < c->radius) {
        return TRUE;
    }
    return FALSE;
}

#define SIZE 3

int main(void) {
    point_t p = {.x=8, .y=8};
    circle_t c = {
            .center = {.x=0, .y=0},
            .radius = 10,
    };
    printf("isinside?=%d\n", isinside(&p, &c));
}