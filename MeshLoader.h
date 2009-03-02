#ifndef _MESHLOADER_H_
#define _MESHLOADER_H_

#include <string>

#include "Mesh.hpp"

class SoCallbackAction;
class SoPrimitiveVertex;

class MeshLoader
{
public:
	static Mesh load(const std::string& file_name);

private:
	static void point_callback(void* userdata,
			SoCallbackAction* action,
			const SoPrimitiveVertex* v1);
	static void line_callback(void* userdata,
			SoCallbackAction* action,
			const SoPrimitiveVertex* v1,
			const SoPrimitiveVertex* v2);
	static void triangle_callback(void* userdata,
			SoCallbackAction* action,
			const SoPrimitiveVertex* v1,
			const SoPrimitiveVertex* v2,
			const SoPrimitiveVertex* v3);
};

#endif // _MESHLOADER_H_
