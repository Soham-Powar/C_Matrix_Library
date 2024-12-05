#include <stdio.h>
#include <stdlib.h>

#include "head.h"

void convCOOtoAOL(SparseMat *mat) {
    if (mat == NULL || mat->coo_mat == NULL || mat->coo_mat->arr == NULL) {
        printf("Matrix is not initialized or empty.\n");
        return;
    }

    if (mat->aol_mat == NULL) {
        initAOL(&mat->aol_mat, mat->rows);
    }

    COOSparse *coo = mat->coo_mat;
    AOLSparse *aol = mat->aol_mat;

    for (ulint i = 0; i < mat->nnz; i++) {
        ulint row = coo->arr[i].row;
        ulint col = coo->arr[i].col;
        ulint data = coo->arr[i].data;

        AOLNode *nn = (AOLNode *)malloc(sizeof(AOLNode));
        if (nn == NULL) {
            printf("Memory allocation failed for AOLNode.\n");
            return;  // Alternatively, set a flag like _flag = 1002;
        }

        nn->col = col;
        nn->data = data;
        nn->next = NULL;

        if (aol->row[row] == NULL) {
            aol->row[row] = nn;
        } else {
            nn->next = aol->row[row];
            aol->row[row] = nn;
        }
    }
}