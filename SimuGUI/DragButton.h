#pragma once

#ifndef DRAGBUTTON_H
#define DRAGBUTTON_H

#include "cwidgets.h"
#include "fancybutton.h"

class DragButton :public FancyButton {

	Q_OBJECT

public:

	DragButton(QWidget *p = 0) : FancyButton(p) {}

	void  mousePressEvent(QMouseEvent *e) {
		QDrag *dg = new QDrag(this);

		QMimeData *md = new QMimeData;

		md->setImageData(this->icon());

		dg->setMimeData(md);
		dg->exec(Qt::MoveAction);
	}
};

#endif // DRAGBUTTON_H