#pragma once

/*
* @date : 2018/01/07
* @author : jihang
*/

#ifndef FMIADVANCE_H
#define FMIADVANCE_H

#include "imode.h"

#include "cwidgets.h"

class FMIAdvance : public IMode {

	Q_OBJECT

public:
	explicit FMIAdvance(QWidget *parent = 0);

signals:

public slots:
	//void test();

private:
	void createWindow();
};
#endif // FMIADVANCE_H