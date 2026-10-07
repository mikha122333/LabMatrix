#pragma once
#include"TMathVector.h"
template<typename vec_type>
class Matrix :public MathVector<MathVector<vec_type>> {
	size_t _N;//lines
	size_t _M;//pillars
	Matrix<vec_type> Transposition()const noexcept;
public:
	Matrix() :MathVector<MathVector<vec_type>>() { _N = 0; _M = 0; }
	Matrix(size_t N, size_t M,vec_type** data=nullptr);
	//Matrix(std::initializer_list<std::initializer_list<vec_type>> data) :MathVector<MathVector<vec_type>>(data) { _N = data.size(); _M = data.begin()->size(); }
	Matrix(std::initializer_list<std::initializer_list<vec_type>> data);
	Matrix(const Matrix& other) :MathVector<MathVector<vec_type>>(other) { _N = other._N; _M = other._M; }

	~Matrix() = default;

	//inline size_t size()const noexcept = delete;
	inline size_t get_N() const noexcept{ return _N; }
	inline size_t get_M() const noexcept{ return _M; }

	Matrix<vec_type>& operator=(const Matrix<vec_type>& other) { MathVector<MathVector<vec_type>>::operator =(other); _N = other._N; _M = other._M; return(*this); }
	Matrix<vec_type>& operator=(Matrix<vec_type>&& other) { MathVector<MathVector<vec_type>>::operator =(std::move(other)); _N = other._N; _M = other._M; other._M = 0; other._N = 0; return(*this); }
	Matrix<vec_type>& operator*=(const Matrix<vec_type>& other);
	Matrix<vec_type> operator *(const Matrix<vec_type>& other)const { Matrix tmp((*this)); return(tmp *= other); }

	friend std::ostream& operator<< (std::ostream& out, const Matrix<vec_type> m1) {
		for (int i = 0; i < m1.get_N(); i++) {
			out << "{" << m1[i][0];
			for (int i2 = 1; i2 < m1.get_M(); i2++) {
				out << ", " << m1[i][i2];
			}
			out << "}\n";
		}
		return(out);
	}
};
template<typename vec_type>
Matrix<vec_type>::Matrix(std::initializer_list<std::initializer_list<vec_type>> data):MathVector<MathVector<vec_type>>(data.size()) {
	_N = data.size();
	if (_N <= 0)
		throw std::logic_error("0 list N");
	_M = data.begin()->size();
	if (_M <= 0)
		throw std::logic_error("o list M");
	auto it = data.begin();
	for (int i = 0; i < _N;i++) {
		MathVector<vec_type> tmp(*	(it+i));
		(*this)[i] = std::move(tmp);
	}
}
template<typename vec_type>
Matrix<vec_type>::Matrix(size_t N, size_t M, vec_type** data):MathVector<MathVector<vec_type>>(N) {
	if (N == 0 || M == 0)
		throw std::logic_error("trying to create Matrix with N=0 or M=0");
	_N = N;
	_M = M;
	for (int i = 0; i < _N; i++) {
		//delete[]((*this)[i]);
		(*this)[i] = MathVector<vec_type>(M);
		for (int i2 = 0; i2 < _M&&(data!=nullptr); i2++) {
			(*this)[i][i2] = data[i][i2];
		}
	}
}
template<typename vec_type>
Matrix<vec_type> Matrix<vec_type>::Transposition()const noexcept {
	vec_type** tmp = new vec_type*[_M];
	for (int i = 0; i < _M; i++) {
		tmp[i] = new vec_type[_N];
		for (int i2 = 0; i2 < _N; i2++) {
			tmp[i][i2] = (*this)[i2][i];
		}
	}
	Matrix<vec_type> res(_M, _N, tmp);
	for (int i = 0; i < _M; i++) {
		delete[](tmp[i]);
	}
	delete[]tmp;
	return res;
}
template<typename vec_type>
Matrix<vec_type>& Matrix<vec_type>::operator*=(const Matrix<vec_type>& other) {
	if (this->_M != other._N)
		throw std::logic_error("trying to *= matrix with different M and N");
	vec_type** tmp = new vec_type * [_N];
	Matrix tmp_mat(other.Transposition());
	for (int i = 0; i < _N; i++) {
		tmp[i] = new vec_type[other._M];
		for (int i2 = 0; i2 < other._M; i2++) {
			tmp[i][i2] = (*this)[i] * tmp_mat[i2];
		}
	}
	(*this) = std::move(Matrix(_N, other._M, tmp));
	return(*this);
}