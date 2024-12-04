// same as input taking from user, here we are taking input from file


// Precondition :
//  taking input as file
//  reading from file and storing in matrix
//  nnz varable to store number of non zero elements in matrix, initailly set to zero


// Postconditon :
// The matrix is filled with non-zero elements
// The mat pointer will point to a newly allocated AOL
//nnz variable is updated to reflect the number of non-zero elements in the matrix.
            
void readAOL(AOLSparse **mat, FILE *file, int *nnz) {
    int rows, cols;
    char line[INT_MAX];

    // Reading the number of rows and columns
    char *p = fgets(line, sizeof(line), file);
    if(!p) {
        return;
    }
    sscanf(line, "%d %d", &rows, &cols);

    // Allocate memory for the AOLSparse structure and initialize row pointers
    *mat = (AOLSparse *)malloc(sizeof(AOLSparse));
    (*mat)->row = (AOLNode **)calloc(rows, sizeof(AOLNode *)); // Initialize the row pointers to NULL

    // For each row, read the elements and check for non-zero elements
    for (int i = 0; i < rows; i++) {
        AOLNode *last = NULL; // Initialize last to NULL for each row

        char *q = fgets(line, sizeof(line), file);
        if(!q) {
            return;
        }
        char *token = strtok(line, ", \t\n");

        int j = 0; // Column index
        while (token != NULL) {
            long value;
            sscanf(token, "%ld", &value);  // Read value from the token

            if (value != 0) {
                // Increment the non-zero element count
                (*nnz)++;

                // Create a new node for the current non-zero element
                AOLNode *newNode = (AOLNode *)malloc(sizeof(AOLNode));
                newNode->data = value;
                newNode->col = j;
                newNode->next = NULL;

                // Insert the new node into the linked list for the current row
                if ((*mat)->row[i] == NULL) {
                    // First node in the row's list
                    (*mat)->row[i] = newNode;
                } else {
                    // Append the new node at the end of the list
                    last->next = newNode;
                }
                // Update last to the new node
                last = newNode;
            }

            token = strtok(NULL, ", \t\n");  // Getting the next token
            j++;
        }
    }
}

