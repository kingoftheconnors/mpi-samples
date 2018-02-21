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

template <typename T>
class Dense_Matrix {
	public:
              Dense_Matrix (int _N, int _M) : values(new T[_N*_M]), N(_N), M(_M) {}
              Dense_Matrix (const Dense_Matrix<T>& former) : values(new T(former.rows()*former.cols())), N(former.rows()), M(former.cols()) //values(new double(*(former.values)))
		{
			memcpy(values, former.values, N*M*sizeof(T));
		}

               //Copy constructor for if the templates are different types
               template <typename S>
                Dense_Matrix (const Dense_Matrix<S>& former) : values(new S(former.rows()*former.cols())), N(former.rows()), M(former.cols()) //values(new double(*(former.values)))
		{
			memcpy(values, former.values, N*M*sizeof(S));
		}

                //Destructor
		virtual ~Dense_Matrix() {
			delete[] values;
		}
		
		//Copy Operator
		Dense_Matrix& operator=(const Dense_Matrix<T>& former) {
		  if(N != former.rows() || M != former.cols())
		  {
		     delete[] values;
		     N = former.rows();
		     M = former.cols();
		     values = new T[N*M];
		  }

		  memcpy(values, former.values, N*M*sizeof(T));
		  return *this;
		}

		//Cross-Type Copy Operator
	       template <typename S>
		Dense_Matrix& operator=(const Dense_Matrix<S>& former) {
		  if(N != former.rows() || M != former.cols())
		  {
		     delete[] values;
		     N = former.rows();
		     M = former.cols();
		     values = new S[N*M];
		  }

		  memcpy(values, former.values, N*M*sizeof(S));
		  return *this;
		}

		//Accessors
		T& operator()(int i, int j) {
			return *(values+i*N+j);
		}
		T operator()(int i, int j) const {
			return *(values+i*N+j);
		}

	        int rows() const {return N;}
		int cols() const {return M;}

	private:
		T* values;
		int N, M;
};

#endif /* DENSEMATRIX_H_ */
