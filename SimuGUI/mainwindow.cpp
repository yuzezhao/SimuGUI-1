
/*
* 主布局
* @date : 2018/12/19
* @author : jihang
*/

#include "mainwindow.h"

MainWindow *MainWindow::m_instance = 0;

MainWindow::MainWindow(QWidget *parent) : FancyWindow(parent) {

	m_instance = this;

	m_styleAction = 0;
	m_styleActions.clear();

	m_modeStack = new FancyTabWidget(this);
	m_modeManager = new ModeManager(m_modeStack);

	m_statusBar = m_modeStack->statusBar();

	createWindow();
	createConnects();

	setAcceptDrops(true);

	setWindowTitle(QString::fromUtf8("Simulation Center"));
	setWindowIcon(QIcon("./Icon/main/workhub"));
	setMinimumSize(QSize(600, 400));
	setMouseTracking(true);

	updateTheme();
}

MainWindow::~MainWindow() {
	delete m_statusBar;
	delete m_modeStack;
	delete m_modeManager;
}

MainWindow *MainWindow::instance() {
	return m_instance;
}

void MainWindow::createWindow() {
	//快捷访问栏，位于左上角，包括新建、打开、存储、存储所有、后退、前进
	createQuickAccessBar();
	//菜单栏
	createMenuBar();
	//拓展栏，位于右上角，一共有两行，一行TitlePosition，一行MenuPosition
	createAdditionalControls();
	//状态栏，位于左下角，第一个可见，第二个不可见
	createStatusBar();
	//模式栏
	createModeBar();
	//中心区域
	createCentralWidget();
	//dock区域
	//createDockWidget();
	//TODO：禁止qt自带menu?
	createToolBar();
}

//创建一个快捷访问栏
void MainWindow::createQuickAccessBar() {
	if (QuickAccessBar* quickAccessBar = fancyBar()->quickAccessBar()) {
		QAction* action = quickAccessBar->actionCustomizeButton();
		action->setToolTip(tr("Customize Quick Access Bar"));

		QAction* smallButton;
		smallButton = quickAccessBar->addAction(QIcon("./Icon/tools/new"), tr("New"));
		smallButton->setShortcut(QKeySequence::New);
		smallButton->setToolTip(tr("New File or Project\nCtrl+N"));
		connect(smallButton, SIGNAL(triggered()), this, SLOT(slotNew()));
		quickAccessBar->setActionVisible(smallButton, false);

		smallButton = quickAccessBar->addAction(QIcon("./Icon/tools/open"), tr("Open"));
		smallButton->setShortcut(tr("Ctrl+O"));
		smallButton->setToolTip(tr("Open File or Project\nCtrl+O"));
		connect(smallButton, SIGNAL(triggered()), this, SLOT(slotOpen()));
		quickAccessBar->setActionVisible(smallButton, false);

		smallButton = quickAccessBar->addAction(QIcon("./Icon/tools/save"), tr("Save"));
		smallButton->setShortcut(tr("Ctrl+S"));
		smallButton->setToolTip(tr("Save the active document\nCtrl+S"));
		connect(smallButton, SIGNAL(triggered()), this, SLOT(slotSave()));
		quickAccessBar->setActionVisible(smallButton, false);

		smallButton = quickAccessBar->addAction(QIcon("./Icon/tools/save_all"), tr("Save All"));
		smallButton->setShortcut(tr("Ctrl+Shift+S"));
		smallButton->setToolTip(tr("Save all active documents\nCtrl+Shift+S"));
		connect(smallButton, SIGNAL(triggered()), this, SLOT(slotSaveAll()));
		quickAccessBar->setActionVisible(smallButton, false);

		smallButton = quickAccessBar->addAction(QIcon("./Icon/tools/undo"), tr("&Undo"));
		smallButton->setShortcut(QKeySequence::Undo);
		smallButton->setEnabled(false);

		smallButton = quickAccessBar->addAction(QIcon("./Icon/tools/redo"), tr("&Redo"));
		smallButton->setShortcut(QKeySequence::Redo);
		smallButton->setEnabled(false);

		fancyBar()->showQuickAccess(false);

		fancyBar()->setBackgroundColor(QColor(0, 100, 200, 100));
	}
}

//创建一个菜单栏
//TODO：在笔记本上会回收，并且使用merge style的时候显示效果不佳
void MainWindow::createMenuBar() {
	if (QMenuBar* menuBar = fancyBar()->menuBar()) {

		QAction *action;
		QMenu* menu;
		action = new QAction(tr("action1"), this);
		menu = menuBar->addMenu(tr("&文件"));
		menu->addAction(action);

		action = new QAction(tr("action1"), this);
		menu = menuBar->addMenu(tr("&编辑"));
		menu->addAction(action);

		action = new QAction(tr("action1"), this);
		menu = menuBar->addMenu(tr("&选项"));
		menu->addAction(action);

		action = new QAction(tr("action1"), this);
		menu = menuBar->addMenu(tr("&设置"));
		menu->addAction(action);

		action = new QAction(tr("action1"), this);
		menu = menuBar->addMenu(tr("&帮助"));
		menu->addAction(action);

		fancyBar()->showMenuBar(true);
	}

	QTextBrowser *text = new QTextBrowser(this);
	QFont ft;
	ft.setPointSize(34);
	text->setFont(ft);
	text->append(tr("还犹豫什么仿就完事了I"));
	fancyBar()->setApplicationWidget(tr("Application"), text);
}

