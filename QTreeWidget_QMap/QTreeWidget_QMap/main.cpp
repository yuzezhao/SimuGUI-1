#include "QTreeWidget_QMap.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTreeWidget_QMap w;
	w.show();
	return a.exec();
}
