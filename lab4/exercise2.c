#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double **data; // use double ** to allocate dynamic memory
  int nrows;
  int ncols;
} Matrix;

void printmat(Matrix *M);
void matrixmult(Matrix *A, Matrix *B, Matrix *C);
Matrix *createMatrix(int nrows, int ncols);
void destroyMatrix(Matrix *M);

int main(int argc, char *argv[])
{

  Matrix *A = createMatrix(3, 2);
  A->data[0][0] = 1.2;
  A->data[0][1] = 2.3;
  A->data[1][0] = 3.4;
  A->data[1][1] = 4.5;
  A->data[2][0] = 5.6;
  A->data[2][1] = 6.7;
  printmat(A);

  Matrix *B = createMatrix(2, 3);
  B->data[0][0] = 5.5;
  B->data[0][1] = 6.6;
  B->data[0][2] = 7.7;
  B->data[1][0] = 1.2;
  B->data[1][1] = 2.1;
  B->data[1][2] = 3.3;
  printmat(B);

  Matrix *C = createMatrix(3, 3);
  matrixmult(A, B, C);
  printmat(C);

  destroyMatrix(A);
  destroyMatrix(B);
  destroyMatrix(C);

  return 0;
}

// creates a matrix with nrows rows and ncols columns
Matrix *createMatrix(int nrows, int ncols)
{
  Matrix *M = malloc(sizeof(Matrix));
  M->nrows = nrows;
  M->ncols = ncols;
  M->data = malloc(nrows * sizeof(double *));
  for (int i = 0; i < nrows; i++) {
    M->data[i] = malloc(ncols * sizeof(double));
  }
  return M;
}

// deallocates memory for a matrix
void destroyMatrix(Matrix *M)
{
  for (int i = 0; i < M->nrows; i++) {
    free(M->data[i]); 
  }
  free(M->data);
  free(M);
}

// prints a matrix
void printmat(Matrix *M)
{
  for (int i = 0; i < M->nrows; i++) {
    for (int j = 0; j < M->ncols; j++) {
      printf("%f ", M->data[i][j]);
    }
    printf("\n");
  }
}

// multiplies matrices A and B, stores result in matrix C
void matrixmult(Matrix *A, Matrix *B, Matrix *C)
{
  for (int i = 0; i < A->nrows; i++) {
    for (int j = 0; j < B->ncols; j++) {
      double sum = 0.0;
      for (int k = 0; k < A->ncols; k++) {
        sum += A->data[i][k] * B->data[k][j];
      }
      C->data[i][j] = sum;
    }
  }
}