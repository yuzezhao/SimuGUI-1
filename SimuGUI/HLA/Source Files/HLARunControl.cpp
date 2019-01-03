
/*
* 仿真控制GUI
* @date : 2018/12/26
* @author : jihang
*/

#include "HLARunControl.h"

HLARunControl::HLARunControl(QWidget *parent) : IMode(parent) {

	setObjectName(QLatin1String("HLARunControl"));
	setDisplayName(tr("HLA\nRunControl"));
	setIcon(QIcon("./Icon/mode/hlarc"));

	createWindow();

	flowThread = new HLAFlowThread();
	connect(flowThread, SIGNAL(FlowSignal(QString)), this, SLOT(DisplayFlow(QString)));
	connect(flowThread, SIGNAL(StateSignal(int)), this, SLOT(DisplayState(int)));
	connect(flowThread->getInstance(), SIGNAL(postUIMsg(QString)), this, SLOT(DisplayHLAState(QString)));
	connect(flowThread->getInstance(), SIGNAL(postUITime(double)), this, SLOT(DisplayHLATime(double)));
}

void HLARunControl::createWindow() {

	QWidget *widget = new QWidget();

	QLabel *title = new QLabel();
	title->setText("HLA Run Control System");
	QFont font("Microsoft YaHei", 20, 75);
	title->setFont(font);

	lcdNumber = new QLCDNumber();
	lcdNumber->setSegmentStyle(QLCDNumber::Flat);
	lcdNumber->setFixedWidth(200);

	MiniStack *functionStack = new MiniStack();
	functionStack->setTitle("function area");
	functionStack->setFixedWidth(300);
	FancyButton *prepare = new FancyButton();
	prepare = addFunctionButton(prepare, "prepare");
	connect(prepare, SIGNAL(clicked()), this, SLOT(prepare()));
	FancyButton *ready = new FancyButton();
	ready = addFunctionButton(ready, "ready");
	connect(ready, SIGNAL(clicked()), this, SLOT(ready()));
	FancyButton *stop = new FancyButton();
	stop = addFunctionButton(stop, "stop");
	connect(stop, SIGNAL(clicked()), this, SLOT(stop()));
	FancyButton *start = new FancyButton();
	start = addFunctionButton(start, "start");
	connect(start, SIGNAL(clicked()), this, SLOT(start()));
	FancyButton *pause = new FancyButton();
	pause = addFunctionButton(pause, "pause");
	connect(pause, SIGNAL(clicked()), this, SLOT(pause()));
	QGridLayout *buttonLayout = new QGridLayout();
	buttonLayout->addWidget(prepare, 0, 0, 1, 1);
	buttonLayout->addWidget(ready, 0, 1, 1, 1);
	buttonLayout->addWidget(stop, 0, 2, 1, 1);
	buttonLayout->addWidget(start, 1, 0, 1, 1);
	buttonLayout->addWidget(pause, 1, 1, 1, 1);
	QWidget *buttonGroup = new QWidget();
	buttonGroup->setLayout(buttonLayout);
	functionStack->addTab(tr("function"), buttonGroup);

	MiniStack *stateStack = new MiniStack();
	stateStack->setTitle("state area");
	stateStack->setFixedWidth(300);
	stateLabel = new QLabel();
	stateLabel->setAlignment(Qt::AlignCenter);
	putImage("1", stateLabel);
	QHBoxLayout *stateLayout = new QHBoxLayout();
	stateLayout->addWidget(stateLabel);
	QWidget *stateWidget = new QWidget();
	stateWidget->setLayout(stateLayout);
	stateStack->addTab(tr("state"), stateWidget);

	MiniStack *bar2 = new MiniStack();
	bar2->setTitle("empty area");

	MiniStack *infoStack = new MiniStack();
	infoStack->setTitle("information area");
	info = new QTextBrowser();
	QHBoxLayout *infoLayout = new QHBoxLayout();
	infoLayout->addWidget(info);
	QWidget *infoWidget = new QWidget();
	infoWidget->setLayout(infoLayout);
	infoStack->addTab(tr("state"), infoWidget);

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->addWidget(title, 0, 0, 1, 5, Qt::AlignCenter);
	layout->addWidget(lcdNumber, 1, 0, 1, 5, Qt::AlignRight);
	layout->addWidget(functionStack, 2, 0, 1, 1);
	layout->addWidget(stateStack, 3, 0, 1, 1);
	layout->addWidget(bar2, 2, 1, 2, 2);
	layout->addWidget(infoStack, 2, 3, 2, 2);

	widget->setLayout(layout);
	setWidget(widget);
}

