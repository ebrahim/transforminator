#include "Debug.hpp"
#include "Point.hpp"
#include "Transform.hpp"

int main()
{
	Point point;
	Transform transform;

	fprintf(stderr, "initial point:\n");
	print_matrix(point);

	// Translate
	transform.reset();
	transform.matrix[0][3] = +5;		// x += 5
	transform.matrix[1][3] = +3;		// y += 3
	transform.matrix[2][3] = -1;		// z -= 1
	fprintf(stderr, "translate transform:\n");
	print_matrix(transform);

	point.transform(transform);
	fprintf(stderr, "translated point:\n");
	print_matrix(point);

	// Scale
	transform.reset();
	transform.matrix[0][0] = -1;		// x *= -1
	transform.matrix[1][1] = +3;		// y *= +3
	transform.matrix[2][2] = +5;		// z *= +5
	fprintf(stderr, "scale transform:\n");
	print_matrix(transform);

	point.transform(transform);
	fprintf(stderr, "scaled point:\n");
	print_matrix(point);

	// FIXME: Rotate
	transform.reset();
	transform.matrix[0][1] = 2;
	transform.matrix[1][2] = 2;
	transform.matrix[2][0] = 2;
	fprintf(stderr, "rotate transform:\n");
	print_matrix(transform);

	point.transform(transform);
	fprintf(stderr, "rotated point:\n");
	print_matrix(point);

	return 0;
}
