#include <stdio.h>

int main(int argc, char *argv[])
{
  int const MATRIX_SIZE = 3;
  int A[MATRIX_SIZE][MATRIX_SIZE] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
  };
  int B[MATRIX_SIZE][MATRIX_SIZE] = {
    {2,0,0},
    {0,2,0},
    {0,0,2}
  };
  //Answer matrix. Starts empty
  int C[MATRIX_SIZE][MATRIX_SIZE] = { {0} };

  for(int i=0; i<MATRIX_SIZE; i++) {
    for(int j=0; j<MATRIX_SIZE; j++) {
      for(int k=0; k<MATRIX_SIZE; k++) {
	//A=Column-Oriented and B=Row-Oriented
	C[j][k] += A[j][i] * B[i][k];

	//A=Row-Oriented and B=Column-Oriented
	//C[i][j] += A[i][k] * B[k][j];

	//A=Column-Oriented and B=Column-Oriented
	//C[k][i] += A[k][j] * B[j][i];

	//A=Row-Oriented and B=Row-Oriented
	//C[i][k] += A[i][j] * B[j][k];
      }
    }
  }

  //Prints final answer
     for(int i=0; i<MATRIX_SIZE; i++) {
	for(int j=0; j<MATRIX_SIZE; j++) {
	  printf("%d, ", C[i][j]);
	}
	printf("\n");
     }

  //Terminate
  return 0;
}


