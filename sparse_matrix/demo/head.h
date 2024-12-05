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


//function prototypes
void _initAOL(AOLSparse **mat, ulint rows);
void _initCOO(COOSparse **mat);
void _initCSR(CSRSparse **mat, ulint rows);
void initSparseMat(SparseMat *mat, ulint rows, ulint cols, sint imptype);

void _readCSR(SparseMat *mat);
void _readCOO(SparseMat *mat);
void _readAOL(AOLSparse **mat, ulint rows, ulint cols, ulint *nnz);
void readSparseMat(SparseMat *mat);

void _deleteAOL(SparseMat *mat);
void _deleteCOO(SparseMat *mat);
void _deleteCSR(SparseMat *mat);
void deleteSparseMat(SparseMat *mat);

void _printCSR();
void _printCOO();
void _printAOL();
void printSparseMat(SparseMat *mat);
