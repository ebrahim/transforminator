#ifndef _GUITRANSFORMGENERATOR_H_
#define _GUITRANSFORMGENERATOR_H_

#include <QToolBox>

#include "Transform.hpp"

#include "ui_GUITransformGenerator.h"

class GUITransformGenerator : public QToolBox, public Ui::GUITransformGenerator
{
	Q_OBJECT

public:
	GUITransformGenerator(QWidget* parent);

public slots:
	void emit_translation()
	{
		emit transform_generated(Transform::translation(
					translate_x->value(),
					translate_y->value(),
					translate_z->value()));
	}

	void emit_scaling()
	{
		emit transform_generated(Transform::scaling(
					scale_x->value(),
					scale_y->value(),
					scale_z->value()));
	}

	void emit_rotation()
	{
		emit transform_generated(Transform::rotation(
					rotate_x->value() * M_PI / 180,
					rotate_y->value() * M_PI / 180,
					rotate_z->value() * M_PI / 180));
	}

signals:
	void transform_generated(const Transform& transform);
};

#endif // _GUITRANSFORMGENERATOR_H_
