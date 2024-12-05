#include <stdio.h>
#include <stdlib.h>

#include "head.h"

void printAOL(SparseMat *mat) {
    if (mat == NULL || mat->aol_mat == NULL) {
        printf("Matrix is not initialized or is empty.\n");
        return;
    }

    AOLSparse *temp = mat->aol_mat;

    for (ulint i = 0; i < mat->rows; i++) {
        AOLNode *tempNode = temp->rows[i];
        for (ulint colIndex = 0; colIndex < mat->cols; colIndex++) {
            if (tempNode != NULL && tempNode->col == colIndex) {
                printf("%d ", tempNode->data);
                tempNode = tempNode->next;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
