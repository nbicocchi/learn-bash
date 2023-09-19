#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

struct node {
    /* the actual data of the node */
    double data;

    /* pointer to the next node */
    struct node *next;
};

struct linkedlist {
    /* number of actual elements contained */
    unsigned elements;

    /* pointer to the head of the list */
    struct node *head;
};

/* Service function for allocating a new node */
struct node *allocate_node(double value) {
    struct node *node;

    node = malloc(sizeof(*node));
    node->data = value;
    node->next = NULL;
    return node;
}

/* Service function for retrieving a node with a given index */
struct node *get_node(struct linkedlist *l, unsigned index) {
    struct node *node;
    unsigned i = 0;

    if (!l->head) {
        /* the list is empty */
        return NULL;
    } else {
        /* the list contains elements */
        node = l->head;
        while (node->next && i < index) {
            node = node->next;
            i++;
        }
        return node;
    }
}

unsigned elements(struct linkedlist *l) {
    return l->elements;
}

unsigned size(struct linkedlist *l) {
    return l->elements;
}

struct linkedlist *allocate_list() {
    struct linkedlist *l;

    l = malloc(sizeof(*l));
    if (l == NULL) return NULL;

    l->elements = 0;
    l->head = NULL;
    return l;
}

void free_list(struct linkedlist *l) {
    struct node *next, *tmp;

    next = l->head;
    while (next) {
        tmp = next;
        next = next->next;
        free(tmp);
    }
    free(l);
}

double get(struct linkedlist *l, unsigned index) {
    return get_node(l, index)->data;
}

double delete(struct linkedlist *l, unsigned index) {
    struct node *delete, *prev, *next;
    double value;

    if (index < 0) return DBL_MAX;

    if (index == 0) {
        delete = get_node(l, 0);
        next = delete->next;
        l->head = next;
    } else {
        prev = get_node(l, index - 1);
        delete = prev->next;
        next = delete->next;
        prev->next = next;
    }

    value = delete->data;
    free(delete);
    l->elements--;
    return value;
}

void add(struct linkedlist *l, double value) {
    struct node *node;

    if (!l->head) {
        /* the list is empty */
        l->head = allocate_node(value);
    } else {
        /* the list contains elements */
        node = get_node(l, elements(l) - 1);
        node->next = allocate_node(value);
    }
    l->elements++;
}

void set(struct linkedlist *l, unsigned index, double value) {
    get_node(l, index)->data = value;
}


int main(void) {
    struct linkedlist *l;
    unsigned index;

    /* allocate empty list */
    l = allocate_list();

    /* insert elements */
    for (index = 0; index < 10; index++) {
        add(l, (double) index);
    }

    /* modify existing elements */
    set(l, 9, 99.0);
    set(l, 8, 99.0);

    /* delete existing elements */
    delete(l, elements(l) - 1);
    delete(l, 0);

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