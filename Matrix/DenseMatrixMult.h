#ifndef DENSEMATRIXMULT_H
#define DENSEMATRIXMULT_H

#include "DenseMatrix.h"

class DenseMatrixMult{

 public:
  static void Multiply(Dense_Matrix &C, Dense_Matrix &A, Dense_Matrix &B) {  // C = A * B
    for(int i=0; i<A.getCols(); i++) {
      for(int j=0; j<A.getRows(); j++) {
        for(int k=0; k<B.getRows(); k++) {
	  C(i, k) += A(i, j) * B(j, k);
        }
      }
    }
  }
};

#endif
