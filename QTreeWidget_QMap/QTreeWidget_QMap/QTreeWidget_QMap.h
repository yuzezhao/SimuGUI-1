#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTreeWidget_QMap.h"
#include<QTreeWidgetItem>

class QTreeWidget_QMap : public QMainWindow
{
	Q_OBJECT

public:
	QTreeWidget_QMap(QWidget *parent = Q_NULLPTR);

private:
	Ui::QTreeWidget_QMapClass ui;


public: 
	void init();
	void updateParentItem(QTreeWidgetItem* item);

public slots:   
	void treeItemChanged(QTreeWidgetItem* item, int column);
	
};
