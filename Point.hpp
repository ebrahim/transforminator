#ifndef _POINT_HPP_
#define _POINT_HPP_

#include "Matrix.hpp"
#include "Transform.hpp"
#include "Types.hpp"

// A point and its normal vector
class Point : public Matrix<Number, 4, 2>
{
public:
	typedef Matrix<Number, 4, 2> MatrixType;

	Point(Number x = 0, Number y = 0, Number z = 0,
	      Number nx = 0, Number ny = 0, Number nz = 0,
		  Number w = 1, Number nw = 0)
	{
		matrix[0][0] = x;
		matrix[1][0] = y;
		matrix[2][0] = z;
		matrix[3][0] = w;
		matrix[0][1] = nx;
		matrix[1][1] = ny;
		matrix[2][1] = nz;
		matrix[3][1] = nw;
	}

	void transform(const Transform& transform)
	{
		*this = transform * *static_cast<MatrixType*>(this);
	}

	Point& operator=(const MatrixType& matrix)
	{
		*static_cast<MatrixType*>(this) = matrix;
		return *this;
	}

	Number& x()
	{
		return matrix[0][0];
	}

	Number& y()
	{
		return matrix[1][0];
	}

	Number& z()
	{
		return matrix[2][0];
	}

	Number& w()
	{
		return matrix[3][0];
	}

	Number& nx()
	{
		return matrix[0][1];
	}

	Number& ny()
	{
		return matrix[1][1];
	}

	Number& nz()
	{
		return matrix[2][1];
	}

	Number& nw()
	{
		return matrix[3][1];
	}
};

#endif // _POINT_HPP_
