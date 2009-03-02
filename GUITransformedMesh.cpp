#include "GUITransformedMesh.h"

#include <QtCore/QTimer>
#include <QtGui/QSlider>
#include <QtGui/QPushButton>

#define SLIDER_STEPS 1280
#define SLIDER_SINGLE_STEP 10
#define TIMER_INTERVAL 50

GUITransformedMesh::GUITransformedMesh(QWidget* parent)
: QWidget(parent)
{
	timer = new QTimer(this);
	timer->setInterval(TIMER_INTERVAL);

	QVBoxLayout* layout = new QVBoxLayout(this);

	scene = new GUIScene(this);
	layout->addWidget(scene);

	QHBoxLayout* buttons_layout = new QHBoxLayout;
	play_button = new QPushButton("Animate", this);
	slider = new QSlider(Qt::Horizontal, this);
	slider->setRange(0, SLIDER_STEPS);
	slider->setSingleStep(SLIDER_SINGLE_STEP);
	buttons_layout->addWidget(play_button);
	buttons_layout->addWidget(slider);

	layout->addLayout(buttons_layout);

	setLayout(layout);

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(update_scene()));
	connect(play_button, SIGNAL(clicked()), this, SLOT(start_animation()));
	connect(timer, SIGNAL(timeout()), this, SLOT(advance_slider()));
	connect(this, SIGNAL(mesh_changed(const Mesh&, const Mesh&)), this, SLOT(update_scene()));
	connect(this, SIGNAL(transform_changed(const Transform&, const Transform&)), this, SLOT(update_scene()));
}

void
GUITransformedMesh::update_scene()
{
	Number step = slider->value();
	scene->set_mesh(get_intermediate_mesh(step / (Number) SLIDER_STEPS));
	if (step >= SLIDER_STEPS)
		stop_animation();
}

void
GUITransformedMesh::set_mesh(const Mesh& new_mesh)
{
	Mesh old_mesh = original_mesh;
	TransformedMesh::set_mesh(new_mesh);
	emit mesh_changed(original_mesh, old_mesh);
}

void
GUITransformedMesh::reset()
{
	Transform old_transform = transform;
	TransformedMesh::reset();
	emit transform_changed(transform, old_transform);
}

void
GUITransformedMesh::set_transform(const Transform& new_transform)
{
	Transform old_transform = transform;
	TransformedMesh::set_transform(new_transform);
	emit transform_changed(transform, old_transform);
}

void
GUITransformedMesh::add_transform(const Transform& new_transform)
{
	Transform old_transform = transform;
	TransformedMesh::add_transform(new_transform);
	emit transform_changed(transform, old_transform);
}

void
GUITransformedMesh::start_animation()
{
	slider->setSliderPosition(slider->minimum());
	timer->start();
}

void
GUITransformedMesh::stop_animation()
{
	timer->stop();
	slider->setSliderPosition(slider->minimum());
}

void
GUITransformedMesh::advance_slider()
{
	slider->setSliderPosition(slider->sliderPosition() + slider->singleStep());
}
