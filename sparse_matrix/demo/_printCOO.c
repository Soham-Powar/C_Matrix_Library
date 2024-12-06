void _printCOO(SparseMat *mat) {
    if (mat == NULL || mat->coo_mat == NULL || mat->coo_mat->arr == NULL) {
        printf("Matrix is not initialized or is empty.\n");
        return;
    }

    COOSparse *temp = mat->coo_mat;
    ulint rows = mat->rows;
    ulint cols = mat->cols;
    ulint nnz = mat->nnz;

    // Print matrix row by row
    for (ulint i = 0; i < rows; i++) {
        for (ulint j = 0; j < cols; j++) {
            int found = 0;  // Flag to track if the current (i, j) has a value
            for (ulint k = 0; k < nnz; k++) {
                if (temp->arr[k].row == i && temp->arr[k].col == j) {
                    printf("%ld ", temp->arr[k].data);
                    found = 1;
                    break;  // Exit loop once the value is printed
                }
            }
            if (!found) {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
