#include <stdio.h>
#include <math.h>

struct array_info {
    int max;
    int min;
    float mean;
    float variance;
};

void array_stats(struct array_info *r, const int *values, unsigned size) {
    unsigned i;

    r->max = values[0];
    r->min = values[0];
    r->mean = 0.0F;
    r->variance = 0.0F;

    /* compute max, min, sum */
    for (i = 0; i < size; i++) {
        if (values[i] > r->max) {
            r->max = values[i];
        }
        if (values[i] < r->min) {
            r->min = values[i];
        }
        r->mean += (float) values[i];
    }

    /* compute mean */
    r->mean /= (float) size;

    /* compute variance */
    for (i = 0; i < size; i++) {
        r->variance += powf((float) values[i] - r->mean, 2.0F);
    }
    r->variance /= (float) size;
}

#define SIZE 128

int main(void) {
    int i, src[SIZE];
    struct array_info info;

    /* fill the array */
    for (i = 0; i < SIZE; i++) {
        src[i] = i;
    }

    /* call array_stats and show the result */
    array_stats(&info, src, SIZE);
    printf("max=%d min=%d mean=%.3f variance=%.3f\n", info.max, info.min, info.mean, info.variance);
}