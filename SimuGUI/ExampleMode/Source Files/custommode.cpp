
/*
* Mode Bar里的选项卡
* @date : 2018/12/12
* @author : jihang
*/

#include "custommode.h"

CustomMode::CustomMode(QWidget *parent) : IMode(parent) {

	setObjectName(QLatin1String("CustomMode"));
	setDisplayName(tr("Custom"));
	setIcon(QIcon("./Icon/mode/custom"));

	//如果需要有东西，则需创建窗口
	createWindow();
}

void CustomMode::createWindow() {

	//第一种插件card
	QGridLayout *pCardLayout = new QGridLayout();
	//两两间隙
	pCardLayout->setSpacing(10);
	//左、上、右、下间隙
	pCardLayout->setContentsMargins(10, 10, 10, 5);
	//建了三张卡片
	createCards();
	//规定每行最多6个，少于6各没事，多于6个再生成一行
	for (int j = 0; j < m_infoCards.count(); j++) {
		pCardLayout->addWidget(m_infoCards.at(j), j / 6, j % 6);
	}

	//第二种插件stack
	MiniStack *stack1 = new MiniStack();
	stack1->setTitle(tr("Device Chooser"));
	stack1->setTitleMargins(5, 1, 5, 1);

	//stack里放plot和其他三个
	MiniStack *stack2 = new MiniStack();
	stack2->setTitle(tr("real-time curve - chart"));
	stack2->setTitleMargins(5, 1, 5, 1);
	stack2->addTab(tr("Tab1"), new QCustomChart());
	stack2->addTab(tr("Tab2"), new QWidget);
	stack2->addTab(tr("Tab3"), new QWidget);
	stack2->addTab(tr("Tab4"), new QWidget);

	//stack的布局
	QHBoxLayout *pStackLayout = new QHBoxLayout();
	pStackLayout->setContentsMargins(10, 5, 10, 5);
	pStackLayout->setSpacing(10);
	pStackLayout->addWidget(stack1);
	pStackLayout->addWidget(stack2);

	//以上两种插件的布局，放到一个QWidget里
	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addLayout(pCardLayout);
	layout->addLayout(pStackLayout);
	layout->addStretch();
	QWidget *w = new QWidget();
	w->setLayout(layout);

	//又创建一个和以上相同的table2
	TinyTabWidget *tabWidget2 = new TinyTabWidget();
	tabWidget2->addTab(new QWidget(), tr("tab77"));
	tabWidget2->addTab(new QWidget(), tr("tab88"));

	tabWidget2->setTextColor(QColor(10, 10, 10));
	tabWidget2->setSelectedTextColor(QColor(255, 255, 255));
	tabWidget2->setHoverColor(QColor(180, 180, 180));
	tabWidget2->setBackgroundColor(QColor(100, 0, 200, 120));
	tabWidget2->setTabPosition(TinyTabWidget::South);
	//tabWidget1->setTabPosition(TinyTabWidget::West);
	//tabWidget3->setTabPosition(TinyTabWidget::South);
	//tabWidget->setTabPosition(TinyTabWidget::East);

	//把w和table2放到上面
	TinyTabWidget *tabWidget = new TinyTabWidget();
	tabWidget->addTab(w, tr("tab1"));
	tabWidget->addTab(tabWidget2, tr("tab2"));

	tabWidget->setTextColor(QColor(10, 10, 10));
	tabWidget->setSelectedTextColor(QColor(255, 255, 255));
	tabWidget->setHoverColor(QColor(180, 180, 180));
	tabWidget->setBackgroundColor(QColor(0, 0, 0, 20));
	tabWidget->setTabPosition(TinyTabWidget::North);

	setWidget(tabWidget);
}

//创建卡片
void CustomMode::createCards() {
	MiniCard *card = new MiniCard();
	card->setTitle(tr("Device"));
	card->setInfo(tr("Device info"));
	card->setValue("0");
	card->setDesc(tr("Online num"));
	card->setNote(tr("Total: 0"));
	m_infoCards.append(card);

	card = new MiniCard();
	card->setTitle(tr("Sensor"));
	card->setInfo(tr("Sensor info"));
	card->setValue("0");
	card->setDesc(tr("Total"));
	card->setNote("20%");
	card->setInfoBackgroundColor(QColor(35, 198, 200));
	card->setNoteColor(QColor(35, 198, 200, 255));
	m_infoCards.append(card);

	card = new MiniCard();
	card->setTitle(tr("Warning record"));
	card->setInfo(tr("Warning info"));
	card->setValue("0");
	card->setDesc(tr("Warning num"));
	card->setNote(QDateTime::currentDateTime().toString("MM/dd hh:mm"));
	card->setInfoBackgroundColor(QColor(248, 172, 89));
	card->setNoteColor(QColor(35, 198, 200));
	m_infoCards.append(card);
}