#pragma once

#ifndef DROPLABEL_H
#define DROPLABEL_H

#include "cwidgets.h"
#include "fancybutton.h"

class DropLabel :public QLabel {

	Q_OBJECT

public:

	DropLabel(QWidget *p = 0) : QLabel(p) {}

	void dragEnterEvent(QDragEnterEvent *e) {
		e->accept();
	}

	void dropEvent(QDropEvent *e) {

		QLabel *label = new QLabel(this);
		//l->setStyleSheet("border:2px solid red;");
		label->setGeometry(e->pos().x(), e->pos().y(), 60, 60);

		QPixmap pixmap = QPixmap::fromImage(e->mimeData()->imageData().value<QImage>());
		pixmap.scaled(label->size(), Qt::KeepAspectRatio);
		label->setScaledContents(true);
		
		label->setPixmap(pixmap);
		label->show();
	}
};

#endif // DROPLABEL_H