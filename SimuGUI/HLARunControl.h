#pragma once

#ifndef HLARUNCONTROL_H
#define HLARUNCONTROL_H

#include "imode.h"

#include "cwidgets.h"

#include "tinytabwidget.h"
#include "ministack.h"
#include "stateprogressbar.h"

class	HLARunControl : public IMode {

	Q_OBJECT

public:
	explicit HLARunControl(QWidget *parent = 0);

signals:

public slots:

private:
	void createWindow();
};
#endif // HLARUNCONTROL_H