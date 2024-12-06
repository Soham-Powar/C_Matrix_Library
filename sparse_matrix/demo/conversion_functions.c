#include "head.h"

void convAOLtoCOO(SparseMat *aol, SparseMat *coo) {
    //in function variables
    ulint i, coo_index = 0; AOLNode *temp;
    //both matrices are already initialised
    if(aol->nnz == 0) {
        _flag = 5001;
        return;
    }
    coo->nnz = aol->nnz;
    coo->coo_mat->arr = (COONode *) malloc(sizeof(COONode) * coo->nnz);
    if(coo->coo_mat->arr == NULL) {
        _flag = 1002; return;
    }
    for(i = 0; i < aol->rows; i++) {
        temp = aol->aol_mat->rows[i];
        while(temp != NULL) {
            coo->coo_mat->arr[coo_index].data = temp->data;
            coo->coo_mat->arr[coo_index].col = temp->col;
            coo->coo_mat->arr[coo_index].row = i;
            coo_index++; 
        }   
    }
    return;
}

void convAOLtoCSR(SparseMat *aol, SparseMat *csr) {
    //in function variables
    ulint row_count; ulint i; ulint csr_arr_index = 0; ulint csr_row_index = 0;
    AOLNode *temp;
    //both matrices are already initialised
    if(aol->nnz == 0) {
        _flag = 5001; return;
    }
    csr->nnz = aol->nnz;
    csr->csr_mat->arr = (CSRNode *) malloc(sizeof(CSRNode) * csr->nnz);

    for(i = 0; i < aol->rows; i++) {
        row_count = 0;
        temp = aol->aol_mat->rows[i];
        while(temp != NULL) {
            csr->csr_mat->arr[csr_arr_index].data = temp->data;
            csr->csr_mat->arr[csr_arr_index].col = temp->col;
            row_count++;
            temp = temp->next;
            csr_arr_index++;    
        }
        csr->csr_mat->row_entries[csr_row_index] = row_count;
        csr_row_index++;
    }
    return;
}
/*
void convCOOtoAOL() {

}

void convCOOtoCSR() {

}

void convCSRtoAOL() {

}

void convCSRtoCOO() {

}
*/