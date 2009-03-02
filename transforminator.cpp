#include <QApplication>
#include <Inventor/SoDB.h>

#include "GUIMainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	GUIMainWindow window;
	window.show();
	SoDB::init();
	int ret = app.exec();
	SoDB::finish();
	return ret;
}
