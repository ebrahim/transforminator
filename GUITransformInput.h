#ifndef _GUITRANSFORMINPUT_H_
#define _GUITRANSFORMINPUT_H_

#include <QtGui/QDoubleSpinBox>

#include "Transform.hpp"

class GUITransformInput : public QWidget
{
	Q_OBJECT

public:
	GUITransformInput(QWidget* parent, double min = -99.99, double max = 99.99, double step = 0.2);

	Transform get();

public slots:
	void set(const Transform& transform);
	void reset()
	{
		set(Transform(Transform::Identity));
	}
	void handle_change()
	{
		emit value_changed(get());
	}

signals:
	void value_changed(const Transform& transform);

protected:
	QDoubleSpinBox* matrix[Transform::Rows][Transform::Cols];
};

#endif // _GUITRANSFORMINPUT_H_
