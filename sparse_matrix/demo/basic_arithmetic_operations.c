#include "head.h"

SparseMat *addAOL(SparseMat *mat1, SparseMat *mat2) {
    // Check for dimension mismatch
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Matrices must have the same dimensions.\n");
        _flag = 4001;  // Set error code for dimension mismatch
        return NULL;
    }

    ulint rows = mat1->rows;
    ulint cols = mat1->cols;

    // Initialize the result matrix
    SparseMat *result = (SparseMat *)malloc(sizeof(SparseMat));
    if (result == NULL) {
        _flag = 2003;  // Memory allocation error
        return NULL;
    }
    initSparseMat(result, rows, cols, 0);
    if (_flag != 0) {
        free(result);
        return NULL;
    }

    for (ulint i = 0; i < rows; i++) {
        AOLNode *current1 = mat1->aol_mat->rows[i];
        AOLNode *current2 = mat2->aol_mat->rows[i];
        AOLNode **lastPtr = &(result->aol_mat->rows[i]);

        while (current1 != NULL && current2 != NULL) {
            if (current1->col == current2->col) {
                lint sum = current1->data + current2->data;
                if (sum != 0) {  // Only include non-zero sums
                    *lastPtr = _newAOLNode(sum, current1->col);
                    if (*lastPtr == NULL)
                        return NULL;  // Handle memory allocation error
                    lastPtr = &((*lastPtr)->next);
                    result->nnz++;
                }
                current1 = current1->next;
                current2 = current2->next;
            } else if (current1->col < current2->col) {
                *lastPtr = _newAOLNode(current1->data, current1->col);
                if (*lastPtr == NULL)
                    return NULL;  // Handle memory allocation error
                lastPtr = &((*lastPtr)->next);
                result->nnz++;
                current1 = current1->next;
            } else {
                *lastPtr = _newAOLNode(current2->data, current2->col);
                if (*lastPtr == NULL)
                    return NULL;  // Handle memory allocation error
                lastPtr = &((*lastPtr)->next);
                result->nnz++;
                current2 = current2->next;
            }
        }

        // Process remaining elements in mat1
        while (current1 != NULL) {
            *lastPtr = _newAOLNode(current1->data, current1->col);
            if (*lastPtr == NULL)
                return NULL;  // Handle memory allocation error
            lastPtr = &((*lastPtr)->next);
            result->nnz++;
            current1 = current1->next;
        }

        // Process remaining elements in mat2
        while (current2 != NULL) {
            *lastPtr = _newAOLNode(current2->data, current2->col);
            if (*lastPtr == NULL)
                return NULL;  // Handle memory allocation error
            lastPtr = &((*lastPtr)->next);
            result->nnz++;
            current2 = current2->next;
        }
    }

    _flag = 0;  // Indicate success
    return result;
}
//checked
//Subtraction of two matirices of same order.

SparseMat *subAOL(SparseMat *mat1, SparseMat *mat2) {
    // Check for dimension mismatch
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Matrices must have the same dimensions.\n");
        _flag = 4001;  // Set error code for dimension mismatch
        return NULL;
    }

    ulint rows = mat1->rows;
    ulint cols = mat1->cols;

    // Initialize the result matrix
    SparseMat *result = (SparseMat *)malloc(sizeof(SparseMat));
    if (result == NULL) {
        _flag = 2003;  // Memory allocation error
        return NULL;
    }
    initSparseMat(result, rows, cols, 0);
    if (_flag != 0) {
        free(result);
        return NULL;
    }

    for (ulint i = 0; i < rows; i++) {
        AOLNode *current1 = mat1->aol_mat->rows[i];
        AOLNode *current2 = mat2->aol_mat->rows[i];
        AOLNode **lastPtr = &(result->aol_mat->rows[i]);

        while (current1 != NULL && current2 != NULL) {
            if (current1->col == current2->col) {
                lint sub = current1->data - current2->data;
                if (sub != 0) {  // Only include non-zero sums
                    *lastPtr = _newAOLNode(sub, current1->col);
                    if (*lastPtr == NULL)
                        return NULL;  // Handle memory allocation error
                    lastPtr = &((*lastPtr)->next);
                    result->nnz++;
                }
                current1 = current1->next;
                current2 = current2->next;
            } else if (current1->col < current2->col) {
                *lastPtr = _newAOLNode(current1->data, current1->col);
                if (*lastPtr == NULL)
                    return NULL;  // Handle memory allocation error
                lastPtr = &((*lastPtr)->next);
                result->nnz++;
                current1 = current1->next;
            } else {
                *lastPtr = _newAOLNode(-(current2->data), current2->col);
                if (*lastPtr == NULL)
                    return NULL;  // Handle memory allocation error
                lastPtr = &((*lastPtr)->next);
                result->nnz++;
                current2 = current2->next;
            }
        }

        // Process remaining elements in mat1
        while (current1 != NULL) {
            *lastPtr = _newAOLNode(current1->data, current1->col);
            if (*lastPtr == NULL)
                return NULL;  // Handle memory allocation error
            lastPtr = &((*lastPtr)->next);
            result->nnz++;
            current1 = current1->next;
        }

        // Process remaining elements in mat2
        while (current2 != NULL) {
            *lastPtr = _newAOLNode(-(current2->data), current2->col);
            if (*lastPtr == NULL)
                return NULL;  // Handle memory allocation error
            lastPtr = &((*lastPtr)->next);
            result->nnz++;
            current2 = current2->next;
        }
    }

    _flag = 0;  // Indicate success
    return result;
}
//checked

