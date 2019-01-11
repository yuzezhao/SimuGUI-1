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
#include "DragButton.h"
#include "DropLabel.h"
#include "ToolDragStack.h"

class Modeling : public IMode {

	Q_OBJECT

public:
	explicit Modeling(QWidget *parent = 0);

signals:

public slots:
	//void test();

private:
	void createWindow();
	void createToolStack();
	void createModelStack();

private:
	ToolDragStack *m_pToolStack;
	DropLabel *m_pModelLabel;
};
#endif // MODELING_H