#include <stdio.h>
#include <math.h>

#define SIZE 128

void compute_mean_variance(float *rmean, float *rvariance, float *values, unsigned size) {
    /* init values */
    *rmean = 0.0F;
    *rvariance = 0.0F;

    /* compute mean */
    for (unsigned i = 0; i < size; i++) {
        *rmean += values[i];
    }
    *rmean /= (float) size;

    /* compute variance */
    for (unsigned i = 0; i < size; i++) {
        *rvariance += powf(values[i] - *rmean, 2.0F);
    }
    *rvariance /= (float) size;
}

int main(void) {
    float src[SIZE], rmean, rvariance;

    /* filling the array */
    for (int i = 0; i < SIZE; i++) {
        src[i] = (float) i;
    }

    compute_mean_variance(&rmean, &rvariance, src, SIZE);
    printf("mean=%.3f\n", rmean);
    printf("variance=%.3f\n", rvariance);
}