
#include "FMISimulator.h"

#include "FMISupport.h"

FMISimulator::FMISimulator(QWidget *parent) : IMode(parent) {

	setObjectName(QLatin1String("FMISimulator"));
	setDisplayName(tr("FMI\nSimulator"));
	setIcon(QIcon("./Icon/mode/fmi"));

	createWindow();
}

void FMISimulator::createWindow() {

	QWidget *widget = new QWidget();

	QLabel *title = new QLabel();
	title->setText("FMI Simulator");
	QFont font("Microsoft YaHei", 20, 75);
	title->setFont(font);

	QPushButton *button = new QPushButton();
	connect(button, SIGNAL(clicked()), this, SLOT(test()));

	textBrowser = new QTextBrowser();

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->addWidget(title, 0, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(button, 1, 0, 1, 1);
	layout->addWidget(textBrowser, 1, 1, 1, 1);

	widget->setLayout(layout);
	setWidget(widget);
}

void FMISimulator::test() {
	FMISupport *fs = new FMISupport();
	connect(fs, SIGNAL(postUIMsg(QString)), this, SLOT(DisplayFMIMsg(QString)));
	if (!fs->loadFMU("D:\\bouncingBall.fmu", FMI_COSIMULATION)) {
		textBrowser->append("error in load fmu");
		return;
	}

	fs->simulateByCs(0.0, 30.0, 0.1, 0, NULL);
	//f->unLoad();
}

void FMISimulator::DisplayFMIMsg(QString s) {
	textBrowser->append(s);
}