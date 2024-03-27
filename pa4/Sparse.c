/****************************************************************************************
Ann Sasi
pa4
CruzID asasi
Sparse.c

*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

int main(int argc, char *argv[]){
    FILE *in, *out;
    int n, aEnt, bEnt;
    // Check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files
    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    fscanf(in, "%d %d %d", &n, &aEnt, &bEnt);


    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    for (int i = 0; i < aEnt; i++){
        int col, row;
        double val;
        fscanf(in,"%d %d %lf", &row, &col, &val);
        changeEntry(A, row, col, val); // Assuming A is defined and changeEntry works as intended
    }
    for (int i = 0; i < bEnt; i++){
        int col, row;
        double val;
        fscanf(in,"%d %d %lf", &row, &col, &val);
        changeEntry(B, row, col, val); // Assuming A is defined and changeEntry works as intended
        }

    fprintf(out, "A has %d non-zero entries: \n", aEnt);
    printMatrix(out, A);
    fprintf(out, "B has %d non-zero entries: \n", bEnt);
    printMatrix(out, B);
    Matrix C = copy(A);
    scalarMult(1.5,C);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    Matrix D = sum(A,B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);
    Matrix E = sum(A,A);
    fprintf(out, "A+A = \n");
    printMatrix(out, E);
    Matrix F =  diff(B,A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);
    Matrix G =  diff(A,A);
    fprintf(out, "A-A =\n");
    printMatrix(out, G);
    Matrix H =  transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, H);
    Matrix I =  product(A,B);
    fprintf(out, "A*B =\n");
    printMatrix(out, I);
    Matrix J =  product(B,B);
    fprintf(out, "B*B =\n");
    printMatrix(out, J);

    fclose(in);
    fclose(out);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&I);
    freeMatrix(&J);
    return 0;
}