//transpose function

int compareCOO(const void *a, const void *b) {
    COONode *nodeA = (COONode *)a;
    COONode *nodeB = (COONode *)b;

    if (nodeA->row != nodeB->row) {
        return (nodeA->row - nodeB->row);
    }
    return (nodeA->col - nodeB->col);
}

void transpose(SparseMat *mat) {
    if (mat->aol_mat) {
        SparseMat *temp;
        temp = (SparseMat *) malloc(sizeof(SparseMat));
        if(temp == NULL) {
            _flag = 0001; return;
        }
        initSparseMat(temp, mat->rows, mat->cols, 1);
        if(_flag == 1002) return;
        convAOLtoCOO(mat, temp);
        if(_flag == 5001 || _flag == 1002) return;
        deleteSparseMat(mat);
        *mat = *temp;
    }

    // Ensure COO matrix is initialized correctly
    if (mat->coo_mat == NULL || mat->coo_mat->arr == NULL) {
        printf("Error: COO matrix not initialized correctly.\n");
        _flag = 3001;  // Error flag for transposition
        return;
    }

    // Transpose by swapping rows and columns in COO representation
    for (ulint i = 0; i < mat->nnz; i++) {
        ulint temp_val = mat->coo_mat->arr[i].col;
        mat->coo_mat->arr[i].col = mat->coo_mat->arr[i].row;
        mat->coo_mat->arr[i].row = temp_val;
    }

    // Sort the COO representation after transposing
    qsort(mat->coo_mat->arr, mat->nnz, sizeof(COONode), compareCOO);

    _flag = 0;  // Transpose successful
}

void scalarMultiplyAOL(SparseMat *mat, lint scalar) {

     if (mat == NULL || mat->aol_mat == NULL) {
        _flag = 3002; // matrix contains no data;
        return;
    }

    for (ulint i = 0; i < mat->rows; i++) {
        AOLNode *current = mat->aol_mat->rows[i];
        while (current != NULL) {
            current->data *= scalar;
            current = current->next;
        }
    }
}
//checked

lint trace(SparseMat *mat) {
    if (mat->aol_mat) {
        SparseMat *temp;
        temp = (SparseMat *) malloc(sizeof(SparseMat));
        if(temp == NULL) {
            _flag = 0001; return;
        }
        initSparseMat(temp, mat->rows, mat->cols, 1);
        if(_flag == 1002) return;
        convAOLtoCOO(mat, temp);
        if(_flag == 5001 || _flag == 1002) return;
        deleteSparseMat(mat);
        *mat = *temp;} else if (mat->csr_mat) {
        // convCSRtoCOO(mat);
        // Handle CSR conversion if needed
    }

    // Ensure COO matrix is initialized correctly
    if (mat->coo_mat == NULL || mat->coo_mat->arr == NULL) {
        printf("Error: COO matrix not initialized correctly.\n");
        _flag = 3001;  // Error flag for transposition
        return _flag;
    }

    _printCOO(mat);
    lint trace = 0;

    // Transpose by swapping rows and columns in COO representation
    for (int i = 0; i < mat->nnz; i++) {
        if (mat->coo_mat->arr[i].col == mat->coo_mat->arr[i].row) {
            trace += mat->coo_mat->arr[i].data;
        }
    }
    _flag = 0;  // Transpose successful
    _printCOO(mat);
    return trace;
}
//trace unchecked 

