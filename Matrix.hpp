#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "Types.hpp"

template <typename ElementType_, SizeType Rows_, SizeType Cols_>
class Matrix
{
public:
	typedef ElementType_ ElementType;
	enum { Rows = Rows_ };
	enum { Cols = Cols_ };
	typedef Matrix<ElementType, Rows, Cols> SelfType;

	SelfType& operator=(const SelfType& other)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] = other.matrix[i][j];
		return *this;
	}

	SelfType& operator+=(const SelfType& other)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] += other.matrix[i][j];
		return *this;
	}

	SelfType& operator-=(const SelfType& other)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] -= other.matrix[i][j];
		return *this;
	}

	bool operator==(const SelfType& other) const
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				if (matrix[i][j] != other.matrix[i][j])
					return false;
		return true;
	}

	bool operator!=(const SelfType& other) const
	{
		return !(*this == other);
	}

	template <SizeType OtherCols>
	Matrix<ElementType, Rows, OtherCols> operator*(const Matrix<ElementType, Cols, OtherCols>& other) const
	{
		Matrix<ElementType, Rows, OtherCols> result;
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < OtherCols; ++j)
			{
				ElementType value = 0;
				for (SizeType k = 0; k < Cols; ++k)
					value += matrix[i][k] * other.matrix[k][j];
				result.matrix[i][j] = value;
			}
		return result;
	}

	SelfType& operator=(ElementType value)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] = value;
		return *this;
	}

	SelfType& operator+=(ElementType value)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] += value;
		return *this;
	}

	SelfType& operator-=(ElementType value)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] -= value;
		return *this;
	}

	SelfType& operator*=(ElementType value)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] *= value;
		return *this;
	}

	SelfType& operator/=(ElementType value)
	{
		for (SizeType i = 0; i < Rows; ++i)
			for (SizeType j = 0; j < Cols; ++j)
				matrix[i][j] /= value;
		return *this;
	}

	ElementType matrix[Rows][Cols];
};

#endif	// _MATRIX_HPP_
