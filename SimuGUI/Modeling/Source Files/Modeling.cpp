
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

	createToolStack();
	createModelStack();

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 9);
	layout->addWidget(title, 0, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(m_pToolStack, 1, 0, 1, 1);
	layout->addWidget(m_pModelLabel, 1, 1, 1, 1);

	widget->setLayout(layout);
	setWidget(widget);
}

void Modeling::createToolStack() {
	m_pToolStack = new ToolDragStack();
	m_pToolStack->setMinimumWidth(100);
	m_pToolStack->setTitle("tool");
}

void Modeling::createModelStack() {

	m_pModelLabel = new DropLabel();
	m_pModelLabel->setStyleSheet("border:3px solid black;");

	m_pModelLabel->setAcceptDrops(true);

	//FancyButton *fb = new FancyButton(tb);
	//fb->setNormalColor(Qt::yellow);
	//fb->setGeometry(90, 10, 80, 80);

	//fb->setIcon(QIcon("./Icon/simutool/c"));
	//fb->setIconSize(fb->size());

	//QGridLayout *layout = new QGridLayout();
	//layout->addWidget(tb);
	//QWidget *modelWidget = new QWidget();
	//modelWidget->setLayout(layout);

	//m_pModelStack->a

}