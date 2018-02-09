
//#include "DenseMatrixMult.h"
//#include <iostream>
//using namespace std;
/*
class DenseMatrixMult {

public:
  
static void Multiply(Dense_Matrix &C, const Dense_Matrix &A, const Dense_Matrix &B)  // C = A * B
{
  
  if(A.rows() == B.cols()) {
    for(int i=0; i<A.getCols(); i++) {
      for(int j=0; j<A.getRows(); j++) {
        for(int k=0; k<B.getRows(); k++) {
	  //A=Row-Oriented and B=Row-Oriented
	  C(i, k) += A(i, j) * B(j, k);
	} 
      }  
    }
  }
}

};
*/

/*int main() {
  Dense_Matrix AA(2,3);
  Dense_Matrix BB(2,3);
  Dense_Matrix CC(2,2);

  DenseMatrixMult::Multiply(CC, BB, AA);
  cout << "Working";
  cout << CC(1,1);

  return 0;
}*/
