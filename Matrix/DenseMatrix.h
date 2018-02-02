/*
 * DenseMatrix.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Connor
 */

#ifndef DENSEMATRIX_H_
#define DENSEMATRIX_H_

class Dense_Matrix {
	public:
		Dense_Matrix(int _N);
		Dense_Matrix (const Dense_Matrix& former);
		virtual ~Dense_Matrix();
		double& operator()(int i, int j);
		void operator=(const Dense_Matrix& former);
	private:
		double* values;
		int N;
};

#endif /* DENSEMATRIX_H_ */
