#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//renaming some of the data types which would be mostly used by us
typedef short int sint;
typedef long int lint;
typedef long long int llint;
typedef unsigned long int ulint;
typedef unsigned long long int ullint;

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
    bool struct_type[3]; //0 index for AOL, 1 index for COO, 2 index for CSR
    AOLSparse *aol_mat;
    COOSparse *coo_mat;
    CSRSparse *csr_mat;
} SparseMat;

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
    AOLNode **row;
} AOLSparse;

typedef struct COOSparse {
    COONode *arr; //arr stands for array
} COOSparse;

typedef struct CSRSparse {
    CSRNode *arr; //arr stands for array
    ulint *row_index;
} CSRSparse;

sint _flag = 0;

void initSparseMat(SparseMat *mat, ulint rows, ulint cols, sint imptype);

// make a init function to initialise the matrix
    // the function would take arguments like rows, cols, sparsemat address, implementation type.
/*
 *      initSparseMat(SparseMat *mat, ulint rows, ulint cols, int imptype) {
 *          //i will mark imptype index in struct_type array as true and rest as false
 *          //all other implementation type pointers would be NULL, except the required one
 *          // row and column values would have been copied
 *          //nnz = 0;
 *      }
 */

//make input read and file read function for all the 3 implementations
// user will basically use a function named readSparseMat(SparseMat *mat) if he wants to read from input given
// or a function named fileReadSparseMat(SparseMat *mat, //filename) if he wants to read from file given
// in those function we will check that which implementation we have to use according to the initialisation of sparse mat
// and then depending on that we will read the matrix from file or input
//e.g.
/*
 *      readSparseMat(SparseMat *mat) {
 *          if(mat->struct_type[0]) {
 *              //readAOL(AOLSparse **mat, int rows, int cols int *nnz)
 *          }
 *          else if(mat->struct[1]) {
 *              //read the matrix using AOL and then convert it to COO
 *              //first use the function readAOL() and then make a function 
 *              //to convert e.g. AOLToCOO() 
 *          }
 *          else {
 *              similar
 *          }
 *
 *
 * 
 * 
 */
