#ifndef DENSEMATRIXMULT_H
#define DENSEMATRIXMULT_H

#include "DenseMatrix.h"

//class DenseMatrixMult{

  template<typename T>
  int Multiply(Dense_Matrix<T> &C, const Dense_Matrix<T> &A, const Dense_Matrix<T> &B);
  /*{
   for(int i=0; i<A.cols(); i++) {
      for(int j=0; j<A.rows(); j++) {
        for(int k=0; k<B.rows(); k++) {
	  C(i, k) += A(i, j) * B(j, k);
        }
      }
    }
  }
};*/

//#include "DenseMatrixMult.cpp"

#endif
