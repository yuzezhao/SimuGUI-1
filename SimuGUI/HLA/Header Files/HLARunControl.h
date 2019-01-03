#pragma once

/*
* 仿真控制GUI
* @date : 2018/12/26
* @author : jihang
*/

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
	//处理HLA状态信息
	void DisplayHLAState(QString);
	//处理HLA时间信息
	void DisplayHLATime(double);

private slots:
	void prepare();
	void ready();
	void start();
	void pause();
	void end();

private:
	void createWindow();
	void putImage(QString, QLabel*);
	FancyButton* addFunctionButton(FancyButton*, QString);

private:
	//线程对象
	HLAFlowThread *flowThread;
	//文本添加对象
	QTextBrowser *info;
	//状态图对象
	QLabel *stateLabel;
	//计时对象
	QLCDNumber *lcdNumber;
};

#endif // HLARUNCONTROL_H