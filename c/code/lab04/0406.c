#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct matrix {
    size_t rows, cols;
    double *data;
};

void show_matrix(const struct matrix *m) {
    size_t i, j;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            printf("%8.2lf", m->data[i * m->cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

struct matrix *matrix_transpose(const struct matrix *m) {
    struct matrix *m_trans;
    size_t i, j;

    m_trans = malloc(sizeof(*m_trans));
    if (!m_trans) return NULL;

    m_trans->rows = m->cols;
    m_trans->cols = m->rows;
    m_trans->data = malloc((unsigned long) (m_trans->rows * m_trans->cols) * sizeof(*(m_trans->data)));
    if (!m_trans->data) return NULL;

    for (i = 0; i < m_trans->rows; i++) {
        for (j = 0; j < m_trans->cols; j++) {
            m_trans->data[i * m_trans->cols + j] = m->data[j * m_trans->rows + i];
        }
    }
    return m_trans;
}

void free_matrix(struct matrix *m) {
    free(m->data);
    free(m);
}

int main(void) {
    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    struct matrix *m_trans, m = {
            .rows=3,
            .cols=2,
            .data = values,
    };

    m_trans = matrix_transpose(&m);

    show_matrix(&m);
    show_matrix(m_trans);

    free_matrix(m_trans);
}