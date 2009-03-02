#ifndef _GUIMAINWINDOW_H_
#define _GUIMAINWINDOW_H_

#include <QtGui/QWidget>

class GUITransformedMesh;
class GUITransformGenerator;
class GUITransformInput;

class GUIMainWindow : public QWidget
{
	Q_OBJECT

public:
	GUIMainWindow(QWidget* parent = NULL);

public slots:
	void load_mesh();
	void add_transform();
	void set_transform();

private:
	GUITransformedMesh* transformed_mesh;
	GUITransformGenerator* transform_generator;
	GUITransformInput* transform_input;
	GUITransformInput* transform_monitor;
};

#endif // _GUIMAINWINDOW_H_
