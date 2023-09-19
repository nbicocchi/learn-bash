#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct array_info {
    int max;
    int min;
    float mean;
    float variance;
} array_info_t;

array_info_t *array_stats(const int *values, unsigned size) {
    unsigned i;
    array_info_t *info;

    info = malloc(sizeof(*info));
    if (!info) return NULL;

    /* init values */
    info->min = values[0];
    info->max = values[0];
    info->mean = 0.0F;
    info->variance = 0.0F;

    /* compute min, max, mean */
    for (i = 0; i < size; i++) {
        if (values[i] > info->max) info->max = values[i];
        if (values[i] < info->min) info->min = values[i];
        info->mean += (float) values[i];
    }
    info->mean /= (float) size;

    /* compute variance */
    for (i = 0; i < size; i++) {
        info->variance += powf((float) values[i] - info->mean, 2.0F);
    }
    info->variance /= (float) size;
    return info;
}

#define SIZE 128

int main(void) {
    int i;
    int src[SIZE];
    array_info_t *info;

    /* filling the array */
    for (i = 0; i < SIZE; i++) {
        src[i] = i;
    }

    info = array_stats(&src[0], SIZE);
    printf("min=%d\n", info->min);
    printf("max=%d\n", info->max);
    printf("mean=%.3f\n", info->mean);
    printf("variance=%.3f\n", info->variance);
}