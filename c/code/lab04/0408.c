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

struct matrix *matrix_swap_diagonals(const struct matrix *m) {
    struct matrix *m_diags;
    size_t i, j;

    /* check if m is square */
    if (m->rows != m->cols) return NULL;

    m_diags = malloc(sizeof(*m_diags));
    if (!m_diags) return NULL;

    m_diags->rows = m->rows;
    m_diags->cols = m->cols;
    m_diags->data = malloc((unsigned long) (m_diags->rows * m_diags->cols) * sizeof(*(m_diags->data)));
    if (!m_diags->data) return NULL;

    for (i = 0; i < m_diags->rows; i++) {
        for (j = 0; j < m_diags->cols; j++) {
            /* check if the element is on a diagonal */
            if ((i == j) || (i == m->cols - j - 1)) {
                /* copy and swap */
                m_diags->data[i * m->cols + j] = m->data[i * m->cols + (m->cols - j - 1)];
            } else {
                /* standard copy */
                m_diags->data[i * m->cols + j] = m->data[i * m->cols + j];
            }
        }
    }
    return m_diags;
}

void free_matrix(struct matrix *m) {
    free(m->data);
    free(m);
}

int main(void) {
    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    struct matrix *m_diags, m = {
            .rows=3,
            .cols=3,
            .data = values,
    };

    m_diags = matrix_swap_diagonals(&m);

    show_matrix(&m);
    show_matrix(m_diags);

    free_matrix(m_diags);
}