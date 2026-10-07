#pragma once
#include "Vector.h"
template<typename vec_type>
class MathVector :protected Vector<vec_type> {
	size_t _start_index;
public:
	MathVector(size_t size = 0, const vec_type* data = nullptr, size_t index = 0) :Vector<vec_type>(size, data) { this->shrink_to_fit(); _start_index = index; }
	MathVector(std::initializer_list<vec_type> data, size_t index = 0) :Vector<vec_type>(data) { this->shrink_to_fit(); _start_index = index; }
	MathVector(const MathVector<vec_type>& other, size_t index = 0) : Vector<vec_type>(other) {_start_index = other._start_index; this->shrink_to_fit();}

	MathVector<vec_type>& operator =(const MathVector<vec_type>& other)noexcept;
	MathVector<vec_type>& operator =(MathVector<vec_type>&& other)noexcept;
	MathVector<vec_type>& operator +=(const MathVector<vec_type>& other);
	MathVector<vec_type>& operator -=(const MathVector<vec_type>& other);
	MathVector<vec_type>& operator *=(double val);
	MathVector<vec_type> operator +(const MathVector<vec_type>& other)const;
	MathVector<vec_type> operator -(const MathVector<vec_type>& other)const;
	vec_type operator *(const MathVector<vec_type>& other)const;
	MathVector<vec_type> operator *(double val)const;
	vec_type operator[](size_t num)const noexcept { return Vector<vec_type>::operator[](num); }
	vec_type& operator[](size_t num)noexcept { return Vector<vec_type>::operator[](num); }


	size_t size()const noexcept { return Vector<vec_type>::size(); }
	size_t index()const noexcept { return _start_index; }

	virtual ~MathVector() = default;

	friend std::ostream& operator<< (std::ostream& out, const MathVector<vec_type>& m1) {
		out << "{";
		if (m1.size() != 0) {
			out << m1[0];
		}
		for (int i = 1; i < m1.size(); i++) {
			out << ", " << m1[i];
		}
		out << "}";
		return(out);
	}
	friend std::istream& operator>>(std::istream& in, MathVector<vec_type>& m1) {
		Vector<vec_type> tmp;
		vec_type ch;
		in >> ch;
		while (in >> ch) {
			tmp.push_back(ch);
		}
		vec_type* arr = new vec_type[tmp.size()];
		for (int i = 0; i < tmp.size(); i++) {
			arr[i] = tmp[i];
		}
		MathVector<vec_type> m2(tmp.size(), arr);
		m1 = m2;
		return in;
	}

};
template<typename vec_type>
MathVector<vec_type>& MathVector<vec_type>:: operator =(const MathVector<vec_type>& other)noexcept {
	if(this!=&other){
		Vector<vec_type>::operator=(other);
		_start_index = other._start_index;
	}
	return (*this);
}
template<typename vec_type>
MathVector<vec_type>& MathVector<vec_type>:: operator =(MathVector<vec_type>&& other)noexcept {
	if (this != &other) {
		Vector<vec_type>::operator=(std::move(other));
		_start_index = other._start_index;
		other._start_index = 0;
	}
	return (*this);
}
template<typename vec_type>
MathVector<vec_type>& MathVector<vec_type>::operator +=(const MathVector<vec_type>& other) {
	if (this->size() == other.size()) {
		for (int i = 0; i < this->size(); i++) {
			this->operator[](i) += other.operator[](i);
		}
		return (*this);
	}
	else {
		throw std::logic_error("different sizes trying +=");
	}
}
template<typename vec_type>
MathVector<vec_type>& MathVector<vec_type>::operator -=(const MathVector<vec_type>& other) {
	if (this->size() == other.size()) {
		for (int i = 0; i < this->size(); i++) {
			this->operator[](i) -= other.operator[](i);
		}
		return (*this);
	}
	else {
		throw std::logic_error("different sizes trying -=");
	}
}
template<typename vec_type>
MathVector<vec_type>& MathVector<vec_type>::operator *=(double val) {
	for (int i = 0; i < this->size(); i++) {
		this->operator[](i) *= val;
	}
	return (*this);
}
template<typename vec_type>
MathVector<vec_type> MathVector<vec_type>::operator +(const MathVector<vec_type>& other)const {
	MathVector res(*this);
	res += other;
	return res;
}
template<typename vec_type>
MathVector<vec_type> MathVector<vec_type>::operator -(const MathVector<vec_type>& other)const {
	MathVector res(*this);
	res -= other;
	return res;
}
template<typename vec_type>
vec_type MathVector<vec_type>::operator *(const MathVector<vec_type>& other)const {
	if (this->size() == other.size()) {
		vec_type res{};
		for (int i = 0; i < this->size(); i++) {
			res =res+ this->operator[](i) * other.operator[](i);
		}
		return (res);
	}
	else {
		throw std::logic_error("different sizes trying *");
	}
}
template<typename vec_type>
MathVector<vec_type> MathVector<vec_type>::operator *(double val)const {
	MathVector res(*this);
	res *= val;
	return res;
}