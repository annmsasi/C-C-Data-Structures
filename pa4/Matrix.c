/****************************************************************************************
Ann Sasi
pa4
CruzID asasi
Matrix.c

*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Matrix.h"

typedef struct entryObj{
    int col;
    double val;
}entryObj;

typedef struct entryObj* entry;

typedef struct matrixObj{
    int size;
    int entries;
    List* rows;
}matrixObj;
// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.

entry newEntry(int col, double num){

    entry new = malloc(sizeof(entryObj));
    new -> col = col;
    new -> val = num;
    return new;
}

void freeEntry(entry* x){
    if (x != NULL && *x != NULL) {
        free(*x);
        *x = NULL;}
}

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(matrixObj));
    M -> size = n;
    M -> entries = 0;
    M -> rows = calloc(n+1, sizeof(List));
    for (int i = 1; i<= n; i++){
        M -> rows[i] = newList();
    }
    return M;
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if (pM == NULL || *pM == NULL) return; 
    for (int i = 1; i <= size(*pM); i++){
        List r = (*pM) -> rows[i];
        if (r != NULL){
            clear(r);
        }
    }
    (*pM) -> entries = 0;
    for (int i = 1; i <= (*pM)->size; i++){ 
        freeList(&((*pM)->rows[i]));
    }
    free((*pM)->rows);
    free(*pM);
    *pM = NULL;
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if (M == NULL){
        printf("Matrix Error: calling size() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M -> size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if (M == NULL){
        printf("Matrix Error: calling NNZ() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M -> entries;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        printf("Matrix Error: calling equals() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(A == B){
        return 1;
    }
    if (A -> size != B -> size){
        return 0;
    }
    if ( A -> entries != B -> entries){
        return 0;
    }
    for (int i = 1; i <= A -> entries; i++){
        if ((length(A -> rows[i]) != length(B -> rows[i]))){
            return 0;
        }
        else{
        moveFront(A -> rows[i]);
        moveFront(B -> rows[i]);
        while (index(A->rows[i]) >= 0) {
            if ((((entry)get(A->rows[i]))->col != ((entry)get(B->rows[i]))->col) ||(((entry)get(A->rows[i]))->val != ((entry)get(B->rows[i]))->val) ){
                return 0;
            }
            moveNext(A->rows[i]);
            moveNext(B->rows[i]);
            }
        }
    }
    return 1;
}
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if (M == NULL){
        printf("Matrix Error: calling makeZero() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= M ->entries; i++){
        clear(M -> rows[i]);
    }
    M -> entries = 0;
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        printf("Matrix Error: calling changeEntry() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > size(M) || j < 1 || j > size(M)) {
        printf("Matrix Error: indices out of bounds in changeEntry().\n");
        return; 
    }

    bool entryAdded = false; // Flag to track if entry is added or updated

    moveFront(M->rows[i]);
    while(index(M->rows[i]) >= 0) {
        entry currentEntry = get(M->rows[i]);
        if(currentEntry->col == j) {
            if(x == 0.0) {
                // Assuming you have a function to free the memory for an entry.
                // If not, you'd need to implement it, ensuring it frees the entry itself
                // and any data it might hold.
                freeEntry(&currentEntry); // Free memory for the entry.
                delete(M->rows[i]); // Remove the entry from the list.
                M->entries--;
            } else {
                currentEntry->val = x; // Update the value if x is not 0
            }
            entryAdded = true;
            break;
        } else if(currentEntry->col > j) {
            if(x != 0.0) {
                entry new = newEntry(j, x); // Create a new entry.
                insertBefore(M->rows[i], new); // Insert before if column is greater.
                M->entries++;
                entryAdded = true;
            }
            break;
        }
        moveNext(M->rows[i]);
    }

    if(!entryAdded && x != 0.0) {
        entry news = newEntry(j, x); // Append the new entry if not added or updated.
        append(M->rows[i], news);
        M->entries++;
    }
}


// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if (A == NULL){
        printf("Matrix Error: calling copy() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix(size(A));
    for (int i = 1; i<= (A -> size); i++){
        List row = A -> rows[i];
        moveFront(row);
        while (index(row) >= 0){
            entry new = (entry) get(row);
            changeEntry(B, i, new->col, new->val);
            moveNext(row);
        }
    }
    return B;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if (A == NULL){
        printf("Matrix Error: calling transpose() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix(A -> size);
    for (int i = 1; i<= A -> size; i++){
        List row = A -> rows[i];
        moveFront(row);
        while (index(row) >= 0){
            entry new = (entry) get(row);
            changeEntry(B, new -> col, i,new->val);
            moveNext(row);}
    }
    return B;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if (A == NULL){
        printf("Matrix Error: calling scalarMult() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = copy(A);
    for (int i = 1; i<= (A -> size); i++){
        List row = A -> rows[i];
        moveFront(row);
        while (index(row) >= 0){
            entry new = get(row);
            // double newval = new->val;
            // newval= newval * x;
            new -> val = (new ->val) * x;
            // changeEntry(B, i,new->col, k);
            if ( x == 0.0){
                (B -> entries)--;
            }
            moveNext(row);} 
    }
    return B;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)

Matrix sum(Matrix A, Matrix B) {
    if ((A == NULL) || (B == NULL) || (size(A) != size(B))) {
        printf("Matrix Error: calling sum() on matrices with invalid conditions.\n");
        exit(EXIT_FAILURE);
    }

    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i];
        List rowB = (A == B) ? rowA : B->rows[i];
        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 || index(rowB) >= 0) {
            entry entryA = (index(rowA) >= 0) ? (entry)get(rowA) : NULL;
            entry entryB = (index(rowB) >= 0) ? (entry)get(rowB) : NULL;

            int colA = (entryA != NULL) ? entryA->col : -1;
            int colB = (entryB != NULL) ? entryB->col : -1;

            if (entryA != NULL && (colA < colB || entryB == NULL)) {
                changeEntry(C, i, colA, entryA->val);
                moveNext(rowA);
            } else if (entryB != NULL && (colB < colA || entryA == NULL)) {
                changeEntry(C, i, colB, entryB->val);
                moveNext(rowB);
            } else if (colA == colB && entryA != NULL && entryB != NULL) {
                double sum = entryA->val + entryB->val;
                if (sum != 0.0) {
                    changeEntry(C, i, colA, sum);
                }
                moveNext(rowA);
                if (A != B) { 
                    moveNext(rowB);
                }
            }
        }
    }
    
    return C;
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
        if ((A == NULL) || (size(A) != size(B)) || (B == NULL)){
        printf("Matrix Error: calling diff() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i];
        List rowB = (A == B) ? rowA : B->rows[i];
        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 || index(rowB) >= 0) {
            entry entryA = (index(rowA) >= 0) ? (entry)get(rowA) : NULL;
            entry entryB = (index(rowB) >= 0) ? (entry)get(rowB) : NULL;

            int colA = (entryA != NULL) ? entryA->col : -1;
            int colB = (entryB != NULL) ? entryB->col : -1;

            if (entryA != NULL && (colA < colB || entryB == NULL)) {
                changeEntry(C, i, colA, entryA->val);
                moveNext(rowA);
            } else if (entryB != NULL && (colB < colA || entryA == NULL)) {
                changeEntry(C, i, colB, entryB->val);
                moveNext(rowB);
            } else if (colA == colB && entryA != NULL && entryB != NULL) {
                double diff = entryA->val - entryB->val;
                if (diff != 0.0) {
                    changeEntry(C, i, colA, diff);
                }
                moveNext(rowA);
                if (A != B) { 
                    moveNext(rowB);
                }
            }
        }
    }
    return C;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || size(A) != size(B)) {
        printf("Matrix Error: calling product() on invalid matrices.\n");
        exit(EXIT_FAILURE);
    }

    Matrix C = newMatrix(size(A)); // Assuming square matrices for simplicity.
    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        if (length(rowA) == 0) continue; // Skip if row i in A is empty.

        for (int j = 1; j <= size(B); j++) { // Iterate over all potential columns in B (and rows for result matrix C).
            double dotProduct = 0.0;
            moveFront(rowA);
            while (index(rowA) >= 0) {
                entry entryA = (entry)get(rowA);
                int colA = entryA->col;

                // Attempt to find a matching entry in B's j-th row.
                List rowB = B->rows[j]; // Here, we're treating B's row as if it were a column due to square matrix assumption.
                moveFront(rowB);
                while (index(rowB) >= 0) {
                    entry entryB = (entry)get(rowB);
                    if (entryB->col == colA) {
                        dotProduct += entryA->val * entryB->val;
                        break; // Break since we've found the matching column entry in B's row.
                    }
                    moveNext(rowB);
                }
                moveNext(rowA);
            }

            if (dotProduct != 0.0) {
                changeEntry(C, i, j, dotProduct); // Add the non-zero product to matrix C.
            }
        }
    }
    return C;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if (out == NULL || M == NULL){
        fprintf(stderr, "Matrix Error: calling printMatrix() on an empty or NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++){
        List row = M->rows[i];
        if (length(row) > 0) {  // Check if the row is not empty
            fprintf(out, "%d: ", i);  // Indicate the row number
            moveFront(row);
            while(index(row) >= 0){
                entry new = get(row);
                if (new->val != 0){
                    fprintf(out, "(%d, %.1f) ", new->col, new->val);
                }
                moveNext(row);
            }
            fprintf(out, "\n");  // Print a newline after all entries in a row
        }
    }
}