#include<stdlib.h>
#include<stdio.h>
#define MATSIZE 8

void freeMatrix(int n, int ** matrix);
int readMatrixSize(char * filename);
int **readMatrix(char * filename);
void denseMatrixMult(int **matrix1, int **matrix2, int ***resultMatrix, int n);
void initMatrix(int ***matrix, int n);
int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n);
int **sub(int ** A, int ** B, int x1, int y1, int x2, int y2, int n);
void printMatrix(int n, int ** A);
