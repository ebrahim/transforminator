#include "GUITransformInput.h"

#include <QtGui/QGridLayout>

GUITransformInput::GUITransformInput(QWidget* parent, double min, double max, double step)
: QWidget(parent)
{
	QGridLayout* layout = new QGridLayout(this);
	for (int i = 0; i < Transform::Rows; ++i)
		for (int j = 0; j < Transform::Cols; ++j)
		{
			matrix[i][j] = new QDoubleSpinBox;
			matrix[i][j]->setRange(min, max);
			matrix[i][j]->setSingleStep(step);
			connect(matrix[i][j], SIGNAL(valueChanged(double)), this, SLOT(handle_change()));
			layout->addWidget(matrix[i][j], i, j);
		}
	setLayout(layout);
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	reset();
}

void
GUITransformInput::set(const Transform& transform)
{
	bool changed = transform != get();
	blockSignals(true);
	for (int i = 0; i < Transform::Rows; ++i)
		for (int j = 0; j < Transform::Cols; ++j)
			matrix[i][j]->setValue(transform.matrix[i][j]);
	blockSignals(false);
	if (changed)
		handle_change();
}

Transform
GUITransformInput::get()
{
	Transform transform;
	for (int i = 0; i < Transform::Rows; ++i)
		for (int j = 0; j < Transform::Cols; ++j)
			transform.matrix[i][j] = matrix[i][j]->value();
	return transform;
}
