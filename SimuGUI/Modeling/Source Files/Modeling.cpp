
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
	createModelList();

	connect(m_pModelLabel, SIGNAL(addModelRequest(QString, QString)),
		this, SLOT(addModel(QString, QString)));

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 9);
	layout->addWidget(title, 0, 0, 1, 3, Qt::AlignCenter);
	layout->addWidget(m_pToolStack, 1, 0, 1, 1);
	layout->addWidget(m_pModelLabel, 1, 1, 1, 1);
	layout->addWidget(m_pModelList, 1, 2, 1, 1);

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
}

void Modeling::createModelList() {
	m_pModelList = new QTableWidget();

	//表头
	m_pModelList->setColumnCount(3);
	//m_pModelList->horizontalHeader()->setDefaultSectionSize(80);
	m_pModelList->horizontalHeader()->setSectionsClickable(false);
	m_pModelList->setColumnWidth(1, 80);
	m_pModelList->setColumnWidth(2, 30);
	m_pModelList->setColumnWidth(3, 30);

	QFont font;
	font.setBold(true);
	m_pModelList->horizontalHeader()->setFont(font);
	//m_pModelList->horizontalHeader()->setStretchLastSection(true);
	m_pModelList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

	//列
	m_pModelList->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	m_pModelList->verticalHeader()->setVisible(false);

	//选择模式
	m_pModelList->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pModelList->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pModelList->setStyleSheet("selection-background-color:lightblue;");

	QStringList header;
	header << "Name" << "Type" << "Delete";
	m_pModelList->setHorizontalHeaderLabels(header);

	m_pModelList->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
	m_pModelList->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
}

void Modeling::addModel(QString modelName, QString modelType) {
	int row = m_pModelList->rowCount();
	m_pModelList->insertRow(row);
	m_pModelList->setItem(row, 0, new QTableWidgetItem(modelName));
	m_pModelList->setItem(row, 1, new QTableWidgetItem(modelType));
	m_pModelList->setItem(row, 2, new QTableWidgetItem(QIcon("./Icon/tools/delete"), NULL));
}