
/*
* 皮肤头文件
* @date : 2018/12/18
* @author : jihang
*/

#ifndef SKINDIALOG_H
#define SKINDIALOG_H

#include <QMap>

#include "tinytabwidget.h"
#include "skinitem.h"
#include "centralarea.h"
#include "fancydialog.h"

#include "cwidgets.h"
#include "theme.h"

class SkinDialog : public FancyDialog {

	Q_OBJECT

public:
	explicit SkinDialog(QWidget *parent = 0);

private:
	void createWindow();

	void setSkin(const QString &);
	QString getSkin();

signals:
	//皮肤发生改变
	void changeSkin();
	//主题发生改变
	void changeTheme();

public slots:

private slots:
	//点击皮肤时做出的反应
	void slotItemClicked();
	//选择theme时做出的反应
	void slotThemeChanged(int index);

private:
	//只有m_pLastSkinItem有必要是类变量，其他几个都可以是createWindow的局部变量
	//皮肤，点击换肤以后，立即存储当前为last，并加入list
	SkinItem *m_pLastSkinItem;
	QList<SkinItem*> m_skinItemList;

	//主题
	QComboBox *m_pThemeComboBox;
	QMap<QString, QString> m_themeMap;
};

#endif // SKINDIALOG_H