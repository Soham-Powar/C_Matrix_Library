#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//renaming some of the data types which would be mostly used by us
typedef short int sint;
typedef long int lint;
typedef long long int llint;
typedef unsigned long int ulint;
typedef unsigned long long int ullint;

typedef struct AOLNode {
    lint data;
    ulint col;
    struct AOLNode *next;
} AOLNode;

typedef struct COONode {
    lint data; 
    ulint col;
    ulint row;
} COONode;

typedef struct CSRNode {
    lint data;
    ulint col;
} CSRNode;

typedef struct AOLSparse {
    AOLNode **rows;
} AOLSparse;

typedef struct COOSparse {
    COONode *arr; //arr stands for array
} COOSparse;

typedef struct CSRSparse {
    CSRNode *arr; //arr stands for array
    ulint *row_entries;
} CSRSparse;

sint _flag = 0;

/* //simple structure for now
 * while initialising a variable of this structure the user will have to choose according to
 * which data structure(COO, AOL, CSR) does he want to implement the matrix. If he chooses AOL
 * then the rest of the pointer like coo_mat and csr_mat would be null and aol_mat would point to
 * the matrix
 */
typedef struct SparseMat {
    ulint rows; //number of rows in the matrix
    ulint cols; //number of columns in the matrix
    ulint nnz; //number of nonzero entries in the matrix
    //bool struct_type[3]; //0 index for AOL, 1 index for COO, 2 index for CSR
    sint imptype;
    AOLSparse *aol_mat;
    COOSparse *coo_mat;
    CSRSparse *csr_mat;
} SparseMat;



void _initAOL(AOLSparse **mat, ulint rows);
void _initCOO(COOSparse **mat);
void _initCSR(CSRSparse **mat, ulint rows);
void initSparseMat(SparseMat *mat, ulint rows, ulint cols, sint imptype);

void _readCSR(SparseMat *mat);
void _readCOO(SparseMat *mat);
void _readAOL(AOLSparse **mat, ulint rows, ulint cols, ulint *nnz);
void readSparseMat(SparseMat *mat);

void _printCSR();
void _printCOO();
void _printAOL();
void printSparseMat(SparseMat *mat);

//#include "head.h"

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
            _initAOL(&mat->aol_mat, mat->rows); //for COO you need AOL
            _initCOO(&mat->coo_mat);
            break;
        case 2:
            //initialises the matrix using CSR implementation
            _initAOL(&mat->aol_mat, mat->rows); //for CSR you need AOL
            _initCSR(&mat->csr_mat, mat->rows);
            break;
        default:
            //return imptype error
            _flag = 1001;
    }
    return;
}

//#include "head.h"

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
                    else if(*current == NULL) {
                        *current = newNode;
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

void _printAOL(SparseMat *mat) {
    if (mat == NULL || mat->aol_mat == NULL) {
        _flag = 3002; // matrix contains no data;
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

int main() {
    SparseMat mat;
    initSparseMat(&mat, 4, 4, 0);
    printf("flag -> %hd\n", _flag);
    readSparseMat(&mat);
    printf("flag -> %hd\n", _flag);
    printSparseMat(&mat);
    printf("flag -> %hd\n", _flag);
    return 0;
}


