#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* Function to initialize an array with random numbers */
void init(int *v, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        v[i] = rand() % 100;
    }
}

/* Function to implement bubble sort */
void sort(int *v, unsigned size) {
    unsigned i, j;
    int tmp, changed;
    for (i = 0; i < size - 1; i++) {
        changed = FALSE;
        for (j = 0; j < size - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                changed = TRUE;
                tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
        if (!changed) break;
    }
}

/* Function to search a value within an array */
int search(const int *v, unsigned size, int value) {
    for (int i = 0; i < size; i++) {
        if (v[i] == value) {
            return i;
        }
    }
    return -1;
}

/* Function to print an array */
void show(int *v, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        printf("[%u] %d\n", i, v[i]);
    }
}

int main() {
    int v[100];
    unsigned n = sizeof(v) / sizeof(*v);

    init(v, n);
    sort(v, n);
    show(v, n);
    printf("index(%d)=%d\n", 10, search(v, n, 10));
}
