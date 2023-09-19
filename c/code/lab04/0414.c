#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_SIZE 16

struct arraylist {
    /* number of actual elements contained */
    unsigned elements;

    /* size of the underlying array (l->data) */
    unsigned size;

    /* array containing the actual data */
    double *data;
};

struct arraylist *allocate_list() {
    struct arraylist *a;

    a = calloc(1, sizeof(*a));
    if (a == NULL) return NULL;

    a->elements = 0;
    a->size = DEFAULT_SIZE;
    a->data = calloc((unsigned long) (DEFAULT_SIZE), sizeof(*(a->data)));
    if (a->data == NULL) return NULL;

    return a;
}

void free_list(struct arraylist *l) {
    free(l->data);
    free(l);
}

double get(struct arraylist *l, unsigned index) {
    return l->data[index];
}

double delete(struct arraylist *l, unsigned index) {
    double element = l->data[index];
    unsigned i;

    for (i = index; i < l->elements - 1; i++) {
        l->data[i] = l->data[i + 1];
    }

    l->elements--;

    /* eventually shrink */
    if (l->elements < l->size / 2) {
        l->data = realloc(l->data, l->size * sizeof(*(l->data)) / 2);
        l->size /= 2;
    }

    return element;
}

void add(struct arraylist *l, double value) {
    /* eventually grow */
    if (l->elements >= l->size) {
        l->data = realloc(l->data, 2 * l->size * sizeof(*(l->data)));
        l->size *= 2;
    }
    l->data[l->elements] = value;
    l->elements++;
}

void set(struct arraylist *l, unsigned index, double value) {
    l->data[index] = value;
}

unsigned elements(struct arraylist *l) {
    return l->elements;
}

unsigned size(struct arraylist *l) {
    return l->size;
}

int main(void) {
    struct arraylist *l;
    unsigned index;

    /* allocate empty list */
    l = allocate_list();

    /* insert elements */
    for (index = 0; index < 35; index++) {
        add(l, (double) index);
    }

    /* modify existing elements */
    set(l, 0, 77.0);

    /* delete existing elements */
    for (index = 30; index > 0; index--) {
        delete(l, index);
    }

    /* show elements */
    for (index = 0; index < l->elements; index++) {
        printf("[%d] %.3f\n", index, get(l, index));
    }

    /* show size */
    printf("elements=%d\n", elements(l));
    printf("size=%d\n", size(l));

    /* free memory */
    free_list(l);
}