#include "QTreeWidget_QMap.h"

QTreeWidget_QMap::QTreeWidget_QMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
	connect(ui.treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));
}
void QTreeWidget_QMap::init()
{
	ui.treeWidget->clear();    //��ʼ�����οؼ�

	//�����һ��������
	QTreeWidgetItem* group1 = new QTreeWidgetItem(ui.treeWidget);
	group1->setText(0, "group1");    //���οؼ���ʾ���ı���Ϣ
	group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);   //�������οؼ����������
	group1->setCheckState(0, Qt::Unchecked); //��ʼ״̬û�б�ѡ��
	//��һ������
	QTreeWidgetItem* subItem11 = new QTreeWidgetItem(group1);
	subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	subItem11->setText(0, "subItem11");  //����������ʾ���ı�
	subItem11->setCheckState(0, Qt::Unchecked); //������ѡ�����ʾ��ʽ��״̬

	QTreeWidgetItem* subItem12 = new QTreeWidgetItem(group1);
	subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	subItem12->setText(0, "subItem12");
	subItem12->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* subItem13 = new QTreeWidgetItem(group1);
	subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	subItem13->setText(0, "subItem13");
	subItem13->setCheckState(0, Qt::Unchecked);

	//����ڶ���������
	QTreeWidgetItem* group2 = new QTreeWidgetItem(ui.treeWidget);
	group2->setText(0, "group2");
	group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	group2->setCheckState(0, Qt::Unchecked);

	//�ڶ�������
	QTreeWidgetItem* subItem21 = new QTreeWidgetItem(group2);   //ָ������������һ������
	subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	subItem21->setText(0, "subItem21");
	subItem21->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* subItem22 = new QTreeWidgetItem(group2);
	subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	subItem22->setText(0, "subItem22");
	subItem22->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* subItem23 = new QTreeWidgetItem(group2);
	subItem23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	subItem23->setText(0, "subItem23");
	subItem23->setCheckState(0, Qt::Unchecked);
}
void QTreeWidget_QMap::treeItemChanged(QTreeWidgetItem* item, int column)
{
	//QString itemText = item->text(0);
	if (Qt::Checked == item->checkState(0))
	{
		// QTreeWidgetItem* parent = item->parent();
		int count = item->childCount(); //��������ĸ���
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				item->child(i)->setCheckState(0, Qt::Checked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
	else if (Qt::Unchecked == item->checkState(0))
	{
		int count = item->childCount();
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				item->child(i)->setCheckState(0, Qt::Unchecked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
}
void QTreeWidget_QMap::updateParentItem(QTreeWidgetItem* item)
{
	QTreeWidgetItem *parent = item->parent();
	if (parent == NULL)
	{
		return;
	}
	int selectedCount = 0;
	int childCount = parent->childCount();
	for (int i = 0; i < childCount; i++) //�ж��ж��ٸ����ѡ��
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			selectedCount++;
		}
	}
	if (selectedCount <= 0)  //���û�����ѡ�У���������Ϊδѡ��״̬
	{
		parent->setCheckState(0, Qt::Unchecked);
	}
	else if (selectedCount > 0 && selectedCount < childCount)    //����в������ѡ�У���������Ϊ����ѡ��״̬�����û�ɫ��ʾ
	{
		parent->setCheckState(0, Qt::PartiallyChecked);
	}
	else if (selectedCount == childCount)    //�������ȫ����ѡ�У�����������Ϊѡ��״̬
	{
		parent->setCheckState(0, Qt::Checked);
	}
}
