#include <iostream>
#include <Inventor/SoInput.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoSeparator.h>

void point_callback(void* userdata,
		SoCallbackAction* action,
		const SoPrimitiveVertex* v1)
{
	const SbVec3f vtx = v1->getPoint();
	printf("Got point (%f,%f,%f)\n" , vtx[0], vtx[1], vtx[2]);
}

void line_callback(void* userdata,
		SoCallbackAction* action,
		const SoPrimitiveVertex* v1,
		const SoPrimitiveVertex* v2)
{
	const SbVec3f vtx[] = { v1->getPoint(), v2->getPoint() };
	printf("Got line (%f,%f,%f)\t(%f,%f,%f)\n"
			, vtx[0][0], vtx[0][1], vtx[0][2]
			, vtx[1][0], vtx[1][1], vtx[1][2]);
}

void triangle_callback(void* userdata,
		SoCallbackAction* action,
		const SoPrimitiveVertex* v1,
		const SoPrimitiveVertex* v2,
		const SoPrimitiveVertex* v3)
{
	const SbVec3f vtx[] = { v1->getPoint(), v2->getPoint(), v3->getPoint() };
	printf("Got triangle (%f,%f,%f)\t(%f,%f,%f)\t(%f,%f,%f)\n"
			, vtx[0][0], vtx[0][1], vtx[0][2]
			, vtx[1][0], vtx[1][1], vtx[1][2]
			, vtx[2][0], vtx[2][1], vtx[2][2]);
}

int main(int argc, char* argv[])
{
	const char* filename = "test.iv";
	if (argc > 1)
		filename = argv[1];

	SoDB::init();

	SoInput in;
	if (in.openFile(filename))
	{
		SoSeparator* root = SoDB::readAll(&in);
		if (root)
		{
			puts("Salaam!");
			root->ref();
			SoCallbackAction ca;
			ca.addTriangleCallback(SoShape::getClassTypeId(), triangle_callback, NULL);
			ca.addLineSegmentCallback(SoShape::getClassTypeId(), line_callback, NULL);
			ca.addPointCallback(SoShape::getClassTypeId(), point_callback, NULL);
			ca.apply(root);
			root->unref();
			return 0;
		}
	}

	return 1;
}
