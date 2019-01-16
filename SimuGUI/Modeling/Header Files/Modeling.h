#pragma once

/*
* @date : 2018/01/04
* @author : jihang
*/

#ifndef MODELING_H
#define MODELING_H

#include "imode.h"

#include "cwidgets.h"
#include "ministack.h"
#include "DropLabel.h"
#include "ToolDragStack.h"

class Modeling : public IMode {

	Q_OBJECT

public:
	explicit Modeling(QWidget *parent = 0);

signals:

public slots:
	void addModel(QString, QString);
	void receiveMes(QString);

private:
	void createWindow();
	void createToolStack();
	void createModelStack();
	void createModelList();

private:
	ToolDragStack *m_pToolStack;
	DropLabel *m_pModelLabel;
	QTableWidget *m_pModelList;
};
#endif // MODELING_H