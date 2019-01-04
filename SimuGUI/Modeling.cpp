
#include "Modeling.h"

Modeling::Modeling(QWidget *parent) : IMode(parent) {

	setObjectName(QLatin1String("Modeling"));
	setDisplayName(tr("Modeling"));
	setIcon(QIcon("./Icon/mode/model"));

	createWindow();
}

void Modeling::createWindow() {

	QWidget *widget = new QWidget();

	QLabel *title = new QLabel();
	title->setText("Modeling");
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