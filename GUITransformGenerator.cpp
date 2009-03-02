#include "GUITransformGenerator.h"

GUITransformGenerator::GUITransformGenerator(QWidget* parent)
: QToolBox(parent)
{
	setupUi(this);
	retranslateUi(this);
	connect(translate, SIGNAL(clicked()), this, SLOT(emit_translation()));
	connect(scale, SIGNAL(clicked()), this, SLOT(emit_scaling()));
	connect(rotate, SIGNAL(clicked()), this, SLOT(emit_rotation()));
	setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed));
}
