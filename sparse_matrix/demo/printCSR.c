#include <stdio.h>
#include <stdlib.h>

#include "head.h"

void printCSR(SparseMat *mat) {
    if (mat == NULL || mat->csr_mat == NULL || mat->csr_mat->arr == NULL ||
        mat->csr_mat->row_index == NULL) {
        printf("Matrix is not initialized or empty.\n");
        return;
    }

    CSRSparse *csr = mat->csr_mat;
    ulint idx = 0;

    for (ulint i = 0; i < mat->rows; i++) {
        for (ulint j = 0; j < mat->cols; j++) {
            // Check if the current column has a non-zero entry
            if (idx < mat->nnz && j == csr->arr[idx].col &&
                idx >= csr->row_index[i] && idx < csr->row_index[i + 1]) {
                printf("%d ", csr->arr[idx].data);
                idx++;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
