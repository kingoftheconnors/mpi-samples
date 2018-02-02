/*
 * DenseMatrix.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: Connor
 */

#include "DenseMatrix.h"

using namespace std;

		//Constructors


//Dense_Matrix::Dense_Matrix() {
//}
//Dense_Matrix::~Dense_Matrix() {
//}

int main() {
    Dense_Matrix Copier(2);
    Copier(0,1)=5;
	cout << Copier(0,1);
	cout << endl;
    Dense_Matrix CopyOf(Copier);
	cout << Copier(0,1);
	cout << endl;
	Dense_Matrix ThirdCopy(2);
	ThirdCopy=Copier;
	cout << Copier(0,1);
	cout << endl;

    return 0;
}
