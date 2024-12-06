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
        current = &(*mat)->rows[i]; //setting current to start of the row
        for(j = 0; j < cols; j++) {
            if(scanf("%ld", &data) > 0) {
                if(data != 0) {
                    newNode = _newAOLNode(data, j);
                    if(newNode == NULL)
                        return;
                    else if((*current) == NULL) {
                        (*current) = newNode;
                        *nnz += 1;
                    }
                    else {
                        (*current)->next = newNode;
                        current = &(*current)->next;
                        *nnz += 1;
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
    //new AOL matrix
    SparseMat temp;
    initSparseMat(&temp, mat->rows, mat->cols, 0);
    if(_flag == 1002) return;
    readSparseMat(&temp);
    if(_flag == 2002 || _flag == 2003) return;
    //convert above AOL to original CSR
    convAOLtoCSR(&temp, mat);
    if(_flag == 5001 || _flag == 1002) return;
    deleteSparseMat(&temp); //delete AOL
    return;
}

/* as we cannot directly read a matrix to COO and the original matrix is already
 * initialised for COO, we will create a AOL matrix in the below function then 
 * convert it to the original COO matrix using a conversion function and afterwards 
 * delete the AOL matrix*/
void _readCOO(SparseMat *mat) {
    //new AOL matrix
    SparseMat temp;
    initSparseMat(&temp, mat->rows, mat->cols, 0);
    if(_flag == 1002) return;
    readSparseMat(&temp);
    if(_flag == 2002 || _flag == 2003) return;
    //convert above AOL to original COO
    convAOLtoCOO(&temp, mat);
    if(_flag == 5001 || _flag == 1002) return;
    deleteSparseMat(&temp); //delete AOL
    return;
}

/* this function abstractly reads the sparse matrix. for reading a specific implementation a specific
 * function is included in this function*/
void readSparseMat(SparseMat *mat) {
    ulint temp_rows, temp_cols;
    if(mat->rows == 0 || mat->cols == 0) {
        _flag = 0001;
    }
    else if(mat->imptype == 0) {
        //check if matrix already contains data
        if(mat->nnz != 0) {
            temp_rows = mat->rows; temp_cols = mat->cols;
            deleteSparseMat(mat);
            initSparseMat(mat, temp_rows, temp_cols, 0);
        }
        printf("Input %lu X %lu Matrix\n", mat->rows, mat->rows);
        _readAOL(&(mat->aol_mat), mat->rows, mat->cols, &mat->nnz);
    } //read in AOL implementation

    else if(mat->imptype == 1) {
        //check if matrix already contains data
        if(mat->nnz != 0) {
            temp_rows = mat->rows; temp_cols = mat->cols;
            deleteSparseMat(mat);
            initSparseMat(mat, temp_rows, temp_cols, 1);
        }
        //printf("Input %lu X %lu Matrix\n", mat->rows, mat->rows);
        _readCOO(mat);
    } //read in COO implementation

    else if(mat->imptype == 2) {
        
        //printf("Input %lu X %lu Matrix\n", mat->rows, mat->rows);
        _readCSR(mat);
    } //read in CSR implementation
    else {
        _flag = 0001;
    }
    return;
}