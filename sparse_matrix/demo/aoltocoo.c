#include "head.h"
// SUGGEST CHANGES/IMPROVEMENTS IF NEEDED.

// case 1:
//     // initialises the matrix using COO implementation
//     initAOL(&mat->aol_mat, mat->rows);  // for COO you need AOL
//     initCOO(&mat->coo_mat);
//     break;

/*	As in the switch case we are initializing both aol and coo in the
 *orignal matix itself. This function only has too copy from aol to coo.
 *
 *
 *
 */
void AOLToCOO(SparseMat *mat) {
    mat->coo_mat->arr = (COONode *)malloc(mat->nnz * sizeof(COONode));

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
