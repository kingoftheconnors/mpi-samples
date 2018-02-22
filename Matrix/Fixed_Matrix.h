/*
 * Fixed_Matrix.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Connor
 */

#ifndef FIXEDMATRIX_H_
#define FIXEDMATRIX_H_
#include <cstring>
#include <iostream>

using namespace std;

template <typename T, int _M, int _N>
class Fixed_Matrix {
private:
  friend ostream& operator<<(ostream &os, const Fixed_Matrix<T, _M, _N> toPrint)
  {
    os << "WORDS";
    cout << "Printing!" << endl;
    return os;
  }
  T* values;
  int N, M;
  
public:
  Fixed_Matrix () : values(new double[N*M], M=_M, N=_N) {}
  Fixed_Matrix (const Fixed_Matrix<T, _M, _N>& former) : values(new T(former.rows()*former.cols())), M(former.rows()), N(former.cols())
  {
    for(int i=0; i<M; i++)
    {
      for(int j=0; j<N; j++)
      {
	values(i, j) = former.values(i, j);
      }
    }
  }

 //Copy constructor for if the templates are different types
 //Fixed_Matrix (const Fixed_Matrix<S, _M, _N>& former) : values(new S(former.rows()*former.cols()))

           //Destructor
~Fixed_Matrix() {
  delete[] values;
}

//Copy Operator
Fixed_Matrix& operator=(const Fixed_Matrix<T, _M, _N>& former)
{
  if(M != former.rows() || N != former.cols())
  {
    delete[] values;
    M = former.rows();
    N = former.cols();
    values = new T[N*M];
  }

  memcpy(values, former.values, N*M*sizeof(T));
  return *this;
}

//Cross-Type Copy Operator
template <typename S, int _m, int _n>
Fixed_Matrix& operator=(const Fixed_Matrix<S, _m, _n>& former)
{
  if(_m == _M && _n && _N)
  {
    for(int i=0; i<M; i++)
    {
      for(int j=0; j<N; j++)
      {
        values(i, j) = former.values(i, j);
      }
    }
  }

  return *this;
}

	   //Accessors
	   T& operator()(int i, int j)
	   {
	     return *(values+i*N+j);
	   }
	   T operator()(int i, int j) const
	   {
	     return *(values+i*N+j);
	   }

int rows() const {return M;}
int cols() const {return N;}

};

#endif /* DENSEMATRIX_H_ */
