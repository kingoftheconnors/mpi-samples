#include <string.h>
#include <stdio.h>

class Matrix {
    //protected:
    private:
	double *A;
	int M;
	int N;

    public:
	//Constructors and Destructor
	Matrix(int _M, int _N)
	    : M(_M), N(_N), A(new double[M*N])
	{}

	//Copy Constructor
	Matrix(int _M, int _N, const Matrix& source)
	    : M(_M), N(_N), A(new double[M*N])
	{
	    memcpy(A, source.A, sizeof(A));
	}

	~Matrix()
	{
	    delete A;
	}

	//Copy Operator
	Matrix& operator=(const Matrix& source) {
	    memcpy(A, source.A, sizeof(A));
	}

	//Accessors
	double& operator()(int i, int j) {
	    return *(A+(i*N)+j);
	}

	double operator()(int i, int j) const {
	    return *(A+(i*N)+j);
	}

	int numRows() { return M; }
	int numCols() { return N; }

};

    int main()
    {
	Matrix exA(2,2);
	exA(0,0)=4;
	printf("%f\n", exA(0,0));
    }

