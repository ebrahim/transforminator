#ifndef _TRANSFORMEDMESH_HPP_
#define _TRANSFORMEDMESH_HPP_

#include "Mesh.hpp"

#include <string>
#include <algorithm>

class TransformedMesh
{
public:
	TransformedMesh()
	: transform(Transform::Identity)
	{
	}

	void set_mesh(const Mesh& new_mesh)
	{
		original_mesh = new_mesh;
		transformed_mesh = original_mesh;
		transformed_mesh.transform(transform);
	}

	void reset()
	{
		transformed_mesh = original_mesh;
		transform.reset();
	}

	void set_transform(const Transform& new_transform)
	{
		transform = new_transform;
		transformed_mesh = original_mesh;
		transformed_mesh.transform(new_transform);
	}

	void add_transform(const Transform& new_transform)
	{
		transform = new_transform * transform;
		transformed_mesh.transform(new_transform);
	}

	Mesh get_intermediate_mesh(Number stage) const
	{
		if (stage < 0.0 || stage > 1.0)
			throw std::string("TransformedMesh::get_intermediate_mesh: Requested stage is out of range");
		return original_mesh * (1.0 - stage) + transformed_mesh * stage;
	}

protected:
	Mesh original_mesh, transformed_mesh;
	Transform transform;		// Not actually needed; just to keep track
};

#endif // _TRANSFORMEDMESH_HPP_
