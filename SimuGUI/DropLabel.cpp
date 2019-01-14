
#include "DropLabel.h"

DropLabel::DropLabel(QWidget *p) : QLabel(p) {

	CNameSet.insert(1);
	MatlabNameSet.insert(1);
	AdamsNameSet.insert(1);
}

void DropLabel::dragEnterEvent(QDragEnterEvent *e) {
	e->accept();
}

void DropLabel::dropEvent(QDropEvent *e) {

	modelInfo model;
	model.type = e->mimeData()->objectName();
	model.name = getName(model.type);

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

	emit addModelRequest(model.name, model.type);
}

QString DropLabel::getName(QString type) {
	if (type == CType) {
		int next = *CNameSet.begin();
		QString name = "CModel_" + QString::number(next);
		CNameSet.remove(next);
		if (CNameSet.isEmpty()) {
			CNameSet.insert(next + 1);
		}
		return name;
	}
	else if (type == MatlabType) {
		int next = *MatlabNameSet.begin();
		QString name = "MatlabModel_" + QString::number(next);
		MatlabNameSet.remove(next);
		if (MatlabNameSet.isEmpty()) {
			MatlabNameSet.insert(next + 1);
		}
		return name;
	}
	else if (type == AdamsType) {
		int next = *AdamsNameSet.begin();
		QString name = "AdamsModel_" + QString::number(next);
		AdamsNameSet.remove(next);
		if (AdamsNameSet.isEmpty()) {
			AdamsNameSet.insert(next + 1);
		}
		return name;
	}
	else {
		return NULL;
	}
}