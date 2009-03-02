#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <vector>

#include "Triangle.hpp"

class Mesh
{
public:
	typedef std::vector<Triangle> TriangleSet;

	void transform(const Transform& transform)
	{
		for (TriangleSet::iterator it = triangles.begin(); it != triangles.end(); ++it)
			it->transform(transform);
	}

	void clear()
	{
		triangles.clear();
	}

	void add_triangle(const Triangle& triangle)
	{
		triangles.push_back(triangle);
	}

	Mesh operator*(Number value) const
	{
		Mesh result;
		result.triangles = triangles;
		for (TriangleSet::iterator it = result.triangles.begin(); it != result.triangles.end(); ++it)
			*it *= value;
		return result;
	}

	Mesh operator/(Number value) const
	{
		Mesh result;
		result.triangles = triangles;
		for (TriangleSet::iterator it = result.triangles.begin(); it != result.triangles.end(); ++it)
			*it /= value;
		return result;
	}

	Mesh operator+(const Mesh& other) const
	{
		Mesh result;
		result.triangles = triangles;

		TriangleSet::const_iterator it2 = other.triangles.begin();
		for (TriangleSet::iterator it1 = result.triangles.begin();
		     it1 != result.triangles.end() && it2 != other.triangles.end();
		     ++it1, ++it2)
			*it1 += *it2;
		return result;
	}

	TriangleSet triangles;
};

#endif // _MESH_HPP_
