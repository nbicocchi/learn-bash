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
    size_t i;

    m = malloc(sizeof(*m));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc((unsigned long) (rows) * sizeof(*(m->data)));
    if (m == NULL) return NULL;

    for (i = 0; i < rows; i++) {
        m->data[i] = malloc((unsigned long) (cols) * sizeof(**(m->data)));
        if (m->data[i] == NULL) return NULL;
    }

    return m;
}

void fill_matrix(struct matrix *m) {
    size_t i, j;
    double value = 1.0;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            m->data[i][j] = value++;
        }
    }
}

void free_matrix(struct matrix *m) {
    size_t i;

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

struct matrix *matrix_transpose(const struct matrix *m) {
    struct matrix *m_trans;
    size_t i, j;

    m_trans = allocate_matrix(m->cols, m->rows);
    for (i = 0; i < m_trans->rows; i++) {
        for (j = 0; j < m_trans->cols; j++) {
            m_trans->data[i][j] = m->data[j][i];
        }
    }
    return m_trans;
}

int main(void) {
    struct matrix *m, *m_trans;

    m = allocate_matrix(3, 2);
    fill_matrix(m);

    m_trans = matrix_transpose(m);

    show_matrix(m);
    show_matrix(m_trans);

    free_matrix(m);
    free_matrix(m_trans);
}