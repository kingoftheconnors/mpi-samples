#include <stdio.h>
#include <unistd.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

  //--------------------LOOP-SETUP------------------------//
    int n, myid, numprocs, i;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    int const SIZE_OF_SECTIONS = 30;

    //Check that number of processes is compatible with section size
    if(SIZE_OF_SECTIONS%numprocs != 0) {
	printf("Error: Number of processes incompatible! Degree of multiprogramming must be a divisor of %d! %d does not divide %d.\n", SIZE_OF_SECTIONS, numprocs, SIZE_OF_SECTIONS);
	return 0;
    }

    int mySect[2][2][SIZE_OF_SECTIONS/numprocs][SIZE_OF_SECTIONS];
    //Initialize array to all 0s
    for(int i=0; i<SIZE_OF_SECTIONS/numprocs; i++)
	for(int j=0; j<SIZE_OF_SECTIONS; j++)
	    for(int act=0; act<2; act++) {
		mySect[act][0][i][j]=0;
	    }

    int lastRow[SIZE_OF_SECTIONS] = {0};
    bool printPermission = true;
    int active = 0;
    int nextActive = 1;

    //Initial frame
    for(int act=0; act<=1; act++) {
	mySect[act][0][1][5]=1;
	mySect[act][0][2][6]=1;
	mySect[act][0][2][7]=1;
	mySect[act][0][3][6]=1;
	mySect[act][0][3][5]=1;
    }

    //Send back rank's first line to previous rank so all ranks are synchronized
    MPI_Sendrecv(mySect[nextActive][0][0], SIZE_OF_SECTIONS, MPI_INT, (myid-1+numprocs)%(numprocs), 0,
		&lastRow, SIZE_OF_SECTIONS, MPI_INT, (myid+1)%numprocs, 0, MPI_COMM_WORLD, &status);
    //Set received line to last line for next frame
	for(int j=0; j<SIZE_OF_SECTIONS; j++) {
	    mySect[active][0][(SIZE_OF_SECTIONS/numprocs)-1][j] = lastRow[j];
	}


  //-----------------MAIN-LOOP-BODY------------------//
    while(1==1) {
    nextActive = (active+1)%2;


  //---------------GETTING-FRAME-STATE----------------//
    //Go through the entire table to find neighbors
    for(int i=0; i<SIZE_OF_SECTIONS/numprocs; i++) {
	for(int j=0; j<SIZE_OF_SECTIONS; j++) {
	    //Set d in other array to keep arrays parallel
	    if(mySect[nextActive][0][i][j]!=mySect[active][0][i][j]) {
		mySect[nextActive][0][i][j]=mySect[active][0][i][j];
	    }

	    //Reinitialize number of neighbors to 0
	    mySect[active][1][i][j] = 0;
	    //Check number of neighbors, including ones from other side
	    for(int a=i-1; a<=i+1; a++) {
		//Check to make sure we aren't checking beyond section
		if((i>0 || a>i-1) && (i<(SIZE_OF_SECTIONS/numprocs)-1 || a<i))
		    for(int b=j-1; b<=j+1; b++) {
			//If point is not current point and is active
			if(a!=i || b!=j)
			    if(mySect[active][0][(a+SIZE_OF_SECTIONS)%SIZE_OF_SECTIONS][(b+SIZE_OF_SECTIONS)%SIZE_OF_SECTIONS]==1) {
				//Increase number of recorded adjacent points
				mySect[active][1][i][j]++;
			    }
		    }
	    }
	}
    }

    //Communication Section for last lines (a.k.a first lines of next rank)
	//Send rank's last line of neighbors to next row for population and printing
	    //Create array of last row for rank
	    //Send last row to next rank and receive last row of last rank in separate array
		MPI_Sendrecv(mySect[active][1][(SIZE_OF_SECTIONS/numprocs)-1], SIZE_OF_SECTIONS, MPI_INT, (myid+1)%(numprocs), 0,
			    &lastRow, SIZE_OF_SECTIONS, MPI_INT, (myid-1+numprocs)%(numprocs), 0, MPI_COMM_WORLD, &status);
	    //Add received array of neighbors to first row to get true number of neighbors for that row
		for(int j=0; j<SIZE_OF_SECTIONS; j++) {
		    mySect[active][1][0][j] += lastRow[j];
		}

    //First rank starts with permission to print
    if(myid == 0) {
	printPermission = true;
    }
    else {
	printPermission = false;
    }

    //Rank with permission continues to print, and all others begin blocking to receive to wait until permission is given
    if(printPermission == false) {
	MPI_Recv(&printPermission, 1, MPI::BOOL, myid-1, 1, MPI_COMM_WORLD, &status);
    }


  //------------------PRINTING-FRAME---------------------//
    //First rank prints to set this frame apart from last frame
    if(myid==0) {
	printf("\n\n\n\n\n\n\n");
    }
    //Print entire set (except for last row, which is printed as first row of next rank)
    for(int i=0; i<(SIZE_OF_SECTIONS/numprocs)-1; i++) {
	for(int j=0; j<SIZE_OF_SECTIONS; j++) {
	    //If this point is alive, print and check for overpopulation
	    if(mySect[active][0][i][j]==1) {
		printf("X");
		//printf("%d", myid);
		//printf(" ");

		//Underpopulation
		if(mySect[active][1][i][j]<2) {
		    mySect[nextActive][0][i][j]=0;
		}
		//Overpopulation
		if(mySect[active][1][i][j]>3) {
		    mySect[nextActive][0][i][j]=0;
		}
	    }
	    else {
		//If this point is dead, print a blank and check for activity
		printf(" ");
		//printf("%d", mySect[active][1][i][j]);

		//Bring alive if exactly 3
		if(mySect[active][1][i][j]==3) {
		    mySect[nextActive][0][i][j]=1;
		}
	    }
	}
    //Finished row. Start new line
    printf("\n");
    }
    //Send permission to next rank (unless last rank)
    if(myid<numprocs-1) {
	MPI_Send(&printPermission, 1, MPI::BOOL, myid+1, 1, MPI_COMM_WORLD);
    }


  //--------------------FRAME-CLEANUP---------------------//
    //Send back rank's first line to previous rank for next frame
    MPI_Sendrecv(mySect[nextActive][0][0], SIZE_OF_SECTIONS, MPI_INT, (myid-1+numprocs)%(numprocs), 0,
		&lastRow, SIZE_OF_SECTIONS, MPI_INT, (myid+1)%numprocs, 0, MPI_COMM_WORLD, &status);
    //Set received line to last line for next frame
	for(int j=0; j<SIZE_OF_SECTIONS; j++) {
	    mySect[nextActive][0][(SIZE_OF_SECTIONS/numprocs)-1][j] = lastRow[j];
	}

    //Prepare for next frame
    active = nextActive;
    sleep(1);
    }
    MPI_Finalize();
    return 0;
}
