
#include "FMIAdvance.h"

FMIAdvance::FMIAdvance(QWidget *parent) : IMode(parent) {

	setObjectName(QLatin1String("FMIAdvance"));
	setDisplayName(tr("FMI\nAdvance"));
	setIcon(QIcon("./Icon/mode/fmi"));

	createWindow();
}

void FMIAdvance::createWindow() {

	QWidget *widget = new QWidget();

	QLabel *title = new QLabel();
	title->setText("FMU Simulator Advance");
	QFont font("Microsoft YaHei", 20, 75);
	title->setFont(font);

	//QPushButton *button = new QPushButton();
	//connect(button, SIGNAL(clicked()), this, SLOT(test()));

	//textBrowser = new QTextBrowser();

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->addWidget(title, 0, 0, 1, 2, Qt::AlignCenter);
	//layout->addWidget(button, 1, 0, 1, 1);
	//layout->addWidget(textBrowser, 1, 1, 1, 1);

	widget->setLayout(layout);
	setWidget(widget);
}