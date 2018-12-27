
/*
* 皮肤源文件
* @date : 2018/12/18
* @author : jihang
*/

#include "skindialog.h"

#define SKIN_NUM 15
#define SKIN_RES_NAME(n)   QString("./Icon/skin/%1").arg(n)
#define THEME_PATH QString("./Icon/theme")

SkinDialog::SkinDialog(QWidget *parent) : FancyDialog(parent) {

	m_pLastSkinItem = 0;
	m_skinItemList.clear();
	m_pThemeComboBox = 0;
	m_themeMap.clear();

	createWindow();

	setFixedSize(800, 600);
	setWindowTitle(tr("Change Skin and Theme"));
	setWindowIcon(QIcon("./Icon/main/logo"));
}

//在setting里存储着当前的skin和themeTODO
void SkinDialog::createWindow() {

	QWidget *pCentralWidget = new QWidget();

	//放skin的
	TinyTabWidget * m_pTabWidget = new TinyTabWidget();
	m_pTabWidget->setHoverColor(Theme::g_tinyTabHoverColor);
	m_pTabWidget->setPressColor(Theme::g_tinyTabPressColor);
	m_pTabWidget->setTextColor(Theme::g_tinyTabTextColor);
	m_pTabWidget->setSelectedTextColor(Theme::g_tinyTabSelectedTextColor);
	m_pTabWidget->setBackgroundColor(Theme::g_tinyTabBackgroundColor);
	m_pTabWidget->setNormalColor(Theme::g_tinyTabNormalColor);
	m_pTabWidget->setSlideColor(Theme::g_tinyTabSlideColor);

	//widget上加area使用tab页
	CentralArea *area = new CentralArea();
	m_pTabWidget->addTab(area, tr("All page"));

	//area上必须有一个widget
	QWidget *allPageWidget = new QWidget();
	QGridLayout *pGridLayout = new QGridLayout();
	pGridLayout->setSpacing(15);
	pGridLayout->setContentsMargins(20, 10, 10, 10);
	allPageWidget->setLayout(pGridLayout);
	area->setWidget(allPageWidget);

	//全部暂时装填
	QStringList skinNameList;
	for (int i = 0; i < SKIN_NUM; i++) {
		skinNameList << SKIN_RES_NAME(i);
	}
	//获取当前皮肤
	QString currentSkin = getSkin();
	//全部展示，并写last和总列表
	for (int i = 0; i < SKIN_NUM; i++) {
		SkinItem *item = new SkinItem();
		item->setMinimumHeight(150);
		item->setPixmapName(skinNameList.at(i));
		if (currentSkin == skinNameList.at(i)) {
			m_pLastSkinItem = item;
		}
		m_skinItemList.append(item);
		//连接和加入
		connect(item, SIGNAL(clicked()), this, SLOT(slotItemClicked()));
		pGridLayout->addWidget(item, i / 3, i % 3);
	}
	//如果当前没有skin，默认第一个，选中last
	if (!m_pLastSkinItem) {
		m_pLastSkinItem = m_skinItemList.at(0);
	}
	m_pLastSkinItem->select(true);

	//全部放入comboBox，开始theme
	m_pThemeComboBox = new QComboBox();
	QDir dir(THEME_PATH);
	QStringList typeList;
	typeList << "*.cptheme" << "*.ini";
	QFileInfoList themeFiles = dir.entryInfoList(typeList, QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	foreach(QFileInfo info, themeFiles) {
		QString fileName = info.absoluteFilePath();
		QString themeName = Theme::getThemeName(fileName);
		m_pThemeComboBox->addItem(themeName, fileName);
	}
	//获取当前主题
	QString currentThemeName = Theme::getThemeName(Theme::getTheme());
	//将comboBox置位为当前的
	int index = m_pThemeComboBox->findText(currentThemeName);
	if (index != -1) {
		m_pThemeComboBox->setCurrentIndex(index);
	}
	//连接
	connect(m_pThemeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(slotThemeChanged(int)));

	//将comboBox放到HBoxLayout里
	m_pThemeComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	QHBoxLayout *themeLayout = new QHBoxLayout();
	themeLayout->setContentsMargins(10, 5, 10, 5);
	themeLayout->setSpacing(10);
	themeLayout->addWidget(new QLabel(tr("Theme:")));
	themeLayout->addWidget(m_pThemeComboBox);
	themeLayout->addStretch();

	//合并skin和theme两部分
	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(m_pTabWidget);
	layout->addLayout(themeLayout);

	//在dialog里添加
	pCentralWidget->setLayout(layout);
	setCentralWidget(pCentralWidget);
}

//set and get
void SkinDialog::setSkin(const QString &skinName) {
	QSettings settings("Canpool", "qtcanpool");
	settings.setValue("skin", skinName);
	update();
}

QString SkinDialog::getSkin() {
	QSettings settings("Canpool", "qtcanpool");
	QString skinName = settings.value("skin").toString();
	return skinName;
}

//点击皮肤时做出的反应
void SkinDialog::slotItemClicked() {
	SkinItem *item = qobject_cast<SkinItem *>(sender());

	//小绿钩改变，并改变last
	if (m_pLastSkinItem == item) {
		return;
	}
	if (m_pLastSkinItem) {
		m_pLastSkinItem->select(false);
	}
	m_pLastSkinItem = item;
	m_pLastSkinItem->select(true);

	//在set方法中就已经update过了
	QString skinName = item->pixmapName();
	setSkin(skinName);

	emit changeSkin();
}

//选择theme时做出的反应
void SkinDialog::slotThemeChanged(int index) {
	//在set方法中就已经load过了
	QString fileName = m_pThemeComboBox->itemData(index).toString();
	Theme::setTheme(fileName);

	emit changeTheme();
}