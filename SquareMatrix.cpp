//#include "Matrix.h"
//#include <vector>
#include <math.h>
#include <iostream>
#include "SquareMatrix.h"
#include "Diagonal.h"
#include "AlgorithmRLS.h"

namespace ADP
{

	const SquareMatrix SquareMatrix::inv() const
	{

		const int n = this->size()[0];
		SquareMatrix matOut(n);
		Diagonal I(n,1);
		//Matrix I(I0); 

		for(int i=1;i<=n;++i)
		{
			AlgorithmRLS myRLS(this->t(), I.col(i));
			matOut.col(i,myRLS.disp());
		}

		return matOut;
	}


	SquareMatrix::SquareMatrix(const std::vector<double> & input)
		:Matrix(input, squareGet_dim(input))
	{}

	const std::vector<double> SquareMatrix::diag() const
	{
		std::vector<double> out(this->size()[0]);
		auto it = out.begin();
		for(int i=1;i<=this->size()[0];++i)
		{
			*it = this->operator()(i,i);
			++it;
		}

		return out;

	}
	const int SquareMatrix::squareGet_dim(const std::vector<double> & input) const
	{
		return floor(sqrt(static_cast<double>(input.size())));
	}

	const Matrix SquareMatrix::check_mat(const Matrix& mat) const
	{

		if (mat.size()[0]==mat.size()[1]) return mat;
		else if (mat.size()[0]<mat.size()[1])
		{
			std::cout<<"warning! not square matrix." << std::endl;
			Matrix out(mat.size()[0],mat.size()[0]);
			for (int i=1;i<=mat.size()[0];++i)
				out.row(i,mat.row(i));
			return out; 
		}
		else{
			std::cout<<"warning! not square matrix." << std::endl;
			Matrix out(mat.size()[1],mat.size()[1]);
			for (int i=1;i<=mat.size()[1];++i)
				out.col(i,mat.col(i));
			return out; 
		}
	}
}