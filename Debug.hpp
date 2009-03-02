#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#include <cstdio>

#include "Matrix.hpp"

template <typename ElementType, SizeType Rows, SizeType Cols>
static void print_matrix(const Matrix<ElementType, Rows, Cols>& matrix, FILE* f = stderr)
{
	for (SizeType i = 0; i < Rows; ++i)
	{
		for (SizeType j = 0; j < Cols; ++j)
			fprintf(f, "%.2f\t", matrix.matrix[i][j]);
		putc('\n', f);
	}
}

#endif // _DEBUG_HPP_
