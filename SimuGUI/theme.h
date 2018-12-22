
/*
* 主题头文件
* @date : 2018/12/17
* @author : jihang
*/

#ifndef THEME_H
#define THEME_H

#include <QColor>
#include <QSettings>
#include <QFile>

#define TABLE_USE_ALTERNATE_COLOR   1

// theme
// classic
#define CLASSIC_ODD_COLOR           QColor(233,231,227)
#define CLASSIC_EVEN_COLOR          QColor(255,255,255)
#define CLASSIC_COLOR               QColor(0,0,0)
#define CLASSIC_CHECK_COLOR         QColor(128,0,255)
#define CLASSIC_MODIFIED_COLOR      QColor(0,0,0)

// flatdark
#define FLATDARK_ODD_COLOR          QColor(46,47,48)
#define FLATDARK_EVEN_COLOR         QColor(64,66,68)
#define FLATDARK_COLOR              QColor(200,200,200)
#define FLATDARK_CHECK_COLOR        QColor(255,106,173)
#define FLATDARK_MODIFIED_COLOR     QColor(0,200,0)

// fancyBar
#define FANCYBAR_HOVER_COLOR        QColor(255,255,255,50)
#define FANCYBAR_PRESS_COLOR        QColor(0, 0, 0, 50)
#define FANCYBAR_TEXT_COLOR         QColor(255,255,255)
#define FANCYBAR_BACKGROUND_COLOR   QColor(0, 100, 200, 100)
// fancyTab
#define FANCYTAB_HOVER_COLOR          QColor(180,180,180)
#define FANCYTAB_PRESS_COLOR          QColor(0, 0, 0, 100)
#define FANCYTAB_TEXT_COLOR           QColor(255,255,255)
#define FANCYTAB_SELECTED_TEXT_COLOR  QColor(255,255,255)
#define FANCYTAB_BACKGROUND_COLOR     QColor(0,0,0,20)
// tinyTab
#define TINYTAB_HOVER_COLOR           QColor(255, 255, 255, 50)
#define TINYTAB_PRESS_COLOR           QColor(0, 0, 0, 100)
#define TINYTAB_TEXT_COLOR            QColor(255,255,255)
#define TINYTAB_SELECTED_TEXT_COLOR   QColor(255,255,255)
#define TINYTAB_BACKGROUND_COLOR      QColor(0, 100, 200, 100)
#define TINYTAB_NORMAL_COLOR          QColor(0, 100, 200, 100)
#define TINYTAB_SLIDE_COLOR           QColor(250, 0, 0)

class Theme {

public:
	//TODO：不知道怎么用的
	static QColor g_color;
	static QColor g_oddColor;   // ji
	static QColor g_evenColor;  // ou
	static QColor g_checkColor;
	static QColor g_modifiedColor;

	static void setClassicTheme();
	static void setFlatdarkTheme();

	//设置theme
	static void setTheme(const QString &fileName);
	//获取theme
	static QString getTheme();
	//获取theme的名字
	static QString getThemeName(const QString &fileName);
	//载入theme
	static void loadTheme(const QString &fileName);

	//theme的适用范围
	// fancyBar
	static QColor g_fancyBarHoverColor;
	static QColor g_fancyBarPressColor;
	static QColor g_fancyBarTextColor;
	static QColor g_fancyBarBackgroundColor;
	// fancyTab
	static QColor g_fancyTabHoverColor;
	static QColor g_fancyTabPressColor;
	static QColor g_fancyTabTextColor;
	static QColor g_fancyTabSelectedTextColor;
	static QColor g_fancyTabBackgroundColor;
	// TinyTab
	static QColor g_tinyTabHoverColor;
	static QColor g_tinyTabPressColor;
	static QColor g_tinyTabTextColor;
	static QColor g_tinyTabSelectedTextColor;
	static QColor g_tinyTabBackgroundColor;
	static QColor g_tinyTabNormalColor;
	static QColor g_tinyTabSlideColor;

private:
	static QColor argbToColor(const QString &);
};

#endif // THEME_H