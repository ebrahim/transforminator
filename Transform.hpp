#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <cmath>

#include "Matrix.hpp"
#include "Types.hpp"

class Transform : public Matrix<Number, 4, 4>
{
public:
	typedef Matrix<Number, 4, 4> MatrixType;

	enum PredefinedTransforms
	{
		Identity,
		Zero,
		Uninitialized,
	};

	explicit Transform(PredefinedTransforms transform = Uninitialized)
	{
		reset(transform);
	}

	Transform(const MatrixType& matrix)
	{
		*this = matrix;
	}

	static Transform translation(Number x, Number y, Number z)
	{
		Transform result(Identity);
		result.matrix[0][3] = x;
		result.matrix[1][3] = y;
		result.matrix[2][3] = z;
		return result;
	}

	static Transform scaling(Number x, Number y, Number z)
	{
		Transform result(Zero);
		result.matrix[0][0] = x;
		result.matrix[1][1] = y;
		result.matrix[2][2] = z;
		result.matrix[3][3] = 1;
		return result;
	}

	static Transform rotation(Number x, Number y, Number z)
	{
		// Z rotation
		Transform z_rotation(Identity);
		Number z_cosine = cos(z);
		Number z_sine = sin(z);
		z_rotation.matrix[0][0] = z_cosine;
		z_rotation.matrix[0][1] = -z_sine;
		z_rotation.matrix[1][0] = z_sine;
		z_rotation.matrix[1][1] = z_cosine;

		// Y rotation
		Transform y_rotation(Identity);
		Number y_cosine = cos(y);
		Number y_sine = sin(y);
		y_rotation.matrix[2][2] = y_cosine;
		y_rotation.matrix[2][0] = -y_sine;
		y_rotation.matrix[0][2] = y_sine;
		y_rotation.matrix[0][0] = y_cosine;

		// X rotation
		Transform x_rotation(Identity);
		Number x_cosine = cos(x);
		Number x_sine = sin(x);
		x_rotation.matrix[1][1] = x_cosine;
		x_rotation.matrix[1][2] = -x_sine;
		x_rotation.matrix[2][1] = x_sine;
		x_rotation.matrix[2][2] = x_cosine;

		return x_rotation * y_rotation * z_rotation;
	}

	Transform& reset(PredefinedTransforms transform = Identity)
	{
		switch (transform)
		{
			case Identity:
				*static_cast<MatrixType*>(this) = 0;
				for (SizeType i = 0; i < MatrixType::Rows; ++i)
					matrix[i][i] = 1;
				break;
			case Zero:
				*static_cast<MatrixType*>(this) = 0;
				matrix[MatrixType::Cols - 1][MatrixType::Cols - 1] = 1;		// Preserve w
				break;
			case Uninitialized:
			default:
				break;
		}
		return *this;
	}

	Transform& operator=(const MatrixType& matrix)
	{
		*static_cast<MatrixType*>(this) = matrix;
		return *this;
	}
};

#endif // _TRANSFORM_HPP_
