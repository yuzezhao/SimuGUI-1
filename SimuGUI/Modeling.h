#pragma once

/*
* @date : 2018/01/04
* @author : jihang
*/

#ifndef MODELING_H
#define MODELING_H

#include "imode.h"

#include "cwidgets.h"

class Modeling : public IMode {

	Q_OBJECT

public:
	explicit Modeling(QWidget *parent = 0);

signals:

public slots:
	//void test();

private:
	void createWindow();
};
#endif // MODELING_H