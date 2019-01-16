
#include "DropLabel.h"

DropLabel::DropLabel(QWidget *p) : QLabel(p) {
	//编号从1开始
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

		modelInfo model = getModel(e->mimeData()->objectName());

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

void DropLabel::deleteModel(QString name) {
	QList<modelInfo>::iterator itor;
	for (itor = modelList.begin(); itor != modelList.end(); itor++) {
		if (itor->name == name) {
			QLabel *label = itor->label;
			delete label;
			//插入可用数字
			if (itor->type == CType) {
				CNameSet.insert(itor->count);
				
			}
			else if (itor->type == MatlabType) {
				MatlabNameSet.insert(itor->count);
			}
			else if (itor->type == AdamsType) {
				AdamsNameSet.insert(itor->count);
			}
			//列表删除项
			modelList.erase(itor++);
			return;
		}
	}
	emit sendMes("error");
}

modelInfo DropLabel::getModel(QString type) {
	modelInfo model;
	model.type = type;
	QString name = "error";
	int next = 7777;
	if (type == CType) {
		next = *CNameSet.begin();
		name = "CModel_" + QString::number(next);
		CNameSet.erase(next);
		if (CNameSet.empty()) {
			CNameSet.insert(next + 1);
		}
	}
	else if (type == MatlabType) {
		next = *MatlabNameSet.begin();
		name = "MatlabModel_" + QString::number(next);
		MatlabNameSet.erase(next);
		if (MatlabNameSet.empty()) {
			MatlabNameSet.insert(next + 1);
		}
	}
	else if (type == AdamsType) {
		next = *AdamsNameSet.begin();
		name = "AdamsModel_" + QString::number(next);
		AdamsNameSet.erase(next);
		if (AdamsNameSet.empty()) {
			AdamsNameSet.insert(next + 1);
		}
	}
	model.count = next;
	model.name = name;
	return model;
}