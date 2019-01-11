#pragma once

#ifndef DROPLABEL_H
#define DROPLABEL_H

#include "cwidgets.h"
#include "fancybutton.h"

#define CType "C"
#define MatlabType "Matlab"
#define AdamsType "Adams"

struct modelInfo {
	QString name;
	QString type;
	QLabel *label;
};

class DropLabel :public QLabel {

	Q_OBJECT

public:
	DropLabel(QWidget *p = 0) : QLabel(p) {}

	void dragEnterEvent(QDragEnterEvent*);
	void dropEvent(QDropEvent*);

signals:
	void addModelRequest(QString, QString);

private:
	QList<modelInfo> modelList;
};

#endif // DROPLABEL_H