#pragma once
#include "Vector.h"
template<typename vec_type>
class MathVector :protected Vector<vec_type> {
	size_t _start_index;
public:
	MathVector(size_t s,const vec_type* data);
	MathVector(std::initializer_list<vec_type> data);
	MathVector(const MathVector&);

	MathVector<vec_type>& operator =(const MathVector<vec_type>& other)noexcept;
	MathVector<vec_type>& operator =(MathVector<vec_type>&& other)noexcept;
	MathVector<vec_type>& operator +=(const MathVector<vec_type>&);
	MathVector<vec_type>& operator -=(const MathVector<vec_type>&);
	MathVector<vec_type>& operator *=(const MathVector<vec_type>&);
	MathVector<vec_type>& operator *=(double val)noexcept;
	MathVector<vec_type> operator +(const MathVector<vec_type>&)const;
	MathVector<vec_type> operator -(const MathVector<vec_type>&)const;
	MathVector<vec_type> operator *(const MathVector<vec_type>&)const;
	MathVector<vec_type> operator *(double val)const noexcept;

	~MathVector();

	friend std::ostream& operator<< (std::ostream& out, const MathVector<vec_type>& v1);
	friend std::istream& operator>> (std::istream& in, MathVector<vec_type>& v1);
};