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
              Dense_Matrix (int _N, int _M) : values(new double[_N*_M]), N(_N), M(_M) {}
              Dense_Matrix (const Dense_Matrix& former) : values(new double(former.N*former.M)), N(former.N), M(former.M) //values(new double(*(former.values)))
		{
			memcpy(values, former.values, N*M*sizeof(double));
		}

		//Destructor
		virtual ~Dense_Matrix() {
			delete[] values;
		}
		//Accessors
		double& operator()(int i, int j) {
			return *(values+i*N+j);
		}
		double operator()(int i, int j) const {
			return *(values+i*N+j);
		}
		//Copy Operator
		Dense_Matrix& operator=(const Dense_Matrix& former) {
		  if(N != former.N || M != former.M)
		  {
		     delete[] values;
		     N = former.N;
		     M = former.M;
		     values = new double[N*N];
		  }

		  memcpy(values, former.values, N*M*sizeof(double));
		  return *this;
		}

		//accessors:
	        int getRows() {return M;}
		int getCols() {return N;}

	private:
		double* values;
		int N;
		int M;
};

#endif /* DENSEMATRIX_H_ */