//创建拓展栏
void MainWindow::createAdditionalControls() {
	QAction *menuAction = new QAction(QIcon("./Icon/tools/style"), tr("Style"), this);
	fancyBar()->addAdditionalControl(menuAction, FancyBar::TitlePosition);

	QAction *skinAction = new QAction(QIcon("./Icon/tools/skin"), tr("Skin"), this);
	connect(skinAction, SIGNAL(triggered(bool)), this, SLOT(slotSkin()));
	fancyBar()->addAdditionalControl(skinAction, FancyBar::TitlePosition);

	QAction *action = new QAction(QIcon("./Icon/tools/option"), tr("Option"), this);
	fancyBar()->addAdditionalControl(action, FancyBar::MenuPosition);

	//Style展开的menu
	QMenu *styleMenu = new QMenu(this);
	//这一组action的connect信息集合
	QActionGroup *actionGroup = new QActionGroup(this);

	QAction *styleAction = new QAction(tr("Window Style"));
	styleAction->setCheckable(true);
	styleMenu->addAction(styleAction);
	actionGroup->addAction(styleAction);
	m_styleActions.append(styleAction);

	styleAction = new QAction(tr("Classic Style"));
	styleAction->setCheckable(true);
	styleMenu->addAction(styleAction);
	actionGroup->addAction(styleAction);
	m_styleActions.append(styleAction);

	styleAction = new QAction(tr("Merged Style"));
	styleAction->setCheckable(true);
	styleMenu->addAction(styleAction);
	actionGroup->addAction(styleAction);
	m_styleActions.append(styleAction);

	connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotSetStyle(QAction*)));
	m_styleActions.at(0)->setChecked(true);

	menuAction->setMenu(styleMenu);
}

//创建状态栏
void MainWindow::createStatusBar() {
	FancyNavBar *navBar = new FancyNavBar();
	navBar->setSideExpand(true);
	//设置点击之后的状态区在哪
	QSplitter *splitter = m_modeStack->addCornerWidget(navBar->panel(), FancyTabWidget::Bottom);
	navBar->setSplitter(splitter);

	QTextBrowser *tb1 = new QTextBrowser(this);
	QTextBrowser *tb2 = new QTextBrowser(this);
	navBar->add(tr("状态显示区"), tb1);
	navBar->add(tr("隐藏着的I"), tb2, new QLineEdit());

	m_statusBar->addWidget(navBar);
}

//创建模式栏
void MainWindow::createModeBar() {
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(0, 0, 0, 20));

	FancyTabBar *modeBar = m_modeStack->tabBar();
	modeBar->setPalette(palette);
	modeBar->setAutoFillBackground(true);

	m_pCustomMode = new CustomMode();
	m_pPaintMode = new PaintMode();
	m_pMenuMode = new MenuMode();

	m_modeManager->objectAdded(m_pCustomMode);
	m_modeManager->objectAdded(m_pPaintMode);
	m_modeManager->objectAdded(m_pMenuMode);

	m_modeManager->setCurrentMode(m_pCustomMode);

	//QAction *action = new QAction(QIcon("./Icon/tools/start"), tr("Start"), this);
	//action->setShortcut(tr("Ctrl+R"));
	//action->setToolTip(tr("Start <i>Ctrl+R</i>"));
	//modeBar->addAction(action);

	modeBar->setTabIconSize(QSize(24, 24));
	modeBar->setTextColor(QColor(255, 255, 255));
	modeBar->setSelectedTextColor(QColor(255, 255, 255));
	modeBar->setHoverColor(QColor(255, 255, 255, 50));
	modeBar->setFixedWidth(80);
}

//创建中心区域，即m_modeStack
void MainWindow::createCentralWidget() {
	setCentralWidget(m_modeStack);
	//为中心区域添加top、left、bottom、right
	//QTextBrowser *tb1 = new QTextBrowser(this);
	//QTextBrowser *tb2 = new QTextBrowser(this);
	//QTextBrowser *tb3 = new QTextBrowser(this);
	//QTextBrowser *tb4 = new QTextBrowser(this);
	//m_modeStack->addCornerWidget(tb1, FancyTabWidget::Left);
	//m_modeStack->addCornerWidget(tb2, FancyTabWidget::Top);
	//m_modeStack->addCornerWidget(tb3, FancyTabWidget::Right);
	//m_modeStack->addCornerWidget(tb4, FancyTabWidget::Bottom);
}

