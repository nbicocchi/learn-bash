#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct matrix {
    size_t rows, cols;
    double **data;
};

struct matrix *allocate_matrix(size_t rows, size_t cols) {
    struct matrix *m;
    int i;

    m = malloc(sizeof(*m));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc((unsigned long) (rows) * sizeof(*m));
    if (m == NULL) return NULL;

    for (i = 0; i < rows; i++) {
        m->data[i] = malloc((unsigned long) (cols) * sizeof(**(m->data)));
        if (m->data[i] == NULL) return NULL;
    }

    return m;
}

void fill_matrix(struct matrix *m) {
    size_t i, j;
    double value = 0.0;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            m->data[i][j] = value++;
        }
    }
}

void free_matrix(struct matrix *m) {
    int i;

    for (i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void show_matrix(const struct matrix *m) {
    size_t i, j;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            printf("%8.2lf", m->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int matrix_compare(const struct matrix *m1, const struct matrix *m2) {
    size_t i, j;

    if ((m1->rows != m2->rows) || (m1->cols != m2->cols)) return 1;

    for (i = 0; i < m1->rows; i++) {
        for (j = 0; j < m1->cols; j++) {
            if (m1->data[i][j] != m2->data[i][j])
                return 1;
        }
    }
    return 0;
}

int main(void) {
    struct matrix *m1, *m2;

    m1 = allocate_matrix(3, 2);
    m2 = allocate_matrix(3, 2);

    fill_matrix(m1);
    fill_matrix(m2);

    show_matrix(m1);
    show_matrix(m2);
    printf("%d\n", matrix_compare(m1, m2));

    free_matrix(m1);
    free_matrix(m2);
}