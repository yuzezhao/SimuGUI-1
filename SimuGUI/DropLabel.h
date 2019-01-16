#pragma once

#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <set>

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
	int count;
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

public slots:
	void deleteModel(QString);

private:
	//ÃûÃüÒýÇæ
	modelInfo getModel(QString);

private:
	QList<modelInfo> modelList;
	std::set<int> CNameSet;
	std::set<int> MatlabNameSet;
	std::set<int> AdamsNameSet;
};

#endif // DROPLABEL_H