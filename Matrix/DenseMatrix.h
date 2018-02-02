/*
 * DenseMatrix.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Connor
 */

#ifndef DENSEMATRIX_H_
#define DENSEMATRIX_H_
#include <cstring>
#include <iostream>

class Dense_Matrix {
	public:
                Dense_Matrix (int _N) : values(new double[_N*_N]), N(_N) {}
                Dense_Matrix (const Dense_Matrix& former) : values(new double(former.N*former.N)), N(former.N) //values(new double(*(former.values)))
		{
			memcpy(values, former.values, N*N*sizeof(double));
		}

		//Destructor
		virtual ~Dense_Matrix() {
			delete[] values;
		}
		//Accessors
		double& operator()(int i, int j) {
			return *(values+i*N+j);
		}
		//Copy Operator
		Dense_Matrix& operator=(const Dense_Matrix& former) {
		  if(N != former.N)
		  {
		     delete[] values;
		     N = former.N;
		     values = new double[N*N];
		  }

		  memcpy(values, former.values, N*N*sizeof(double));
		  return *this;
		}

		//accessors:
	        //int rows() {return M;}
		int cols() {return N;}

	private:
		double* values;
		int N;
};

#endif /* DENSEMATRIX_H_ */
