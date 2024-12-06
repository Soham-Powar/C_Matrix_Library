#include "head.h"

void _printAOL(SparseMat *mat) {
    if (mat == NULL || mat->aol_mat == NULL) {
        _flag = 0001; // matrix initialised incorrectly
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



void _printCOO(SparseMat *mat) {
    if (mat == NULL || mat->coo_mat == NULL || mat->coo_mat->arr == NULL) {
        _flag = 0001;
        return;
    }
    else if(mat->nnz == 0) {
        printf("Matrix Empty\n");
        return;
    }

    COOSparse *temp = mat->coo_mat;
    ulint rows = mat->rows;
    ulint cols = mat->cols;
    ulint nnz = mat->nnz;

    // Print matrix row by row
    for (ulint i = 0; i < rows; i++) {
        for (ulint j = 0; j < cols; j++) {
            int found = 0;  // Flag to track if the current (i, j) has a value
            for (ulint k = 0; k < nnz; k++) {
                if (temp->arr[k].row == i && temp->arr[k].col == j) {
                    printf("%ld ", temp->arr[k].data);
                    found = 1;
                    break;  // Exit loop once the value is printed
                }
            }
            if (!found) {
                printf("0 ");
            }
        }
        printf("\n");
    }
}



void printSparseMat(SparseMat *mat) {
    if(mat->imptype == 0) {
        _printAOL(mat);
    }
    else if(mat->imptype == 1) {
        _printCOO(mat);
    }
    else if(mat->imptype == 2) {
        _printCSR(mat);
    }
    else {
        _flag = 0001;//matrix not initialised or initialised incorrectly
    }
    return;
}