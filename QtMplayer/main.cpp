#include "QtMplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtMplayer w;
	w.show();
	return a.exec();
}