//创建dock，在area周围的可以自由拖动的区域
void MainWindow::createDockWidget() {
	QTreeWidget *m_pTreeWidget = new QTreeWidget(this);
	m_pTreeWidget->setHeaderHidden(true);
	m_pTreeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTreeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
	//    connect(m_pTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
	//            this, SLOT(SlotItemActivated(QTreeWidgetItem*,int)));

	QDockWidget *pDockWidgetTest = new QDockWidget(tr("Test View"), this);
	pDockWidgetTest->setAllowedAreas(Qt::AllDockWidgetAreas);
	pDockWidgetTest->setWidget(m_pTreeWidget);
	addDockWidget(Qt::LeftDockWidgetArea, pDockWidgetTest);

	QTableView *m_pTableView = new QTableView(this);
	QDockWidget *pDockWidgetScd = new QDockWidget(tr("SCD View"), this);
	pDockWidgetScd->setAllowedAreas(Qt::AllDockWidgetAreas);
	pDockWidgetScd->setWidget(m_pTableView);
	//pDockWidgetScd->hide();
	addDockWidget(Qt::RightDockWidgetArea, pDockWidgetScd);

	QTextEdit* m_pTextEdit = new QTextEdit(this);
	QDockWidget *pDockWidgetOutput = new QDockWidget(tr("Output"), this);
	pDockWidgetOutput->setAllowedAreas(Qt::AllDockWidgetAreas);
	pDockWidgetOutput->setWidget(m_pTextEdit);
	addDockWidget(Qt::RightDockWidgetArea, pDockWidgetOutput);
}

void MainWindow::createToolBar() {
	setContextMenuPolicy(Qt::NoContextMenu);
}

void MainWindow::createConnects() {
	//调整整体大小的信号槽
	connect(this, SIGNAL(resizable(bool)), this, SLOT(slotResizable(bool)));
}

//TODO:如果未来找到了Canpool配置文件，找找有没有pos和size
void MainWindow::readSettings() {
	QSettings settings("Canpool", "qtproject");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	move(pos);
	resize(size);
}
void MainWindow::writeSettings() {
	QSettings settings("Canpool", "qtproject");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

//----------所有的槽----------
//更新主题槽
void MainWindow::updateTheme() {
	FancyTabBar *modeBar = m_modeStack->tabBar();
	modeBar->setTextColor(Theme::g_fancyTabTextColor);
	modeBar->setSelectedTextColor(Theme::g_fancyTabSelectedTextColor);
	modeBar->setHoverColor(Theme::g_fancyTabHoverColor);
	modeBar->setPressColor(Theme::g_fancyTabPressColor);
	modeBar->setBackgroundColor(Theme::g_fancyTabBackgroundColor);

	fancyBar()->setHoverColor(Theme::g_fancyBarHoverColor);
	fancyBar()->setPressColor(Theme::g_fancyBarPressColor);
	fancyBar()->setTextColor(Theme::g_fancyBarTextColor);
	fancyBar()->setBackgroundColor(Theme::g_fancyBarBackgroundColor);
}

//一些示例
void MainWindow::slotNew() {

	//分页示例
	QDialog dlg;
	QHBoxLayout layout;
	PageSorter sorter;
	sorter.setMaxPage(5);
	layout.addWidget(&sorter);
	dlg.setLayout(&layout);
	dlg.exec();

	//对话框右上角有个按钮示例
	FancyDialog dialog;
	dialog.setTitleBarHeight(30);
	dialog.addAdditionalControl(new QAction(QIcon("./Icon/tools/help"), tr("What is this"), this));
	dialog.exec();

	//简单dialog示例
	QTextBrowser *tb = new QTextBrowser(this);
	FancyDialog dialog2;
	dialog2.setCentralWidget(tb);
	dialog2.exec();

	//滑动浏览器示例
	QDialog dialog3;
	FancyBanner banner;
	for (int i = 0; i < 10; i++) {
		banner.addPage(QPixmap(QString("./Icon/skin/%1").arg(i)));
	}
	QHBoxLayout layout2;
	layout2.setMargin(0);
	layout2.setSpacing(0);
	layout2.addWidget(&banner);
	dialog3.setLayout(&layout2);
	dialog3.resize(300, 80);
	dialog3.exec();
}

//变换皮肤和主题窗口，并添加信号槽
void MainWindow::slotSkin() {
	SkinDialog dlg;
	connect(&dlg, SIGNAL(changeSkin()), this, SLOT(slotChangeSkin()));
	connect(&dlg, SIGNAL(changeTheme()), this, SLOT(updateTheme()));
	dlg.exec();
}

void MainWindow::slotResizable(bool resizable) {
	m_statusBar->setSizeGripEnabled(resizable);
}

void MainWindow::slotChangeSkin() {
	update();
}

//三种style切换的槽，m_styleAction为存储的被顶替的，m_styleActions存的所有
void MainWindow::slotSetStyle(QAction *action) {
	if (m_styleAction == action) {
		return;
	}
	m_styleAction = action;
	int index = m_styleActions.indexOf(action);
	fancyBar()->setFancyStyle((FancyBar::FancyStyle)index);
	//设置一下背景圈的颜色
	if (index == FancyBar::ClassicStyle || index == FancyBar::MergedStyle) {
		fancyBar()->setApplicationButtonBkColor(QColor(255, 255, 255, 0));
	}
	else {
		fancyBar()->setApplicationButtonBkColor(QColor(240, 130, 0));
	}
}