#ifndef _GUITRANSFORMEDMESH_H_
#define _GUITRANSFORMEDMESH_H_

#include "TransformedMesh.hpp"
#include "GUIScene.h"

class QSlider;
class QTimer;

class GUITransformedMesh : public QWidget, public TransformedMesh
{
	Q_OBJECT

public:
	GUITransformedMesh(QWidget* parent);

public slots:
	void update_scene();
	void set_mesh(const Mesh& new_mesh);
	void reset();
	void set_transform(const Transform& new_transform);
	void add_transform(const Transform& new_transform);
	void start_animation();
	void stop_animation();
	void advance_slider();

signals:
	void mesh_changed(const Mesh& new_mesh, const Mesh& old_mesh);
	void transform_changed(const Transform& new_transform, const Transform& old_transform);

protected:
	GUIScene* scene;
	QPushButton* play_button;
	QSlider* slider;
	QTimer* timer;
};

#endif // _GUITRANSFORMEDMESH_H_
