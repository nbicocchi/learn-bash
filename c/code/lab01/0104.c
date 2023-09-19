#include <stdio.h>
#include <math.h>

int main() {
    int x1 = 0, y1 = 0;
    int x2 = 10, y2 = 10;
    float distance;

    distance = sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    printf("p1=(%d,%d) p2=(%d,%d) distance=%f\n", x1, y1, x2, y2, distance);

    // alternative, using powf function
    distance = sqrtf(powf((x1 - x2), 2) + powf((y1 - y2), 2));
    printf("p1=(%d,%d) p2=(%d,%d) distance=%f\n", x1, y1, x2, y2, distance);

    // alternative, using hypotf function
    distance = hypotf(x1 - x2, y1 - y2);
    printf("p1=(%d,%d) p2=(%d,%d) distance=%f\n", x1, y1, x2, y2, distance);
}