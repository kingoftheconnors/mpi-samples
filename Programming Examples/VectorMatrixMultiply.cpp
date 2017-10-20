//module load openmpi-x86_64

#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
  int n, myid, numprocs, i;
  int const MATRIX_SIZE = 3;
  int matrix[MATRIX_SIZE][MATRIX_SIZE] = {
    {1,2,3},
    {4,5,6},
    {3,2,1},
  };
  int vector[MATRIX_SIZE] = {1,3,1};
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  //initialize array that will have all the info as well as the array/vector that will have the answer
  int arrayData[MATRIX_SIZE] = {0};
  MPI_Status status;
  if (myid == 0) {
    for(int i=0; i<MATRIX_SIZE; i++) {
      for(int j=0; j<MATRIX_SIZE; j++) {
        arrayData[j] = matrix[j][i];
      }
      arrayData[MATRIX_SIZE] = vector[i];
      MPI_Send(&arrayData, MATRIX_SIZE+1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
      //Free arrayData for when all arrays are reduced
      for(int j=0; j<MATRIX_SIZE; j++) {
	arrayData[j] = 0;
      }
    }
  }
  else {
    int tempArray[MATRIX_SIZE+1] = {0};
    //for(int i=0; i<1; i++) {
      //Receive info
      MPI_Recv(&tempArray, MATRIX_SIZE+1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      for(int j=0; j<MATRIX_SIZE; j++) {
        arrayData[j]=arrayData[j] + (tempArray[j]*tempArray[MATRIX_SIZE]);
      }
    //}
  }
  //Reduce all arrays into a single answer
  int finalVector[MATRIX_SIZE+1] = {0};
  MPI_Reduce(&arrayData, &finalVector, MATRIX_SIZE+1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if(myid==0) {
    for(int i=0; i<MATRIX_SIZE; i++) {
      printf("%d\n", finalVector[i]);
    }
  }
  MPI_Finalize();
  return 0;
}


