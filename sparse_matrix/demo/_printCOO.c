void _printCOO(SparseMat *mat) {
    if (mat == NULL || mat->coo_mat == NULL || mat->coo_mat->arr == NULL) {
        printf("Matrix is not initialized or is empty.\n");
        return;
    }

    COOSparse *temp = mat->coo_mat;
    ulint rows = mat->rows;
    ulint cols = mat->cols;
    ulint nnz = mat->nnz;
    ulint indexCOO = 0;

    for (ulint i = 0; i < rows; i++) {
        for (ulint j = 0; j < cols; j++) {
            if (indexCOO < nnz && temp->arr[indexCOO].row == i &&
                temp->arr[indexCOO].col == j) {
                printf("%ld ", temp->arr[indexCOO].data);
                indexCOO++;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
