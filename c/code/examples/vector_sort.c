#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* Function to initialize an array with random numbers */
void init(int v[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
    }
}

/* Function to implement bubble sort */
void sort(int v[], int n) {
    int i, j, tmp, changed;
    for (i = 0; i < n - 1; i++) {
        changed = FALSE;
        for (j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j+1]) {
                changed = TRUE;
                tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
        if (!changed) break;
    }
}

/* Function to print an array */
void show(int v[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("[i:%d] -> [value:%d]\n", i, v[i]);
    }
    printf("\n");
}

int main() {
    int v[10];
    int n = sizeof(v) / sizeof(v[0]);

    init(v, n);
    show(v, n);
    sort(v, n);
    show(v, n);
}
