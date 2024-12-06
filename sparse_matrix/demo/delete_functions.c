#include "head.h"

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
    mat->aol_mat->rows = NULL;
    free(temp_rows); //deletes the double node pointer array
    temp_aol = mat->aol_mat;
    mat->aol_mat = NULL;
    free(temp_aol); //deletes the AOLSparse variable
    return;
}

void deleteSparseMat(SparseMat *mat) {
    if(mat == NULL) {
        _flag = 0001;
    }
    else if(mat->imptype == 0) {
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
    mat->cols = mat->rows = mat->nnz = 0; //sets the number of non zero entries in the matrix to zero
    mat->imptype = -1;
    return;
}