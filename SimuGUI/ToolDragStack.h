#pragma once

#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include "cwidgets.h"
#include "ministack.h"
#include "fancybutton.h"

class ToolDragStack :public MiniStack {

	Q_OBJECT

public:

	explicit ToolDragStack(QWidget *p = 0);

	~ToolDragStack() {};

	virtual void mousePressEvent(QMouseEvent *e);

	Qt::DropAction m_acceptableDropAction;

	QLabel* m_cLabel;
	QLabel* m_matlabLabel;
	QLabel* m_adamsLabel;

	QLabel* m_dragLabel;

private:
	void putImage(QString, QLabel *);
};

#endif // TOOLWIDGET_H