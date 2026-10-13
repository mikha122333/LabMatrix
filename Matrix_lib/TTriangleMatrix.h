#pragma once
#include "TMathVector.h"
template<typename vec_type>
class TriangleMatrix :public MathVector< MathVector<vec_type>> {
protected:
	size_t _N;
	MathVector pillar_to_mathvector(size_t number_of_pillar)const noexcept;
	MathVector line_to_full_mathvector(size_t number_of_line)const noexcept;
public:
	TriangleMatrix();
	TriangleMatrix(size_t N, vec_type** data);
	TriangleMatrix(std::initializer_list<std::initializer_list<vec_type>>);
	TriangleMatrix(const TriangleMatrix& other);

	inline size_t get_N() { return _N; } const noexcept;

	TriangleMatrix<vec_type>& operator=(const TriangleMatrix<vec_type>& other)noexcept;
	TriangleMatrix<vec_type>& operator=(TriangleMatrix<vec_type>&& other)noexcept;
	TriangleMatrix<vec_type>& operator *=(const TriangleMatrix<vec_type>& other);
	TriangleMatrix<vec_type> operator*(const TriangleMatrix<vec_type>& other)const;

	friend std::ostream& operator<< (std::ostream& out, const Matrix<vec_type> m1) {
		for (int i = 0; i < m1.get_N(); i++) {
			out << "{" << m1[i][0];
			for (int i2 = 1; i2 < m1.get_M(); i2++) {
				try {
					out << ", " << m1[i][i2];
				}
				catch (...) {
					out << ", 0";
				}
			}
			out << "}\n";
		}
		return(out);
	}
};