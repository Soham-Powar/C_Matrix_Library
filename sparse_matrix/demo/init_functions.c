#include "head.h"

void _initAOL(AOLSparse **mat, ulint rows) {
    (*mat) = (AOLSparse *) malloc(sizeof(AOLSparse));
    if(*mat == NULL) {
        _flag = 1002;
        return;
    }
    (*mat)->rows = (AOLNode **) calloc(rows, sizeof(AOLNode));
    if((*mat)->rows == NULL)
        _flag = 1002;
    return;
}

void _initCOO(COOSparse **mat) {
    (*mat) = (COOSparse *) malloc(sizeof(COOSparse));
    if(*mat == NULL) {
        _flag = 1002;
        return;
    }
    (*mat)->arr = NULL;
    return;
}

void _initCSR(CSRSparse **mat, ulint rows) {
    (*mat) = (CSRSparse *) malloc(sizeof(CSRSparse));
    if(*mat == NULL) {
        _flag = 1002;
        return;
    }
    (*mat)->arr = NULL;
    (*mat)->row_entries = (ulint *) calloc(rows, sizeof(ulint));
    if((*mat)->row_entries == NULL)
        _flag = 1002;
    return;    
}

/* this function initialises the provided sparse matrix with the number of rows and columns 
 * you want and the type of implementation(AOL, COO, CSR)
 * precondition: a sparse matrix should have already been defined, rows, columns and
 *      implementation type should be provided. 
 *      for AOL imptype = 0, COO imptype = 1, CSR imptype = 2 and so on
 * postcondition: on success sets the global variable 'flag' to 0, else to a specific type 
 *      no. which can be checked with checkErr().
 */
void initSparseMat(SparseMat *mat, ulint rows, ulint cols, sint imptype) {
    deleteSparseMat(mat);
    _flag = 0000;
    mat->rows = rows; //stored the number of rows
    mat->cols = cols; //stored the number of columns
    mat->nnz = 0; //initialized the number of nonzero entries in the matrix to 0
    mat->imptype = imptype;
    //making all the different implementation mat pointer point to null initially
    mat->aol_mat = NULL;
    mat->coo_mat = NULL;
    mat->csr_mat = NULL;
    switch(imptype) {
        case 0:
            //initialises the matrix using AOL implementation
            _initAOL(&mat->aol_mat, mat->rows);
            break;
        case 1:
            //initialises the matrix using COO implementation
            _initCOO(&mat->coo_mat);
            break;
        case 2:
            //initialises the matrix using CSR implementation
            _initCSR(&mat->csr_mat, mat->rows);
            break;
        default:
            //return imptype error
            _flag = 1001;
    }
    return;
}


