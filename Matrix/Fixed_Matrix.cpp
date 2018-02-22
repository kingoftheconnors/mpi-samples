/*
 * DenseMatrix.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: Connor
 */

#include "Fixed_Matrix.h"

/*
template <typename T, int _N, int _M>
Fixed_Matrix<T, _N, _M>::Fixed_Matrix () : values(new double[N*M], N=_N, M=_M) {}

template <typename T, int _N, int _M>
  Fixed_Matrix<T, _N, _M>::Fixed_Matrix (const Fixed_Matrix<T, _N, _M> &former) : values(new T(former.rows()*former.cols())), N(former.rows()), M(former.cols())
  {
    memcpy(values, former.values, N*M*sizeof(T));
  }

//template <typename S, int _n, int _m>
//template <typename T, int _N, int _M>
//Update for operator equals to transform and check for M to equal N or use only N and M
template <typename S, typename T, int _N, int _M, int _n, int _M>
  Fixed_Matrix<T, _N, _M>::Fixed_Matrix (const Fixed_Matrix<S, _n, _m> &former) : values(new S(former.rows()*former.cols())), N(former.rows()), M(former.cols())
  {
    memcpy(values, former.values, N*M*sizeof(S));
  }

  template <typename T, int _N, int _M>
  //virtual Fixed_Matrix<T, _N, _M>::~Fixed_Matrix() {
  Fixed_Matrix<T, _N, _M>::~Fixed_Matrix() {
    delete[] values;
  }

  template <typename T, int _N, int _M>
  Fixed_Matrix<T, _N, _M>& Fixed_Matrix<T, _N, _M>::operator=(const Fixed_Matrix<T, _N, _M> &former) {
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
  template <typename S, int _n, int _m>
  template <typename T, int _N, int _M>
  Fixed_Matrix<S, _n, _m>& Fixed_Matrix<T, _N, _M>::operator=(const Fixed_Matrix<S, _n, _m> &former) {
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
  template <typename T, int _N, int _M>
  T& Fixed_Matrix<T, _N, _M>::operator()(int i, int j) {
    return *(values+1*N+j);
  }
  template <typename T, int _N, int _M>
  T Fixed_Matrix<T, _N, _M>::operator()(int i, int j) const {
    return *(values+1*N+j);
  }

  template <typename T, int _N, int _M>
  int Fixed_Matrix<T, _N, _M>::rows() const {return N;}
  template <typename T, int _N, int _M>
  int Fixed_Matrix<T, _N, _M>::cols() const {return M;}

  //Printing the Matrix
  template <typename S, int _n, int _m>
  template <typename T, int _N, int _M>
  ostream& Fixed_Matrix<T, _N, _M>::operator<< (ostream& os, const Fixed_Matrix<S, _n, _m> toPrint) {
    //for(int i=0; i<N; i++)
    //{
    //for(int j=0; j<M; j++)
    //{
	//os << values[i*N + j] + " WOORDS ";
	os << "WOORDS";
	cout << "Using the method" << endl;
	//}
      //os << endl;
      //}
    return os;
  }

  template Fixed_Matrix<double, 2, 2>();

*/
