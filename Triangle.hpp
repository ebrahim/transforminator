#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "Point.hpp"

class Triangle
{
public:
	Triangle()
	{
	}

	Triangle(const Point& a, const Point& b, const Point& c)
	: a(a)
	, b(b)
	, c(c)
	{
	}

	void transform(const Transform& transform)
	{
		a.transform(transform);
		b.transform(transform);
		c.transform(transform);
	}

	Triangle& operator*=(Number value)
	{
		a *= value;
		b *= value;
		c *= value;
		return *this;
	}

	Triangle& operator/=(Number value)
	{
		a /= value;
		b /= value;
		c /= value;
		return *this;
	}

	Triangle& operator+=(const Triangle& other)
	{
		a += other.a;
		b += other.b;
		c += other.c;
		return *this;
	}

	Point a, b, c;
};

#endif // _TRIANGLE_HPP_
