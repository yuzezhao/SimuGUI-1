
#include "DropLabel.h"

DropLabel::DropLabel(QWidget *p) : QLabel(p) {
	//±àºÅ´Ó1¿ªÊ¼
	CNameSet.insert(1);
	MatlabNameSet.insert(1);
	AdamsNameSet.insert(1);
}

void DropLabel::dragEnterEvent(QDragEnterEvent *e) {
	e->accept();
}

void DropLabel::dropEvent(QDropEvent *e) {

	QString moveType = e->mimeData()->text();

	if (DRAP_COPY == moveType) {
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
		e->setDropAction(Qt::MoveAction);
		e->accept();
		emit addModelRequest(model.name, model.type);
	}
	else if (DRAG_MOVE == moveType) {
		QLabel *label = e->mimeData()->property("label").value<QLabel*>();
		QPoint point = e->pos();
		QRect rect(e->pos(), label->size());
		label->setGeometry(rect);
	}
}

void DropLabel::mousePressEvent(QMouseEvent *event) {
	
	if (event->button() & Qt::LeftButton) {
		
		QPoint point = event->localPos().toPoint();
		
		QList<modelInfo>::iterator itor;
		
		for (itor = modelList.begin(); itor != modelList.end(); itor++) {
			if (itor->label->geometry().contains(point)) {
				//emit sendMes(itor->name);
				break;
			}
		}
		if (itor != modelList.end()) {
			QLabel *label = itor->label;
			QDrag *dg = new QDrag(label);
			QMimeData *md = new QMimeData;
			md->setProperty("label", QVariant::fromValue(label));
			md->setText(DRAG_MOVE);
			dg->setMimeData(md);
			dg->exec();
		}
	}
}

void DropLabel::dragMoveEvent(QDragMoveEvent *event) {

	QString moveType = event->mimeData()->text();

	if (DRAG_MOVE == moveType) {
		QLabel *label = event->mimeData()->property("label").value<QLabel*>();
		QPoint point = event->pos();
		QRect rect(event->pos(), label->size());
		label->setGeometry(rect);
	}
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