#include "matmodel.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	matmodel r;
	r.resize(1100, 600);
	r.show();
	return app.exec();
}
