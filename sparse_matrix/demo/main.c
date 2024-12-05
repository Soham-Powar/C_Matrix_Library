/*head.h*/
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

/*init_functions.c*/

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

/*read_functions.c*/

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
 * function is included in this function*/
void readSparseMat(SparseMat *mat) {
    if(mat->rows == 0 || mat->cols == 0) {
        _flag = 2001;
    }
    else if(mat->imptype == 0) {
        printf("Input %lu X %lu Matrix\n", mat->rows, mat->rows);
        _readAOL(&(mat->aol_mat), mat->rows, mat->cols, &mat->nnz);
    } //read in AOL implementation
    else if(mat->imptype == 1) {
        printf("Input %lu X %lu Matrix\n", mat->rows, mat->rows);
        _readCOO(mat);
    } //read in COO implementation
    else if(mat->imptype == 2) {
        printf("Input %lu X %lu Matrix\n", mat->rows, mat->rows);
        _readCSR(mat);
    } //read in CSR implementation
    else {
        _flag = 0001;
    }
    return;
}

/*print_functions.c*/

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
        _flag = 0001;//matrix not initialised or initialised incorrectly
    }
    return;
}

/*delete_functions.c*/

void _deleteCSR(SparseMat *mat) {
    //in function variables
    CSRNode *temp_arr = NULL;
    ulint *temp_row_entries = NULL;
    CSRSparse *temp_csr = NULL;
    //actual code
    if(mat->csr_mat == NULL) {
        return;
    } //checks whether the matrix is already empty
    else {
        temp_arr = mat->csr_mat->arr;
        temp_csr = mat->csr_mat;
        temp_row_entries = mat->csr_mat->row_entries;
        mat->csr_mat->arr = NULL;
        mat->csr_mat->row_entries = NULL;
        mat->csr_mat = NULL;
        free(temp_arr);
        free(temp_csr);
        free(temp_row_entries);
    }
    return;
}

void _deleteCOO(SparseMat *mat) {
    //in function variables
    COONode *temp_arr = NULL;
    COOSparse *temp_coo = NULL;
    //actual code
    if(mat->coo_mat == NULL) {
        return;
    } //checks whether the matrix is already empty
    else {
        temp_arr = mat->coo_mat->arr;
        temp_coo = mat->coo_mat;
        mat->coo_mat->arr = NULL;
        mat->coo_mat = NULL;
        free(temp_arr); // frees the coo node array
        free(temp_coo); // frees the coo structure variable
    }
    return;
}

void _deleteAOL(SparseMat *mat) {
    //in function variables
    AOLNode *curr_ent = NULL, *temp = NULL;
    AOLNode **temp_rows = NULL;
    AOLSparse *temp_aol = NULL;
    int i;
    //actual code
    if(mat->aol_mat == NULL) {
        return;
    } // checks whether the matrix is empty already
    for(i = 0; i < mat->rows; i++) {
        curr_ent = mat->aol_mat->rows[i];
        mat->aol_mat->rows[i] = NULL;
        while(curr_ent != NULL) {
            temp = curr_ent;
            curr_ent = curr_ent->next;
            free(temp);
        }
    } // deletes all the data nodes
    temp_rows = mat->aol_mat->rows; 
    free(temp_rows); //deletes the double node pointer array
    temp_aol = mat->aol_mat;
    free(temp_aol); //deletes the AOLSparse variable
    return;
}

void deleteSparseMat(SparseMat *mat) {
    if(mat->imptype == 0) {
        _deleteAOL(mat); 
    }
    else if(mat->imptype == 1) {
        _deleteCOO(mat);
    }
    else if(mat->imptype == 2) {
        _deleteCSR(mat);
    }
    else {
        _flag = 0001;
    }
    mat->nnz = 0; //sets the number of non zero entries in the matrix to zero
    return;
}

/*******************************************************************/

void checkErr(sint f) {
    printf("Executed with code: %hd\n", f);
    return;
}

int main() {
    SparseMat mat;
    initSparseMat(&mat, 3, 3, 0);
    checkErr(_flag);
    readSparseMat(&mat);
    checkErr(_flag);
    printSparseMat(&mat);
    checkErr(_flag);
    deleteSparseMat(&mat);
    checkErr(_flag);
    printSparseMat(&mat);
    checkErr(_flag);
    return 0;
}