void HLARunControl::putImage(QString path, QLabel *label) {
	QPixmap *pixmap = new QPixmap("./Icon/hlaState/" + path);
	pixmap->scaled(label->size(), Qt::KeepAspectRatio);
	label->setScaledContents(true);
	label->setPixmap(*pixmap);
}

FancyButton* HLARunControl::addFunctionButton(FancyButton* button, QString name) {
	QFont font("Microsoft YaHei", 15);
	button->setFixedHeight(60);
	button->setTextColor(Qt::black);
	button->setFont(font);
	button->setText(name);
	button->setNormalColor(Qt::gray);
	button->setHoverColor(Qt::green);
	return button;
}

void HLARunControl::DisplayFlow(QString msg) {
	info->append("#FlowThread#" + msg);
}

void HLARunControl::DisplayState(int state) {
	if (state == StateMachineCode::getJoinedCode()) {
		putImage("2", stateLabel);
	}
	else if (state == StateMachineCode::getInitialedCode()) {
		putImage("3", stateLabel);
	}
	else if (state == StateMachineCode::getRegisPointCode()) {
		putImage("4", stateLabel);
	}
	else if (state == StateMachineCode::getSynchedCode()) {
		putImage("5", stateLabel);
	}
	else if (state == StateMachineCode::getPubAndSubCode()) {
		putImage("6", stateLabel);
	}
	else if (state == StateMachineCode::getRegisteredCode()) {
		putImage("7", stateLabel);
	}
	else if (state == StateMachineCode::getRunningCode()) {
		putImage("8", stateLabel);
	}
}

void HLARunControl::DisplayHLAState(QString msg) {
	info->append("#PortAdapter#" + msg);
}

void HLARunControl::DisplayHLATime(double time) {
	lcdNumber->display(time);
}

void HLARunControl::prepare() {
	//判断流程状态
	if (flowThread->getState() != StateMachineCode::getUnstartCode()) {
		QMessageBox::warning(NULL, "Warning", "Environment Already Established!!!");
		return;
	}
	//create必须是主线程执行！！！！！！！！！！
	info->append("Preparing Environment, Please Wait...");
	QCoreApplication::processEvents();
	InterfaceResponse<bool> *ir = flowThread->getInstance()->createFederation();
	if (!ir->isSuccessful()) {
		info->append("HERE IS AN ERROR");
	}
	info->append(ir->getMessage().c_str());
	flowThread->start();
}

void HLARunControl::ready() {
	//判断流程状态
	if (flowThread->getState() != StateMachineCode::getRegisPointCode()) {
		QMessageBox::warning(NULL, "Warning", "WRONG CLICK!!!");
		return;
	}
	info->append("please wait for others patiently...");
	flowThread->start();
}

void HLARunControl::start() {
	if (flowThread->getState() == StateMachineCode::getRegisteredCode()) {
		flowThread->start();
	}
	else if (flowThread->getState() == StateMachineCode::getRunningCode()) {
		if (flowThread->getInstance()->isPause) {
			flowThread->getInstance()->isPause = false;
			putImage("8", stateLabel);
		}
	}
	else {
		QMessageBox::warning(NULL, "Warning", "WRONG CLICK!!!");
	}
}

void HLARunControl::pause() {
	//判断流程状态
	if (flowThread->getState() != StateMachineCode::getRunningCode()) {
		QMessageBox::warning(NULL, "Warning", "Simulation Not Run!!!");
		return;
	}
	flowThread->getInstance()->isPause = true;
	putImage("9", stateLabel);
}

void HLARunControl::end() {
	//TODO：点END卡住就退了
	//判断流程状态
	if (flowThread->getState() != StateMachineCode::getRunningCode()) {
		QMessageBox::warning(NULL, "Warning", "WRONG CLICK!!!");
		return;
	}
	flowThread->getInstance()->isEnd = true;
	putImage("10", stateLabel);
}