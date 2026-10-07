#pragma once
#include"TMathVector.h"
template<typename vec_type>
class Matrix :public MathVector<MathVector<vec_type>> {
	size_t _N;//lines
	size_t _M;//pillars
	Matrix Transposition()const noexcept;
public:
	Matrix();
	Matrix(size_t N, size_t M);
	Matrix(std::initializer_list<std::initializer_list<vec_type>>);
	Matrix(const Matrix& other);

	~Matrix() = default;

	inline size_t get_N() const noexcept{ return _N; }
	inline size_t get_M() const noexcept{ return _M; }

	Matrix& operator*=(const Matrix& other) {}//change to working variant
	Matrix operator *(const Matrix& other)const {}//change to working variant
};