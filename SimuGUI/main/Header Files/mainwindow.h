
/*
* 主布局
* @date : 2018/12/19
* @author : jihang
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextBrowser>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTreeWidget>
#include <QDockWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QSettings>
#include <QAction>

#include "fancywindow.h"
#include "fancytabwidget.h"
#include "fancytabbar.h"
#include "modemanager.h"
#include "fancybar.h"
#include "quickaccessbar.h"
#include "fancydialog.h"
#include "fancynavbar.h"
#include "pagesorter.h"
#include "fancybanner.h"

#include "cwidgets.h"
#include "skindialog.h"
#include "theme.h"

#include "custommode.h"
#include "menumode.h"
#include "paintmode.h"
#include "HLARunControl.h"
#include "FMISimulator.h"

class MainWindow : public FancyWindow {

	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	static MainWindow* instance();

private:
	//第一部分
	void createWindow();
	void createQuickAccessBar();
	void createMenuBar();
	void createAdditionalControls();
	void createStatusBar();
	void createModeBar();
	void createCentralWidget();
	void createDockWidget();
	void createToolBar();
	//第二部分
	void createConnects();
	//第三部分
	void readSettings();
	void writeSettings();

public slots:
	void updateTheme();

private slots:
	void slotNew();
	void slotSkin();
	void slotResizable(bool resizable);
	void slotChangeSkin();
	void slotSetStyle(QAction *action);

private:
	//自己
	static MainWindow *m_instance;

	//管理mode，需要管理其中的stack初始化
	ModeManager *m_modeManager;

	//中心区域的对象stack
	FancyTabWidget *m_modeStack;

	//状态栏，在slotResizable里使用
	QStatusBar *m_statusBar;

	//存储的所有style和上一个style
	QList<QAction *> m_styleActions;
	QAction *m_styleAction;

	//三个mode
	CustomMode *m_pCustomMode;
	PaintMode *m_pPaintMode;
	MenuMode *m_pMenuMode;
	HLARunControl *m_pHLARunControl;
	FMISimulator *m_pFMISimulator;
};

#endif // MAINWINDOW_H