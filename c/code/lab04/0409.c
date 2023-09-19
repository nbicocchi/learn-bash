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

struct matrix *matrix_swap_diagonals(const struct matrix *m) {
    struct matrix *m_diags;
    size_t i, j;

    /* check if m is square */
    if (m->rows != m->cols) return NULL;

    m_diags = allocate_matrix(m->rows, m->cols);

    for (i = 0; i < m_diags->rows; i++) {
        for (j = 0; j < m_diags->cols; j++) {
            /* check if the element is on a diagonal */
            if ((i == j) || (i == m->cols - j - 1)) {
                /* copy and swap */
                m_diags->data[i][j] = m->data[i][m->cols - j - 1];
            } else {
                /* standard copy */
                m_diags->data[i][j] = m->data[i][j];
            }
        }
    }
    return m_diags;
}

int main(void) {
    struct matrix *m, *m_diags;

    m = allocate_matrix(3, 3);
    fill_matrix(m);

    m_diags = matrix_swap_diagonals(m);

    show_matrix(m);
    show_matrix(m_diags);

    free_matrix(m);
    free_matrix(m_diags);
}