SparseMat *_copySparseMatrix(SparseMat *mat) {
    // Allocate memory for the copied matrix
    SparseMat *copyMat = (SparseMat *)malloc(sizeof(SparseMat));
    if (!copyMat) {
        printf("Memory allocation failed for _copySparseMatrix.\n");
        return NULL;
    }

    // Initialize the copied matrix
    initSparseMat(copyMat, mat->rows, mat->cols, mat->imptype);

    // Copy COO representation if it exists
    if (mat->coo_mat != NULL) {
        copyMat->nnz = mat->nnz;
        copyMat->coo_mat->arr = (COONode *)malloc(mat->nnz * sizeof(COONode));
        for (ulint i = 0; i < mat->nnz; i++) {
            copyMat->coo_mat->arr[i].row = mat->coo_mat->arr[i].row;
            copyMat->coo_mat->arr[i].col = mat->coo_mat->arr[i].col;
            copyMat->coo_mat->arr[i].data = mat->coo_mat->arr[i].data;
        }
    }

    return copyMat;
}

bool __isEqual(SparseMat *mat1, SparseMat *mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols ||
        mat1->nnz != mat2->nnz) {
        printf("Matrix dimensions or nnz mismatch.\n");
        return false;
    }

    for (ulint i = 0; i < mat1->nnz; i++) {
        if (mat1->coo_mat->arr[i].row != mat2->coo_mat->arr[i].row ||
            mat1->coo_mat->arr[i].col != mat2->coo_mat->arr[i].col ||
            mat1->coo_mat->arr[i].data != mat2->coo_mat->arr[i].data) {
            return false;
        }
    }
    return true;
}

bool isSymmetric(SparseMat *mat) {
    if (mat->rows != mat->cols) {
        return false;  // Non-square matrices cannot be symmetric
    }
    else if(mat->imptype == 0) {
        SparseMat *temp;
        temp = (SparseMat *) malloc(sizeof(SparseMat));
        if(temp == NULL) {
            _flag = 0001; return false;
        }
        initSparseMat(temp, mat->rows, mat->cols, 1);
        if(_flag == 1002) return false;
        convAOLtoCOO(mat, temp);
        if(_flag == 5001 || _flag == 1002) return false;
        deleteSparseMat(mat);
        *mat = *temp;    
    }

    SparseMat *copiedMat = _copySparseMatrix(mat);
    if (!copiedMat) {
        printf("Error creating a copy of the matrix.\n");
        return false;
    }

    // Step 2: Transpose the copied matrix
    transpose(copiedMat);

    // Step 3: Compare the original matrix with the transposed matrix
    bool symmetric = _isEqual(mat, copiedMat);

    // Step 4: Free the copied matrix memory

    return symmetric;
}

SparseMat *dotProductAOL(SparseMat *mat1, SparseMat *mat2) {
    // Check for dimension mismatch
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Matrices must have the same dimensions.\n");
        _flag = 4001;  // Set error code for dimension mismatch
        return NULL;
    }

    ulint rows = mat1->rows;
    ulint cols = mat1->cols;

    // Initialize the result matrix
    SparseMat *result = (SparseMat *)malloc(sizeof(SparseMat));
    if (result == NULL) {
        _flag = 2003;  // Memory allocation error
        return NULL;
    }
    initSparseMat(result, rows, cols, 0);
    if (_flag != 0) {
        free(result);
        return NULL;
    }

    // Traverse each row of the matrices
    for (ulint i = 0; i < rows; i++) {
        AOLNode *current1 = mat1->aol_mat->rows[i];
        AOLNode *current2 = mat2->aol_mat->rows[i];
        AOLNode **lastPtr = &(result->aol_mat->rows[i]);

        // Traverse through non-zero elements in both matrices
        while (current1 != NULL && current2 != NULL) {
            if (current1->col == current2->col) {
                // Element-wise multiplication for matching column indices
                lint product = current1->data * current2->data;
                if (product != 0) {  // Only store non-zero results
                    *lastPtr = _newAOLNode(product, current1->col);
                    if (*lastPtr == NULL) {
                        return NULL;  // Handle memory allocation error
                    }
                    lastPtr = &((*lastPtr)->next);
                    result->nnz++;  // Increase non-zero count
                }
                current1 = current1->next;
                current2 = current2->next;
            } else if (current1->col < current2->col) {
                current1 = current1->next;
            } else {
                current2 = current2->next;
            }
        }
    }

    _flag = 0;  // Indicate success
    return result;
}



