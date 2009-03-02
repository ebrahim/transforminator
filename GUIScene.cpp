#include "GUIScene.h"

#include <iostream>

#define TEXTURE_FILENAME "../data/cube.bmp"
#define USE_TEXTURE false
#define WIREFRAME 0
#define PERSPECTIVE 0

#define EPSILON (1e-10)

GUIScene::GUIScene(QWidget* parent)
: QGLWidget(parent)
{
}

void
GUIScene::initializeGL()
{
	loadGLTextures();

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLfloat light_position[] = { 3.0f, 3.0f, 5.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

#if WIREFRAME
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_LINE);
#endif
}

void
GUIScene::resizeGL(int width, int height)
{
	if (!height)
		height = 1;

	glViewport(0, 0, (GLint) width, (GLint) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

#if PERSPECTIVE
	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
#else
	glOrtho(-width / 80.0f, width / 80.0f, -height / 80.0f, height / 80.0f, 0.1f, 100.0f);
#endif

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void
GUIScene::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, texture);

	glTranslatef(0.0f, 0.0f, -6.0f);
	glBegin(GL_TRIANGLES);

	for (Mesh::TriangleSet::iterator it = mesh.triangles.begin(); it != mesh.triangles.end(); ++it)
	{
		glTexCoord2f(0.0f, 0.0f);
		float aw = it->a.w();
		if (aw == 0.0f)
			aw = EPSILON;
		glNormal3f(it->a.nx() / aw, it->a.ny() / aw, it->a.nz() / aw);
		glVertex3f(it->a.x() / aw, it->a.y() / aw, it->a.z() / aw);
		glTexCoord2f(1.0f, 0.0f);
		float bw = it->b.w();
		if (bw == 0.0f)
			bw = EPSILON;
		glNormal3f(it->b.nx() / bw, it->b.ny() / bw, it->b.nz() / bw);
		glVertex3f(it->b.x() / bw, it->b.y() / bw, it->b.z() / bw);
		glTexCoord2f(0.0f, 1.0f);
		float cw = it->c.w();
		if (cw == 0.0f)
			cw = EPSILON;
		glNormal3f(it->c.nx() / cw, it->c.ny() / cw, it->c.nz() / cw);
		glVertex3f(it->c.x() / cw, it->c.y() / cw, it->c.z() / cw);
	}
	glEnd();
}

void
GUIScene::loadGLTextures()
{
	QImage t, b;

	if (!USE_TEXTURE || !b.load(TEXTURE_FILENAME))
	{
		b = QImage(16, 16, QImage::Format_ARGB32);
		b.fill(QColor(Qt::blue).rgb());
	}

	t = QGLWidget::convertToGLFormat(b);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
