
/*
* Mode Bar里的选项卡
* @date : 2018/12/12
* @author : jihang
*/

#include "menumode.h"

MenuMode::MenuMode(QWidget *parent) : IMode(parent) {

	//最基本的三个属性
	setObjectName(QLatin1String("MenuMode"));
	setDisplayName(tr("Menu"));
	setIcon(QIcon("./Icon/mode/menu"));

	//加上menu的话就默认加到menu区，能够设置按键和停留显示
	QMenu *menu = new QMenu();
	menu->addAction(QIcon("./Icon/debug/debug"), tr("Action1"));
	menu->addAction(QIcon("./Icon/debug/debug"), tr("Action2"));
	menu->addAction(QIcon("./Icon/debug/debug"), tr("Action3"));
	menu->addAction(QIcon("./Icon/debug/debug"), tr("Action4"));
	menu->setToolTip(tr("menu mode"));

	setMenu(menu);
}