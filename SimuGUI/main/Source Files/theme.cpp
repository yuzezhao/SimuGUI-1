
/*
* 主题源文件
* @date : 2018/12/17
* @author : jihang
*/

#include "theme.h"

QColor Theme::g_color;
QColor Theme::g_oddColor;
QColor Theme::g_evenColor;
QColor Theme::g_checkColor;
QColor Theme::g_modifiedColor;

// fancyBar
QColor Theme::g_fancyBarHoverColor = FANCYBAR_HOVER_COLOR;
QColor Theme::g_fancyBarPressColor = FANCYBAR_PRESS_COLOR;
QColor Theme::g_fancyBarTextColor = FANCYBAR_TEXT_COLOR;
QColor Theme::g_fancyBarBackgroundColor = FANCYBAR_BACKGROUND_COLOR;
// FancyTab
QColor Theme::g_fancyTabHoverColor = FANCYTAB_HOVER_COLOR;
QColor Theme::g_fancyTabPressColor = FANCYTAB_PRESS_COLOR;
QColor Theme::g_fancyTabTextColor = FANCYTAB_TEXT_COLOR;
QColor Theme::g_fancyTabSelectedTextColor = FANCYTAB_SELECTED_TEXT_COLOR;
QColor Theme::g_fancyTabBackgroundColor = FANCYTAB_BACKGROUND_COLOR;
// TinyTab
QColor Theme::g_tinyTabHoverColor = TINYTAB_HOVER_COLOR;
QColor Theme::g_tinyTabPressColor = TINYTAB_PRESS_COLOR;
QColor Theme::g_tinyTabTextColor = TINYTAB_TEXT_COLOR;
QColor Theme::g_tinyTabSelectedTextColor = TINYTAB_SELECTED_TEXT_COLOR;
QColor Theme::g_tinyTabBackgroundColor = TINYTAB_BACKGROUND_COLOR;
QColor Theme::g_tinyTabNormalColor = TINYTAB_NORMAL_COLOR;
QColor Theme::g_tinyTabSlideColor = TINYTAB_SLIDE_COLOR;

//主题主要有五种颜色，有两种主题
void Theme::setClassicTheme() {
	g_color = CLASSIC_COLOR;
	g_evenColor = CLASSIC_EVEN_COLOR;
	g_oddColor = CLASSIC_ODD_COLOR;
	g_checkColor = CLASSIC_CHECK_COLOR;
	g_modifiedColor = CLASSIC_MODIFIED_COLOR;
}

void Theme::setFlatdarkTheme() {
	g_color = FLATDARK_COLOR;
	g_evenColor = FLATDARK_EVEN_COLOR;
	g_oddColor = FLATDARK_ODD_COLOR;
	g_checkColor = FLATDARK_CHECK_COLOR;
	g_modifiedColor = FLATDARK_MODIFIED_COLOR;
}

void Theme::setTheme(const QString &fileName) {
	QSettings settings("Canpool", "qtcanpool");
	settings.setValue("theme", fileName);
	loadTheme(fileName);
}

QString Theme::getTheme() {
	QSettings settings("Canpool", "qtcanpool");
	QString theme = settings.value("theme").toString();
	return theme;
}

QString Theme::getThemeName(const QString &fileName) {
	if (!QFile::exists(fileName)) {
		return QString("");
	}

	QSettings settings(fileName, QSettings::IniFormat);
	settings.beginGroup("Name");
	QString themeName = settings.value("ThemeName").toString();
	settings.endGroup();
	return themeName;
}

void Theme::loadTheme(const QString &fileName) {
	if (!QFile::exists(fileName)) {
		return;
	}

	QSettings settings(fileName, QSettings::IniFormat);
	settings.beginGroup("Colors");

	g_fancyBarHoverColor = argbToColor(settings.value("FancyBarHoverColor").toString());
	g_fancyBarPressColor = argbToColor(settings.value("FancyBarPressColor").toString());
	g_fancyBarTextColor = argbToColor(settings.value("FancyBarTextColor").toString());
	g_fancyBarBackgroundColor = argbToColor(settings.value("FancyBarBackgroundColor").toString());

	g_fancyTabHoverColor = argbToColor(settings.value("FancyTabHoverColor").toString());
	g_fancyTabPressColor = argbToColor(settings.value("FancyTabPressColor").toString());
	g_fancyTabTextColor = argbToColor(settings.value("FancyTabTextColor").toString());
	g_fancyTabSelectedTextColor = argbToColor(settings.value("FancyTabSelectedTextColor").toString());
	g_fancyTabBackgroundColor = argbToColor(settings.value("FancyTabBackgroundColor").toString());

	g_tinyTabHoverColor = argbToColor(settings.value("TinyTabHoverColor").toString());
	g_tinyTabPressColor = argbToColor(settings.value("TinyTabPressColor").toString());
	g_tinyTabTextColor = argbToColor(settings.value("TinyTabTextColor").toString());
	g_tinyTabSelectedTextColor = argbToColor(settings.value("TinyTabSelectedTextColor").toString());
	g_tinyTabBackgroundColor = argbToColor(settings.value("TinyTabBackgroundColor").toString());
	g_tinyTabNormalColor = argbToColor(settings.value("TinyTabNormalColor").toString());
	g_tinyTabSlideColor = argbToColor(settings.value("TinyTabSlideColor").toString());
	settings.endGroup();
}

QColor Theme::argbToColor(const QString &argb) {
	QColor color;
	bool ok = true;
	QRgb rgba = argb.toLongLong(&ok, 16);
	if (ok) {
		color = QColor::fromRgba(rgba);
	}
	else {
		color = QColor(0, 0, 0);
	}
	return color;
}