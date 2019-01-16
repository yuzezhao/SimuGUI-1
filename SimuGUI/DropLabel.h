#pragma once

#ifndef DROPLABEL_H
#define DROPLABEL_H

#include "cwidgets.h"
#include "fancybutton.h"

#define CType "C"
#define MatlabType "Matlab"
#define AdamsType "Adams"

#define DRAG_MOVE "Drag_Move"
#define DRAP_COPY "Drag_Copy"

struct modelInfo {
	QString name;
	QString type;
	QLabel *label;
};

class DropLabel :public QLabel {

	Q_OBJECT

public:
	explicit DropLabel(QWidget *p = 0);

	virtual void dragEnterEvent(QDragEnterEvent*);
	virtual void dropEvent(QDropEvent*);

	virtual void mousePressEvent(QMouseEvent *);
	virtual void dragMoveEvent(QDragMoveEvent *);

signals:
	void addModelRequest(QString, QString);
	void sendMes(QString);

private:
	//ÃûÃüÒýÇæ
	QString getName(QString);

private:
	QList<modelInfo> modelList;
	QSet<int> CNameSet;
	QSet<int> MatlabNameSet;
	QSet<int> AdamsNameSet;
};

#endif // DROPLABEL_H