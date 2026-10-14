#pragma once
#include "TTriangleMatrix.h"
#include "TMatrix.h"
class app_double {
public:
	app_double() {};
	void start();
	TriangleMatrix<double> get_tri_mat(size_t N=0)const noexcept;
	Matrix<double> get_mat(size_t N=0, size_t M=0)const noexcept;

};