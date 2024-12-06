
# Sparse Matrix Library in C

This project implements a sparse matrix library in C, supporting three matrix representations: **Array of Lists (AOL)**, **Coordinate List (COO)**, and **Compressed Sparse Row (CSR)**. It provides functions for initialization, reading, printing, and performing various matrix operations like addition, dot product, transposition, and equality checks.

## Features
- **Efficient Storage**: Choose between AOL, COO, and CSR representations.
- **Matrix Operations**: Supports addition, dot product, and transpose.
- **Memory Management**: Includes functions for dynamically managing memory and deleting matrices.
- **Error Handling**: Comprehensive error checking using the `_flag` system.

## Requirements
- C Compiler (e.g., GCC)
- Standard C Libraries (`stdio.h`, `stdlib.h`, `stdbool.h`)

## Setup
Clone this repository and compile the code using a C compiler:
```
git clone <repository_url>
```

## Functions
- **Initialization**: Initializes a sparse matrix in the specified format (AOL, COO, or CSR).
- **Reading**: Reads matrix data from input and stores it in the appropriate format.
- **Matrix Operations**: Performs matrix addition, dot product, transpose, equality checks and more.
- **Memory Management**: Includes functions to delete matrices and free allocated memory.

## Contributing
Feel free to fork this repository, submit issues, or contribute with pull requests.
---
