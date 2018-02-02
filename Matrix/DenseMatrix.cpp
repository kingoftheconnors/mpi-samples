/*
 * DenseMatrix.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: Connor
 */

#include "DenseMatrix.h"
#include <cstring>
#include <iostream>
using namespace std;

		//Constructors
		Dense_Matrix::Dense_Matrix (int _N) : values(new double[_N*_N]) {N=_N;}
		Dense_Matrix::Dense_Matrix (const Dense_Matrix& former) : values(new double(former.N*former.N)) //values(new double(*(former.values)))
		{
			N=former.N;
			memcpy(values, former.values, N*N*sizeof(double*));
		}
		//Destructor
		Dense_Matrix::~Dense_Matrix() {
			delete[] values;
		}
		//Accessors
		double& Dense_Matrix::operator()(int i, int j) {
			return *(values+i*N+j);
		}
		//Copy Operator
		void Dense_Matrix::operator=(const Dense_Matrix& former) {
			memcpy(values, former.values, N*N*sizeof(double*));
		}

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
