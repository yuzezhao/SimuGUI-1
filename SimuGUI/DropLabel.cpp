
#include "DropLabel.h"

void DropLabel::dragEnterEvent(QDragEnterEvent *e) {
	e->accept();
}

void DropLabel::dropEvent(QDropEvent *e) {

	//nameÅÐ¶Ï

	modelInfo model;
	model.name = e->mimeData()->objectName();
	model.type = e->mimeData()->text();

	QLabel *label = new QLabel(this);
	label->setStyleSheet("border:1px solid gray;");
	label->setGeometry(e->pos().x(), e->pos().y(), 60, 60);

	QPixmap pixmap = QPixmap::fromImage(e->mimeData()->imageData().value<QImage>());
	pixmap.scaled(label->size(), Qt::KeepAspectRatio);
	label->setScaledContents(true);
	label->setPixmap(pixmap);
	label->show();

	model.label = label;
	modelList.append(model);

	//emit addModelRequest(model.name);
}