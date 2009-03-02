#ifndef _GUISCENE_H_
#define _GUISCENE_H_

#include <QtOpenGL>

#include "Mesh.hpp"

class GUIScene : public QGLWidget
{
	Q_OBJECT

public:
	GUIScene(QWidget* parent);

	void set_mesh(const Mesh& new_mesh)
	{
		mesh = new_mesh;
		updateGL();
	}

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void loadGLTextures();

	Mesh mesh;
	GLuint texture;
};

#endif // _GUISCENE_H_
