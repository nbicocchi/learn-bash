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

struct matrix *matrix_product(const struct matrix *m1, const struct matrix *m2) {
    struct matrix *m_prod;
    size_t i, j, h;

    /* check if m is square */
    if (m1->cols != m2->rows) return NULL;

    m_prod = malloc(sizeof(*m_prod));
    if (!m_prod) return NULL;

    m_prod->rows = m1->rows;
    m_prod->cols = m2->cols;
    m_prod->data = malloc((unsigned long) (m_prod->rows * m_prod->cols) * sizeof(*(m_prod->data)));
    if (!m_prod->data) return NULL;

    for (i = 0; i < m_prod->rows; i++) {
        for (j = 0; j < m_prod->cols; j++) {
            /* actual product */
            m_prod->data[i * m_prod->cols + j] = 0.0;
            for (h = 0; h < m1->cols; h++) {
                double n1 = m1->data[i * m1->cols + h];
                double n2 = m2->data[h * m2->cols + j];
                m_prod->data[i * m_prod->cols + j] += n1 * n2;
            }
        }
    }
    return m_prod;
}

void free_matrix(struct matrix *m) {
    free(m->data);
    free(m);
}

int main(void) {
    struct matrix *m_prod;

    double v1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    struct matrix m1 = {
            .rows=3,
            .cols=3,
            .data = v1,
    };

    double v2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    struct matrix m2 = {
            .rows=3,
            .cols=2,
            .data = v2,
    };

    m_prod = matrix_product(&m1, &m2);

    show_matrix(&m1);
    show_matrix(&m2);
    show_matrix(m_prod);

    free_matrix(m_prod);
}