
#include "HLARunControl.h"

HLARunControl::HLARunControl(QWidget *parent) : IMode(parent) {

	setObjectName(QLatin1String("HLARunControl"));
	setDisplayName(tr("HLA\nRunControl"));
	setIcon(QIcon("./Icon/mode/hlarc"));

	createWindow();
}

void HLARunControl::createWindow() {

	QWidget *widget = new QWidget();

	QLabel *title = new QLabel();
	title->setText("HLA Run Control System");
	QFont font("Microsoft YaHei", 20, 75);
	title->setFont(font);
	title->setAlignment(Qt::AlignCenter);

	MiniStack *functionStack = new MiniStack();
	functionStack->setTitle("function area");
	functionStack->setFixedHeight(180);

	MiniStack *progressBar = new MiniStack();
	progressBar->setTitle("state area");
	progressBar->setFixedHeight(180);

	MiniStack *bar1 = new MiniStack();
	bar1->setTitle("ex area");

	MiniStack *bar2 = new MiniStack();
	bar2->setTitle("ex area");

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->addWidget(title, 0, 0, 1, 2);
	layout->addWidget(functionStack, 1, 0, 1, 1);
	layout->addWidget(progressBar, 1, 1, 1, 1);
	layout->addWidget(bar1, 2, 0, 1, 1);
	layout->addWidget(bar2, 2, 1, 1, 1);

	widget->setLayout(layout);
	setWidget(widget);

	//progressBarÀïÌí¼Óprogress
	StateProgressBar *stateProgressBar = new StateProgressBar();
	stateProgressBar->setType(StateProgressBar::ACK);
	QStringList states;
	states << tr("xxx") << tr("xxx") << tr("xxx") << tr("xxx") << tr("xxx") << tr("xxx") <<tr("xxx");
	stateProgressBar->setStates(states);
	stateProgressBar->setTip("here");
	stateProgressBar->setValue(1);
	//stateProgressBar->setMinimumHeight(140);
	progressBar->addTab(tr("State"), stateProgressBar);

	
}