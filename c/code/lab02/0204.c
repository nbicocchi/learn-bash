#include <stdio.h>

#define SIZE 128

long findi(int value, const int *values, unsigned size) {
    for (long i = 0; i < size; i++) {
        if (values[i] == value) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    int i, src[SIZE];
    long index;

    /* filling the array */
    for (i = 0; i < SIZE; i++) {
        src[i] = i;
    }

    index = findi(100, src, SIZE);
    printf("index=%ld\n", index);

}