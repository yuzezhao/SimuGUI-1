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
	explicit DropLabel(QWidget *p = 0);

	void dragEnterEvent(QDragEnterEvent*);
	void dropEvent(QDropEvent*);

signals:
	void addModelRequest(QString, QString);

private:
	QString getName(QString);

private:
	QList<modelInfo> modelList;
	QSet<int> CNameSet;
	QSet<int> MatlabNameSet;
	QSet<int> AdamsNameSet;
};

#endif // DROPLABEL_H