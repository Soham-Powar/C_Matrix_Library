#include "head.h"

void _printAOL(SparseMat *mat) {
    if (mat == NULL || mat->aol_mat == NULL) {
        _flag = 3001; // matrix contains no data;
        return;
    }
    else if(mat->nnz == 0) {
        printf("Matrix empty\n");
        return;
    }

    AOLSparse *temp = mat->aol_mat;

    for (ulint i = 0; i < mat->rows; i++) {
        AOLNode *tempNode = temp->rows[i];
        for (ulint colIndex = 0; colIndex < mat->cols; colIndex++) {
            if (tempNode != NULL && tempNode->col == colIndex) {
                printf("%ld ", tempNode->data);
                tempNode = tempNode->next;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
    return;
}

void printSparseMat(SparseMat *mat) {
    if(mat->imptype == 0) {
        _printAOL(mat);
    }
    else if(mat->imptype == 1) {
        //_printCOO();
    }
    else if(mat->imptype == 2) {
        //_printCSR();
    }
    else {
        _flag = 3001;//matrix not initialised or initialised incorrectly
    }
    return;
}