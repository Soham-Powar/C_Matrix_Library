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
        AOLNode *current1 = mat1->aol_mat->row[i];
        AOLNode *current2 = mat2->aol_mat->row[i];
        AOLNode **lastPtr = &(result->aol_mat->row[i]);

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
        AOLNode *current1 = mat1->aol_mat->row[i];
        AOLNode *current2 = mat2->aol_mat->row[i];
        AOLNode **lastPtr = &(result->aol_mat->row[i]);

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


//transpose function

void transpose(SparseMat *mat) {
    if (mat->aol_mat) {
        convAOLtoCOO(mat);

        if (_flag != 0) {
            printf("Error during AOL to COO conversion. Aborting transpose.\n");
            return;
        }
        // _deleteAOL(
        //     mat);  // Delete AOL representation after successful conversion
    } else if (mat->csr_mat) {
        // convCSRtoCOO(mat);
        // Handle CSR conversion if needed
    }

    // Ensure COO matrix is initialized correctly
    if (mat->coo_mat == NULL || mat->coo_mat->arr == NULL) {
        printf("Error: COO matrix not initialized correctly.\n");
        _flag = 3001;  // Error flag for transposition
        return;
    }

    _printCOO(mat);

    // Transpose by swapping rows and columns in COO representation
    for (int i = 0; i < mat->nnz; i++) {
        int temp_val = mat->coo_mat->arr[i].col;
        mat->coo_mat->arr[i].col = mat->coo_mat->arr[i].row;
        mat->coo_mat->arr[i].row = temp_val;
    }

    _flag = 0;  // Transpose successful
    _printCOO(mat);
}

void scalarMultiplyAOL(SparseMat *mat, lint scalar) {

     if (mat == NULL || mat->aol_mat == NULL) {
        _flag = 3002; // matrix contains no data;
        return;
    }

    for (ulint i = 0; i < mat->rows; i++) {
        AOLNode *current = mat->aol_mat->rows[i];
        while (current != NULL) {
            current->val *= scalar;
            current = current->next;
        }
    }
}


