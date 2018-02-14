
#include "DenseMatrixMult.h"

template <typename T>
int Multiply(Dense_Matrix<T> &C, const Dense_Matrix<T> &A, const Dense_Matrix<T> &B)  // C = A * B
{

  //Check for compatibility
  if( (A.cols() != B.rows()) || (C.rows() != A.rows()) || (C.cols() != B.cols()) ) {
    return -1;
  }

  for(int i=0; i<A.getCols(); i++) {
    for(int j=0; j<A.getRows(); j++) {
      T temp = (T) 0.0;
        for(int k=0; k<B.getRows(); k++) {
	//A=Row-Oriented and B=Row-Oriented
	temp += A(i, j) * B(j, k);
      }
	
      C(i,k) = temp;
    }  
  }

    return 1;
}

