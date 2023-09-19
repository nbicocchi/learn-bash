#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct vector {
    unsigned length;
    int *data;
    void (*init)(struct vector *);
    void (*show)(struct vector *);
    void (*sort)(struct vector *);
};

void init(struct vector *vector) {
    unsigned i;
    for (i = 0; i < vector->length; i++) {
        vector->data[i] = rand() % 100;
    }
}

void show(struct vector *vector) {
    unsigned i;
    for (i = 0; i < vector->length; i++) {
        printf("[i:%d] -> [value:%d]\n", i, vector->data[i]);
    }
    printf("\n");
}

void sort(struct vector *vector) {
    unsigned i, j;
    int tmp, changed;
    for (i = 0; i < vector->length - 1; i++) {
        changed = FALSE;
        for (j = 0; j < vector->length - i - 1; j++) {
            if (vector->data[j] > vector->data[j+1]) {
                changed = TRUE;
                tmp = vector->data[j];
                vector->data[j] = vector->data[j + 1];
                vector->data[j + 1] = tmp;
            }
        }
        if (!changed) break;
    }
}

struct vector *allocate_vector(unsigned size) {
    struct vector *vector;

    vector = calloc(1, sizeof(struct vector));
    vector->length = size;
    vector->data = calloc(size, sizeof(int));
    vector->init = init;
    vector->show = show;
    vector->sort = sort;
    return vector;
}

int main() {
    struct vector *vector = allocate_vector(10);
    vector->init(vector);
    vector->show(vector);
    vector->sort(vector);
    vector->show(vector);
}
