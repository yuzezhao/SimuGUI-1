#pragma once

#ifndef HLARUNCONTROL_H
#define HLARUNCONTROL_H

#include "imode.h"

#include "cwidgets.h"

#include "tinytabwidget.h"
#include "ministack.h"
#include "stateprogressbar.h"
#include "fancybutton.h"

#include "HLAFlowThread.h"
#include "StateMachineCode.h"

class	HLARunControl : public IMode {

	Q_OBJECT

public:
	explicit HLARunControl(QWidget *parent = 0);

signals:

public slots:
	//处理线程传回的信号信息
	void DisplayFlow(QString);
	//处理线程传回的状态信息
	void DisplayState(int);
	//处理
	void DisplayHLAState(int, QString);

private slots:
	void prepare();
	//void ready();
	//void run();
	//void pause();
	//void end();

private:
	void createWindow();
	void putImage(QString, QLabel*);
	FancyButton* addFunctionButton(FancyButton*, QString);

private:
	HLAFlowThread *flowThread;
	QTextBrowser *info;
	QLabel *stateLabel;
};
#endif // HLARUNCONTROL_H