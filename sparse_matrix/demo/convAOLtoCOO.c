void convAOLtoCOO(SparseMat *mat) {
    printf("ds;;\n");

    mat->coo_mat = (COOSparse *)malloc(sizeof(COOSparse));
    mat->coo_mat->arr = (COONode *)malloc(sizeof(COONode) * mat->nnz);

    printf("dsj\n");

    if (mat->coo_mat->arr == NULL) {
        printf("Memory allocation failed for COO matrix!\n");
        return;
    }

    ulint indexCOO = 0;

    for (ulint i = 0; i < mat->rows; i++) {
        AOLNode *current = mat->aol_mat->rows[i];
        while (current != NULL) {
            mat->coo_mat->arr[indexCOO].row = i;
            mat->coo_mat->arr[indexCOO].col = current->col;
            mat->coo_mat->arr[indexCOO].data = current->data;
            indexCOO++;
            current = current->next;
        }
    }
}
