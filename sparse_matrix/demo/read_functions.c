#include "head.h"

AOLNode *_newAOLNode(lint data, ulint col) {
    AOLNode *new = (AOLNode *) malloc(sizeof(AOLNode));
    if(new == NULL) {
        _flag = 2003;
        return NULL;
    }
    new->data = data;
    new->col = col;
    new->next = NULL;
    return new;
}

void _readAOL(AOLSparse **mat, ulint rows, ulint cols, ulint *nnz) {
    //in function variables
    AOLNode **current = NULL, *newNode;
    lint data;
    ulint i, j;
    //actual code
    for(i = 0; i < rows; i++) {
        current = (*mat)->rows[i]; //setting current to start of the row
        for(j = 0; j < cols; j++) {
            if(scanf("%ld", &data) > 0) {
                if(data != 0) {
                    newNode = _newAOLNode(data, j);
                    if(newNode == NULL)
                        return;
                    else if((*current) == NULL) {
                        (*current) = newNode;
                    }
                    else {
                        (*current)->next = newNode;
                        current = &(*current)->next;
                    }
                }
                else {
                    continue;
                }
            }
            else {
                _flag = 2002;
                return;
            }
        }
    }
    _flag = 0000;
    return;
}

void _readCSR(SparseMat *mat) {
    _readAOL(&(mat->aol_mat), mat->rows, mat->cols, &mat->nnz);
    //convert aol to csr
    //delete aol
    return;
}

void _readCOO(SparseMat *mat) {
    _readAOL(&(mat->aol_mat), mat->rows, mat->cols, &mat->nnz);
    //convert aol to csr
    //delete aol
    return;
}




/* this function abstractly reads the sparse matrix. for reading a specific implementation a specific
 * function is include in this function*/
void readSparseMat(SparseMat *mat) {
    if(mat->rows == 0 || mat->cols == 0) {
        _flag = 2001;
    }
    else if(mat->imptype == 0) {
        _readAOL(&(mat->aol_mat), mat->rows, mat->cols, &mat->nnz);
    } //read in AOL implementation
    else if(mat->imptype == 1) {
        _readCOO(mat);
    } //read in COO implementation
    else if(mat->imptype == 2) {
        _readCSR(mat);
    } //read in CSR implementation
    else {
        _flag = 2001;
    }
    return;
}