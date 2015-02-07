#include "assignment1.h"

void p1(void)
{
    int **matrix;
    initMatrix(&matrix,MATSIZE);
    printMatrix(MATSIZE,matrix);
    freeMatrix(MATSIZE, matrix);
}

void p2(void)
{
    int ** matrix1=readMatrix("matrix1.txt");
    printMatrix(MATSIZE,matrix1);
    freeMatrix(MATSIZE, matrix1);
}

void p3a(void)
{
    int ** matrix1=readMatrix("matrix1.txt");
    int ** matrix2=readMatrix("matrix2.txt");
    int ** sumMatrix = sum(matrix1, matrix2, 1, 1, 0, 1, 3);
    printMatrix(MATSIZE,matrix1);
    printMatrix(MATSIZE,matrix2);
    printMatrix(3,sumMatrix);
    freeMatrix(MATSIZE, matrix1);
    freeMatrix(MATSIZE, matrix2);
    freeMatrix(3, sumMatrix);
}

void p3b(void)
{
    int ** matrix1=readMatrix("matrix1.txt");
    int ** matrix2=readMatrix("matrix2.txt");
    int ** subMatrix = sub(matrix1, matrix2, 1, 1, 0, 1, 3);
    printMatrix(MATSIZE,matrix1);
    printMatrix(MATSIZE,matrix2);
    printMatrix(3,subMatrix);
    freeMatrix(MATSIZE, matrix1);
    freeMatrix(MATSIZE, matrix2);
    freeMatrix(3, subMatrix);
}

void p4(void)
{
    char dataFileMat1[]="matrix1.txt";
    char dataFileMat2[]="matrix2.txt";
    int ** matrix1=readMatrix(dataFileMat1);
    int ** matrix2=readMatrix(dataFileMat2);
    int ** resultingMatrix;
    denseMatrixMult(matrix1, matrix2, &resultingMatrix, MATSIZE);
    printMatrix(MATSIZE,resultingMatrix);
    freeMatrix(MATSIZE,resultingMatrix);
    freeMatrix(MATSIZE,matrix1);
    freeMatrix(MATSIZE,matrix2);
}

int main( int argc, char *argv[] )
{
    if( argc < 2 )
   	{
        printf("Expecting at least one argument. Please try again\n");
   	}
    else if(argc==2)
    {
        if(atoi(argv[1])==3)
        {
            printf("Expecting two arguments for this part. Please try again.\n");
        }
        else
        {
            if(atoi(argv[1])==1)
            {
                p1();
            }
            else if(atoi(argv[1])==2)
            {
                p2();
            }
            else if(atoi(argv[1])==4)
            {
                p4();
            }
            else
            {
                printf("Incorrect argument supplied.\n");
            }
        }
    }
    else if(argc==3)
    {
        if(atoi(argv[1])!=3)
        {
            printf("Expecting two arguments only for Part 3. Please try again.\n");
        }
        else
        {
            if(atoi(argv[2])==1)
            {
                p3a();
            }
            else if(atoi(argv[2])==2)
            {
                p3b();
            }
        }
    }
    else
    {
        printf("The argument supplied is %s\n", argv[1]);
    }
}

