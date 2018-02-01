/*
 * DenseMatrix.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: Connor
 */

//#include "DenseMatrix.h"
#include <cstring>
#include <iostream>
using namespace std;

class Dense_Matrix {
	private:
		double* values;
		int N;
	public:
		//Constructors
		Dense_Matrix () : values(new double[1]) {N=1;}
		Dense_Matrix (int _N) : values(new double[_N*_N]) {N=_N;}
		Dense_Matrix (const Dense_Matrix& former) : values(new double[former.N*former.N])
		{
			memcpy(values, former.values, former.N);
			N=former.N;
		}
		//Destructor
		~Dense_Matrix() {
			delete[] values;
		}
		//Accessors
		double& operator()(int i, int j) {
			return *(values+i*N+j);
		}
		double operator()(int i, int j) {
			return values[i*N+j];
		}
		//Copy Operator
		void operator=(const Dense_Matrix& source) {
		    memcpy(values, source.values, sizeof(source.values));
		}

};
//Dense_Matrix::Dense_Matrix() {
//}
//Dense_Matrix::~Dense_Matrix() {
//}

int main() {
    Dense_Matrix Copier(3);
    cout << Copier(1,1);
    cout << endl;
    Copier(1,1)=5;
	cout << Copier(1,1);
	cout << endl;
    Dense_Matrix CopyOf(Copier);
	cout << CopyOf(1,1);
	cout << endl;

    return 0;
}
