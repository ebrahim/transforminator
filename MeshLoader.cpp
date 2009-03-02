#include "MeshLoader.h"

#include <iostream>

#include <Inventor/SoInput.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoSeparator.h>

void MeshLoader::point_callback(void* userdata,
		SoCallbackAction* action,
		const SoPrimitiveVertex* v1)
{
#if 0
	Mesh* mesh = static_cast<Mesh*>(userdata);
	const SbVec3f vertices = v1->getPoint();
	fprintf(stderr, "Got point (%f,%f,%f)\n" , vertices[0], vertices[1], vertices[2]);
#endif
}

void MeshLoader::line_callback(void* userdata,
		SoCallbackAction* action,
		const SoPrimitiveVertex* v1,
		const SoPrimitiveVertex* v2)
{
#if 0
	Mesh* mesh = static_cast<Mesh*>(userdata);
	const SbVec3f vertices[] = { v1->getPoint(), v2->getPoint() };
	fprintf(stderr, "Got line (%f,%f,%f)\t(%f,%f,%f)\n"
			, vertices[0][0], vertices[0][1], vertices[0][2]
			, vertices[1][0], vertices[1][1], vertices[1][2]);
#endif
}

void MeshLoader::triangle_callback(void* userdata,
		SoCallbackAction* action,
		const SoPrimitiveVertex* v1,
		const SoPrimitiveVertex* v2,
		const SoPrimitiveVertex* v3)
{
	Mesh* mesh = static_cast<Mesh*>(userdata);
	const SbVec3f vertices[] = { v1->getPoint(), v2->getPoint(), v3->getPoint() };
	const SbVec3f normals[] = { v1->getNormal(), v2->getNormal(), v3->getNormal() };
	Triangle triangle(Point(vertices[0][0], vertices[0][1], vertices[0][2], normals[0][0], normals[0][1], normals[0][2]),
	                  Point(vertices[1][0], vertices[1][1], vertices[1][2], normals[1][0], normals[1][1], normals[1][2]),
	                  Point(vertices[2][0], vertices[2][1], vertices[2][2], normals[2][0], normals[2][1], normals[2][2]));
	mesh->add_triangle(triangle);
#if 0
	fprintf(stderr, "Got triangle (%f,%f,%f)\t(%f,%f,%f)\t(%f,%f,%f)\n"
			, vertices[0][0], vertices[0][1], vertices[0][2]
			, vertices[1][0], vertices[1][1], vertices[1][2]
			, vertices[2][0], vertices[2][1], vertices[2][2]);
#endif
}

Mesh MeshLoader::load(const std::string& filename)
{
	Mesh mesh;

	SoInput in;
	if (!in.openFile(filename.c_str()))
		throw std::string("MeshLoader::load: Failed to open ") + filename;
	SoSeparator* root = SoDB::readAll(&in);
	if (!root)
		throw std::string("MeshLoader::load: Failed to load mesh from ") + filename;
	mesh.clear();
	root->ref();
	SoCallbackAction ca;
	ca.addTriangleCallback(SoShape::getClassTypeId(), triangle_callback, &mesh);
	ca.addLineSegmentCallback(SoShape::getClassTypeId(), line_callback, &mesh);
	ca.addPointCallback(SoShape::getClassTypeId(), point_callback, &mesh);
	ca.apply(root);
	root->unref();

	return mesh;
}
