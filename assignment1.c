#include "assignment1.h"

void denseMatrixMult(int ** A, int ** B, int *** resultMatrix, int n)
{
/*
M0 = (A0,0 + A1,1)(B0,0 + B1,1)
M1 = (A1,0 + A1,1)B0,0
M2 = A0,0(B0,1 − B1,1)
M3 = A1,1(B1,0 − B0,0)
M4 = (A0,0 + A0,1)B1,1
M5 = (A1,0 − A0,0)(B0,0 + B0,1)
M6 = (A0,1 − A1,1)(B1,0 + B1,1)
*/
	int **result;
	int **M0, **M1, **M2, **M3, **M4, **M5, **M6;
	int **C00, **C01, **C10, **C11;
	int **tempMat1, **tempMat2; // used to hold the submatrices of size (n/2, n/2)
	int **blankMatrix; // matrix of size (n/2, n/2) with all entries = 0
	int i, j;

	initMatrix(&result, n);

	if (n==1){
		result[0][0] = A[0][0] * B[0][0];
		*resultMatrix = result;
		freeMatrix(n, result);
		return;
	}
	//printf("hi");
	initMatrix(&blankMatrix, n/2);

	printf("hi2\n");
	//M0
	tempMat1 = sum(A, A, 0, 0, n/2, n/2, n/2);
	tempMat2 = sum(B, B, 0, 0, n/2, n/2, n/2);
	denseMatrixMult(tempMat1, tempMat2, &M0, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	//M1
	tempMat1 = sum(A, A, 0, n/2, n/2, n/2, n/2);
	tempMat2 = sum(B, blankMatrix, 0, 0, 0, 0, n/2);
	denseMatrixMult(tempMat1, tempMat2, &M1, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	//M2 = A0,0(B0,1 − B1,1)
	tempMat1 = sum(A, blankMatrix, 0, 0, 0, 0, n/2);
	tempMat2 = sub(B, B, 0, n/2, n/2, n/2, n/2);
	denseMatrixMult(tempMat1, tempMat2, &M2, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	//M3 = A1,1(B1,0 − B0,0)
	tempMat1 = sum(A, blankMatrix, n/2, n/2, 0, 0, n/2);
	tempMat2 = sub(B, B, n/2, 0, 0, 0, n/2);
	denseMatrixMult(tempMat1, tempMat2, &M3, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	//M4 = (A0,0 + A0,1)B1,1
	tempMat1 = sum(A, A, 0, 0, 0, n/2, n/2);
	tempMat2 = sum(B, blankMatrix, n/2, n/2, 0, 0, n/2);
	denseMatrixMult(tempMat1, tempMat2, &M4, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	//M5 = (A1,0 − A0,0)(B0,0 + B0,1)
	tempMat1 = sub(A, A, n/2, 0, 0, 0, n/2);
	tempMat2 = sum(B, B, 0, 0, 0, n/2, n/2);
	denseMatrixMult(tempMat1, tempMat2, &M5, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	//M6 = (A0,1 − A1,1)(B1,0 + B1,1)
	tempMat1 = sub(A, A, 0, n/2, n/2, n/2, n/2);
	tempMat2 = sum(B, B, n/2, 0, n/2, n/2, n/2);
	denseMatrixMult(tempMat1, tempMat2, &M6, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);
	/*
C0,0 =M0 +M3 −M4 +M6
C0,1 = M2 + M4
C1,0 = M1 + M3
C1,1 =M0 −M1 +M2 +M5
*/
	printf("hi3\n");
	//C0,0
	tempMat1 = sum(M0, M3, 0, 0, 0, 0, n/2);
	tempMat2 = sub(tempMat1, M4, 0, 0, 0, 0, n/2);
	C00 = sum(tempMat2, M6, 0, 0, 0, 0, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	//C0,1
	C01 = sum(M2, M4, 0, 0, 0, 0, n/2);

	//C1,0
	C10 = sum(M1, M3, 0, 0, 0, 0, n/2);

	//C1,1
	tempMat1 = sub(M0, M1, 0, 0, 0, 0, n/2);
	tempMat2 = sum(tempMat1, M2, 0, 0, 0, 0, n/2);
	C11 = sum(tempMat2, M5, 0, 0, 0, 0, n/2);
	freeMatrix(n/2, tempMat1);
	freeMatrix(n/2, tempMat2);

	freeMatrix(n/2, M0);
	freeMatrix(n/2, M1);
	freeMatrix(n/2, M2);
	freeMatrix(n/2, M3);
	freeMatrix(n/2, M4);
	freeMatrix(n/2, M5);
	freeMatrix(n/2, M6);

	//filling up result
	for (i = 0; i < n/2; i++){
		for (j = 0; j < n/2; j++){
			result[i][j] = C00[i][j];
		}
	}
	for (i = 0; i < n/2; i++){
		for (j = 0; j < n/2; j++){
			result[i][j+(n/2)] = C01[i][j];
		}
	}
	for (i = 0; i < n/2; i++){
		for (j = 0; j < n/2; j++){
			result[i+(n/2)][j] = C10[i][j];
		}
	}
	for (i = 0; i < n/2; i++){
		for (j = 0; j < n/2; j++){
			result[i+(n/2)][j+(n/2)] = C11[i][j];
		}
	}

	freeMatrix(n/2, C00);
	freeMatrix(n/2, C01);
	freeMatrix(n/2, C10);
	freeMatrix(n/2, C11);
	printf("hi im here\n");
	printMatrix(n, result);
	*resultMatrix = result;
	freeMatrix(n, result);

}

int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n)
{
	int i, j;
	int **res; // declares the double point to store the result of the summation

	initMatrix(&res, n); // initalizes the result as a matrix with n by n elements

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			res[i][j] = A[x1+i][y1+j] + B[x2+i][y2+j]; // stores the sum of the submatrices as
		}						   // as required; since A[x1][y1] and B[x2][y2]
	}							   // are the starts of the submatrices, we just
								   // need to add i and j to them
	return res;
}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n)
{
	int i, j;
	int **res;

	initMatrix(&res, n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			res[i][j] = A[x1+i][y1+j] - B[x2+i][y2+j]; // similar logic as sum() but subtracts instead
		}
	}
	
	return res;
}

void initMatrix(int ***mat,int n)
{
	int i, j;
	int **tempmat = (int **)malloc(sizeof(int*)*(unsigned long)n); // allocates n single pointers of matrix

	for (i = 0; i < n; i++)
	{
		tempmat[i] = (int *)malloc(sizeof(int*)*(unsigned long)n); // allocates memory for the ith single
						 										   // pointer
		for (j = 0; j < n; j++)
		{
			tempmat[i][j] = 0; // initalizes every (i,j)th element = 0
		}
	}

	*mat = tempmat; // assigns the passed in mat to point to tempmat (function edits global mat in place)	
}

int **readMatrix(char * filename)
{
	int i, j;
	int **m; // declares the matrix m to be initialized and have elements stored into
	
	initMatrix(&m, MATSIZE); // initializes the double pointer m with the triple pointer &m

	FILE *fp = fopen(filename, "r");
	for (i=0; i < MATSIZE; i++)
	{
		for (j=0; j < MATSIZE; j++)
		{
			fscanf(fp, "%d", &m[i][j]); // opens the file and scans every element to be placed into m
		}
	}
	fclose(fp);

	return m; // returns the double pointer m
}
void freeMatrix(int n, int ** matrix)
{
	int i;
	
	for (i = 0; i < n; i++)
	{
		free(matrix[i]); // frees the ith single pointer
	}

	free(matrix); // frees the array of single pointers
}

void printMatrix(int n, int ** A)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", A[i][j]); // prints every (i, j)th element
		}
		printf("\n"); // prints a line break after every row
	}

	//freeMatrix(n, A); // frees the passed-in double pointer A
}
