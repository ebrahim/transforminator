#include "GUIMainWindow.h"

#include <iostream>

#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include "Transform.hpp"
#include "MeshLoader.h"

#include "GUITransformedMesh.h"
#include "GUITransformGenerator.h"
#include "GUITransformInput.h"

#define DEFAULT_MESH_FILENAME "../data/obj.wrl"

GUIMainWindow::GUIMainWindow(QWidget* parent)
: QWidget(parent)
{
	QVBoxLayout* main_layout = new QVBoxLayout(this);

	QPushButton* load_button = new QPushButton("Load Model", this);
	main_layout->addWidget(load_button);

	transformed_mesh = new GUITransformedMesh(this);
	main_layout->addWidget(transformed_mesh);

	QHBoxLayout* transform_inputs_layout = new QHBoxLayout;
	transform_generator = new GUITransformGenerator(this);
	transform_input = new GUITransformInput(this);
	transform_monitor = new GUITransformInput(this);
	transform_inputs_layout->addWidget(transform_generator, 0, Qt::AlignHCenter);
	transform_inputs_layout->addWidget(transform_input, 0, Qt::AlignHCenter);
	transform_inputs_layout->addWidget(transform_monitor, 0, Qt::AlignHCenter);
	main_layout->addLayout(transform_inputs_layout);

	QHBoxLayout* transform_buttons_layout = new QHBoxLayout;
	QPushButton* add_transform_button = new QPushButton("Add Transformation", this);
	QPushButton* set_transform_button = new QPushButton("Set Transformation", this);
	transform_buttons_layout->addWidget(add_transform_button);
	transform_buttons_layout->addWidget(set_transform_button);
	main_layout->addLayout(transform_buttons_layout);

	setLayout(main_layout);

	setMinimumSize(640, 480);

	connect(load_button, SIGNAL(clicked()),
			this, SLOT(load_mesh()));
	connect(add_transform_button, SIGNAL(clicked()),
			this, SLOT(add_transform()));
	connect(set_transform_button, SIGNAL(clicked()),
			this, SLOT(set_transform()));
	connect(transform_generator, SIGNAL(transform_generated(const Transform&)),
			transform_input, SLOT(set(const Transform&)));
	connect(transform_monitor, SIGNAL(value_changed(const Transform&)),
			transformed_mesh, SLOT(set_transform(const Transform&)));
	connect(transformed_mesh, SIGNAL(transform_changed(const Transform&, const Transform&)),
			transform_monitor, SLOT(set(const Transform&)));

	// Load a default mesh
	try
	{
		transformed_mesh->set_mesh(MeshLoader::load(DEFAULT_MESH_FILENAME));
	}
	catch (const std::string& e)
	{
		std::cerr << e << std::endl;
		QMessageBox::warning(this, "Default mesh file not found",
				"Unable to find the default mesh file\n"
				"You'll need to load a mesh file manually");
	}
}

void GUIMainWindow::load_mesh()
{
	for (;;)
	{
		QString mesh_filename = QFileDialog::getOpenFileName(this, "Open mesh file");
		if (mesh_filename.isNull())
			break;
		try
		{
			transformed_mesh->set_mesh(MeshLoader::load(mesh_filename.toStdString()));
			break;
		}
		catch (const std::string& e)
		{
			QMessageBox::critical(this, "Failed", "Failed to load mesh from the selected file");
		}
	}
}

void GUIMainWindow::add_transform()
{
	transformed_mesh->add_transform(transform_input->get());
	transform_input->reset();
}

void GUIMainWindow::set_transform()
{
	transformed_mesh->set_transform(transform_input->get());
	transform_input->reset();
}
