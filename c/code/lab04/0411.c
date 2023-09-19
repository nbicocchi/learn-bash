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

struct matrix *matrix_product(const struct matrix *m1, const struct matrix *m2) {
    struct matrix *m_prod;
    size_t i, j, h;

    /* check if m is square */
    if (m1->cols != m2->rows) return NULL;

    m_prod = allocate_matrix(m1->rows, m2->cols);

    for (i = 0; i < m_prod->rows; i++) {
        for (j = 0; j < m_prod->cols; j++) {
            /* actual product */
            m_prod->data[i][j] = 0.0;
            for (h = 0; h < m1->cols; h++) {
                m_prod->data[i][j] += m1->data[i][h] * m2->data[h][j];
            }
        }
    }
    return m_prod;
}

int main(void) {
    struct matrix *m1, *m2, *m_prod;

    m1 = allocate_matrix(3, 3);
    m2 = allocate_matrix(3, 2);

    fill_matrix(m1);
    fill_matrix(m2);

    m_prod = matrix_product(m1, m2);

    show_matrix(m1);
    show_matrix(m2);
    show_matrix(m_prod);

    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m_prod);
}