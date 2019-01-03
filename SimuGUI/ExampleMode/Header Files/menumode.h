
/*
* Mode Bar里的选项卡
* @date : 2018/12/12
* @author : jihang
*/

#ifndef MENUMODE_H
#define MENUMODE_H

#include "imode.h"

class MenuMode : public IMode {

	Q_OBJECT

public:
	explicit MenuMode(QWidget *parent = 0);

signals:

public slots:
};
#endif // MENUMODE_H