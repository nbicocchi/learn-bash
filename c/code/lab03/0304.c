#include <stdio.h>
#include <math.h>

struct array_info {
    int max;
    int min;
    float mean;
    float variance;
};

struct array_info array_stats(const int *values, unsigned size) {
    unsigned i;
    int max = values[0], min = values[0];
    float mean = 0.0F, variance = 0.0F;

    /* compute max, min, sum */
    for (i = 0; i < size; i++) {
        if (values[i] > max) {
            max = values[i];
        }
        if (values[i] < min) {
            min = values[i];
        }
        mean += (float) values[i];
    }

    /* compute mean */
    mean /= (float) size;

    /* compute variance */
    for (i = 0; i < size; i++) {
        variance += powf((float) values[i] - mean, 2.0F);
    }
    variance /= (float) size;

    /* return array_info_t variable */
    struct array_info info = {.max = max, .min = min, .mean = mean, .variance = variance};
    return info;
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
    info = array_stats(src, SIZE);
    printf("max=%d min=%d mean=%.3f variance=%.3f\n", info.max, info.min, info.mean, info.variance);
}