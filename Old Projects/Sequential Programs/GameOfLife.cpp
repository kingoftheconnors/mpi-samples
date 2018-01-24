#include <stdio.h>
#include <unistd.h>

int main() {
    int const SIZE_OF_SECTIONS = 15;

    int Sect[SIZE_OF_SECTIONS][SIZE_OF_SECTIONS][2] = {0};
    int active = 0;
    int nextActive = 1;
    int numAdj = 0;

    //Initial setup
    for(int act=0; act<=1; act++) {
	Sect[5][5][act]=1;
	Sect[5][8][act]=1;
	Sect[7][5][act]=1;
	Sect[8][6][act]=1;
	Sect[8][7][act]=1;
	Sect[8][8][act]=1;
	Sect[8][9][act]=1;
	Sect[7][9][act]=1;
	Sect[6][9][act]=1;
    }

    while(1==1) {
    nextActive = (active+1)%2;
    //Go through the entire table
    for(int i=0; i<SIZE_OF_SECTIONS; i++) {
	for(int j=0; j<SIZE_OF_SECTIONS; j++) {
	    numAdj = 0;

	    //Check number of neighbors, including ones from other side
	    for(int a=i-1; a<=i+1; a++) {
		for(int b=j-1; b<=j+1; b++) {
		    //If point is not current point and is active
		    if(a!=i || b!=j)
		        if(Sect[(a+SIZE_OF_SECTIONS)%SIZE_OF_SECTIONS][(b+SIZE_OF_SECTIONS)%SIZE_OF_SECTIONS][active]==1) {
			    //Increase number of recorded adjacent points
			    numAdj++;
			}
		}
	    }
	    //Set d in other array to keep arrays parallel
	    if(Sect[i][j][nextActive]!=Sect[i][j][active]) {
		Sect[i][j][nextActive]=Sect[i][j][active];
	    }
	    //If this point is alive, print and check for overpopulation
	    if(Sect[i][j][active]==1) {
		printf("%d", numAdj);
		//Underpopulation
		if(numAdj<2) {
		    Sect[i][j][nextActive]=0;
		}
		//Overpopulation
		if(numAdj>3) {
		    Sect[i][j][nextActive]=0;
		}
	    }
	    else {
		//If this point is dead, print a blank and check for activity
		printf(" ");
		//Bring alive if exactly 3
		if(numAdj==3) {
		    Sect[i][j][nextActive]=1;
		}
	    }
	}
    //Finished first for loop. Start new line
    printf("\n");
    }
    //Prepare for next frame
    printf("\n\n\n");
    active = nextActive;
    //Wait before making next frame
    sleep(1);
    }
}
