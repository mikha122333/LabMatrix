#pragma once
#include "TMathVector.h"
template<typename vec_type>
class TriangleMatrix :public MathVector< MathVector<vec_type>> {
protected:
	size_t _N;
	MathVector<vec_type> pillar_to_mathvector(size_t number_of_pillar, size_t start_in, size_t end_in)const;
	MathVector<vec_type> line_to_full_mathvector(size_t number_of_line,size_t start_in,size_t end_in)const;
public:
	TriangleMatrix() :MathVector<MathVector<vec_type>>() { _N = 0; };
	TriangleMatrix(size_t N, vec_type** data=nullptr);
	TriangleMatrix(std::initializer_list<std::initializer_list<vec_type>> data);
	TriangleMatrix(const TriangleMatrix& other) :MathVector<MathVector<vec_type>>(other) { _N = other._N; };

	TriangleMatrix(const MathVector<MathVector<vec_type>>& other);

	inline size_t get_N() const noexcept { return _N; };

	TriangleMatrix<vec_type>& operator=(const TriangleMatrix<vec_type>& other)noexcept { MathVector<MathVector<vec_type>>::operator=(other); _N = other._N; return(*this); }
	TriangleMatrix<vec_type>& operator=(TriangleMatrix<vec_type>&& other)noexcept { MathVector<MathVector<vec_type>>::operator=(std::move(other)); _N = other._N; other._N = 0; return(*this); }
	TriangleMatrix<vec_type>& operator *=(const TriangleMatrix<vec_type>& other);
	TriangleMatrix<vec_type> operator*(const TriangleMatrix<vec_type>& other)const;

	friend std::ostream& operator<< (std::ostream& out, const TriangleMatrix<vec_type> m1) {
		for (int i = 0; i < m1.get_N(); i++) {
			out << "{" << m1[i][0];
			for (int i2 = 1; i2 < m1.get_N(); i2++) {
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
template<typename vec_type>
TriangleMatrix<vec_type>::TriangleMatrix(const MathVector<MathVector<vec_type>>& other) :MathVector<MathVector<vec_type>>(other) {
	if (other.size() <= 0 || other[0].size() <= 0)
		throw std::logic_error("wrong math vec");
	int tmp = other[0].size();
	for (int i = 0; i < other.size(); i++) {
		if (other[i].size() != (tmp+i)) {
			throw std::logic_error("wrong math vec");
		}
	}
	_N = other.size();
}
template<typename vec_type>
MathVector<vec_type> TriangleMatrix<vec_type>::pillar_to_mathvector(size_t number_of_pillar, size_t start_in, size_t end_in)const{
	if (number_of_pillar >= _N || (end_in - start_in + 1) > _N || (end_in - start_in + 1) <= 0 || end_in >= _N)
		throw std::out_of_range("num_of_pil is out of range");
	MathVector<vec_type> res(end_in-start_in+1);
	for (int i = 0; i < end_in-start_in+1; i++) {
		try {
			res[i] = (*this)[i+start_in][number_of_pillar];
		}
		catch (...) {
			res[i]= vec_type{};
		}
	}
	return res;
}
template<typename vec_type>
MathVector<vec_type> TriangleMatrix<vec_type>::line_to_full_mathvector(size_t number_of_line, size_t start_in, size_t end_in)const {
	if (number_of_line >= _N || (end_in-start_in+1)>_N || (end_in - start_in + 1)<=0||end_in>=_N)
		throw std::out_of_range("num_of_pil is out of range");
	MathVector<vec_type> res(end_in-start_in+1);
	for (int i = 0; i < end_in-start_in+1; i++) {
		try {
			res[i] = (*this)[number_of_line][i+start_in];
		}
		catch (...) {
			res[i] = vec_type{};
		}
	}
	return res;
}
template<typename vec_type>
TriangleMatrix<vec_type>::TriangleMatrix(size_t N, vec_type** data):MathVector<MathVector<vec_type>>(N) {
	if (N <= 0)
		throw std::logic_error("inapropriate trianglematrix");
	_N = N;
	for (int i = 0; i < N; i++) {
		(*this)[i] = MathVector<vec_type>(i + 1);
		for (int i2 = 0; i2 < i + 1&&(data!=nullptr); i2++) {
			(*this)[i][i2] = data[i][i2];
		}
	}
}
template<typename vec_type>
TriangleMatrix<vec_type>::TriangleMatrix(std::initializer_list<std::initializer_list<vec_type>> data) :MathVector<MathVector<vec_type>>(data.size()) {
	if (data.size() <= 0||(data.begin()->size()!=1 ))
		throw std::logic_error("wrong init list");
	_N = data.size();
	auto it = data.begin();
	for (int i = 0; i < _N; i++) {
		MathVector<vec_type> tmp(*(it + i));
		(*this)[i] = std::move(tmp);
	}
}
template<typename vec_type>
TriangleMatrix<vec_type>& TriangleMatrix<vec_type>::operator *=(const TriangleMatrix<vec_type>& other) {
	if (_N != other._N)
		throw std::logic_error("trying *= trimat with diff size");
	TriangleMatrix<vec_type> res(_N);
	size_t start_in, end_in;
	for (int i = 0; i < _N; i++) {
		vec_type* tmp_data=new vec_type[i + 1];
		for (int i2 = 0; i2 <= i; i2++) {
			tmp_data[i2] = (this->line_to_full_mathvector(i, i2, i)) * other.pillar_to_mathvector(i2,i2,i);
		}
		res[i] = std::move(MathVector<vec_type>(i + 1, tmp_data));
		delete[] tmp_data;
	}
	(*this) = std::move(res);
	return (*this);
}
template<typename vec_type>
TriangleMatrix<vec_type> TriangleMatrix<vec_type>::operator *(const TriangleMatrix<vec_type>& other)const {
	TriangleMatrix<vec_type> res((*this));
	res *= other;
	return res;
}