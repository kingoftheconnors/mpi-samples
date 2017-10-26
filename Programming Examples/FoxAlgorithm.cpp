//module load openmpi-x86_64

#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
  int n, myid, numprocs, i;
  int const MATRIX_SIZE = 3;
  int A[MATRIX_SIZE][MATRIX_SIZE] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
  };
  int B[MATRIX_SIZE][MATRIX_SIZE] = {
    {1,0,0},
    {0,1,0},
    {0,0,1}
  };
  //Answer matrix. Starts empty
  int C[MATRIX_SIZE][MATRIX_SIZE] = { {0} };
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  //Abort if there is not the right number of processes being used
  if(numprocs != MATRIX_SIZE*MATRIX_SIZE) {
    printf("You are using the wrong number of processes! You should be using %d processes!\n", MATRIX_SIZE*MATRIX_SIZE);
    return 0;
  }

  //initialize status for receiving and variables-to-send
  MPI_Status status;
  int aVar = 0;
  int bVar = 0;

  MPI_Scatter(A, 1, MPI_INT, &aVar, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(B, 1, MPI_INT, &bVar, 1, MPI_INT, 0, MPI_COMM_WORLD);

  //Create Communicators
  int myRow = myid/MATRIX_SIZE;
  MPI_Comm rowComm;
  MPI_Comm_split(MPI_COMM_WORLD, myRow, myid, &rowComm);
  //Initialize temp variables used in Roll Back
  int myA = aVar;
  int tempB = 0; int stageRoot = 0;
  //Fox Algorithm Loop
  for(int stage=0; stage<MATRIX_SIZE; stage++) {
      //Broadcast A
	//Reinitialize aVar to the value from A the process is holding
	//This aVar will be broadcasted or replaced depending on the stage
	aVar = myA;
	//Set stageRoot, which sets which element in a row broadcasts its aVar
	stageRoot = (myRow+stage)%MATRIX_SIZE;
	MPI_Bcast(&aVar, 1, MPI_INT, stageRoot, rowComm);
      //Multiply
      C[myid/MATRIX_SIZE][myid % MATRIX_SIZE] += aVar*bVar;
      //Roll Back B
      MPI_Sendrecv(&bVar, 1, MPI_INT, (myid+(MATRIX_SIZE*(MATRIX_SIZE-1)))%(MATRIX_SIZE*MATRIX_SIZE), 3,
		   &tempB, 1, MPI_INT, (myid+MATRIX_SIZE)%(MATRIX_SIZE*MATRIX_SIZE), 3, MPI_COMM_WORLD, &status);
      bVar = tempB;
  }

  //Reduce all values into a single answer to rank 0
  int finalC[MATRIX_SIZE][MATRIX_SIZE] = { {0} };
  MPI_Reduce(&C, &finalC, MATRIX_SIZE*MATRIX_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  //Rank 0 prints final answer
  if(myid==0) {
     for(int i=0; i<MATRIX_SIZE; i++) {
	for(int j=0; j<MATRIX_SIZE; j++) {
	  printf("%d, ", finalC[i][j]);
	}
	printf("\n");
     }
  }
  MPI_Comm_free(&rowComm);
  MPI_Finalize();
  return 0;
}


