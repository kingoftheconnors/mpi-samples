
#include "DenseMatrixMult.h"

using namespace std;

template <typename T>
void output_Dense_Matrix(const Dense_Matrix<T> &A)
{
  for(int i=0; i<A.rows(); ++i)
  {
    for(int j=0; j<A.cols(); ++j)
    {
      cout << A(i,j) << " ";
    }
    cout << endl;
  }
}

int main() {
  Dense_Matrix<double> First(2,2);
  Dense_Matrix<double> Second(2,2);
  Dense_Matrix<double> Third(2,2);
  First(0,0)=1; First(0,1)=0;
  First(1,0)=0; First(1,1)=1;
  
  Second(0,0)=1; Second(0,1)=1;
  Second(1,0)=0; Second(1,1)=2;

  cout << "Before " << endl << endl;
  cout << "Third:"<<endl;
  output_Dense_Matrix(Third);
  cout << "Second:"<<endl;
  output_Dense_Matrix(Second);
  cout << "First:"<<endl;
  output_Dense_Matrix(First);

  int multOut = Multiply(Third, Second, First);

  cout << "Result from DenseMatrixMult: " << multOut << endl;

  cout << "After " << endl << endl;
  cout << "Third:"<<endl;
  output_Dense_Matrix(Third);
  cout << "Second:"<<endl;
  output_Dense_Matrix(Second);
  cout << "First:"<<endl;
  output_Dense_Matrix(First);

  return 0;
}
