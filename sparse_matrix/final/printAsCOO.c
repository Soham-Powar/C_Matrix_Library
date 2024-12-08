#include "head.h"

void printAsCOO(SparseMat *mat) {
    if(mat == NULL) {
        _flag = 0001; return;
    } //if matrix is not intialised correctly
    else if(mat->imptype = 0) {
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
    } //if matrix is of aol type convert it coo

    //in function variables
    

    //actual code
    for(i = 0; i < nnz; i++) {

    }
}