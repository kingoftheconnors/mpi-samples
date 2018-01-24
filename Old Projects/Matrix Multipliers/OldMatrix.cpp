#include <vector>
using std::vector;

class Matrix {
    public:
	//Default constructor
	Matrix(int n) {
	    arr.resize(n);
	    for(int i=0; i<n; i++) {
		arr[i].resize(n);
	    }
	}
	//Copy constructor
	Matrix(const Matrix& root)
	{
	arr = root.arr;
	}

	//Move constructor
	Matrix(Matrix& root)
	{
	arr = root.arr;
	root.emptyMatrix();
	}

	Matrix& copy(const Matrix& root) {
	    arr = root.arr;
	    return *this;
	}
	Matrix& move(Matrix& root) {
	    if(&root != this) {
		arr = root.arr;
		root.emptyMatrix();
	    }
	    return *this;
	}

	Matrix multiply(Matrix B) {
	    Matrix answer(arr.size());
	    for(int i=0; i<arr.size(); i++) {
		for(int j=0; j<arr.size(); j++) {
		    for(int k=0; k<arr.size(); k++) {
			answer.arr[j][k] += arr[j][i] * B.arr[i][k];
		    }
		}
	    }
	}

	void emptyMatrix() {
	    for(int i=0; i<arr.size();i++) {
		for(int j=0; j<arr[0].size();j++) {
		    arr[i][j]=0;
		}
	    }
	}

	~Matrix() {
	}
    private:
	std::vector< std::vector<int> > arr;
};
