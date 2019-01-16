
#include "ToolDragStack.h"

#include "DropLabel.h"

ToolDragStack::ToolDragStack(QWidget *p) : MiniStack(p) {

	m_cLabel = new QLabel();
	putImage("c", m_cLabel);
	//m_cLabel->setStyleSheet("background-color:gray");
	m_cLabel->setCursor(QCursor(Qt::PointingHandCursor));
	m_cLabel->setFixedHeight(80);
	m_cLabel->setFixedWidth(80);

	m_matlabLabel = new QLabel();
	putImage("matlab", m_matlabLabel);
	//m_matlabLabel->setStyleSheet("background-color:gray");
	m_matlabLabel->setCursor(QCursor(Qt::PointingHandCursor));
	m_matlabLabel->setFixedHeight(80);
	m_matlabLabel->setFixedWidth(80);

	m_adamsLabel = new QLabel();
	putImage("adams", m_adamsLabel);
	//m_adamsLabel->setStyleSheet("background-color:gray");
	m_adamsLabel->setCursor(QCursor(Qt::PointingHandCursor));
	m_adamsLabel->setFixedHeight(80);
	m_adamsLabel->setFixedWidth(80);

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->addWidget(m_cLabel, 0, 0, 1, 1, Qt::AlignTop);
	layout->addWidget(m_matlabLabel, 1, 0, 1, 1, Qt::AlignTop);
	layout->addWidget(m_adamsLabel, 2, 0, 1, 1, Qt::AlignTop);
	QWidget *toolWidget = new QWidget();
	toolWidget->setLayout(layout);

	addTab(tr("tool"), toolWidget);

	setAcceptDrops(false);
}

void ToolDragStack::mousePressEvent(QMouseEvent *event) {
	if (event->button() & Qt::LeftButton) {

		QPoint point = event->localPos().toPoint();
		//TODO:magic number，默认的stack头高40
		point.setY(point.y() - 40);

		QString modelType;

		if (m_cLabel->geometry().contains(point)) {
			m_dragLabel = m_cLabel;
			modelType = CType;
		}
		else if (m_matlabLabel->geometry().contains(point)) {
			m_dragLabel = m_matlabLabel;
			modelType = MatlabType;
		}
		else if (m_adamsLabel->geometry().contains(point)) {
			m_dragLabel = m_adamsLabel;
			modelType = AdamsType;
		}
		else {
			return;
		}

		QDrag *dg = new QDrag(m_dragLabel);
		dg->setPixmap(*(m_dragLabel->pixmap()));

		QMimeData *md = new QMimeData;
		md->setImageData(m_dragLabel->pixmap()->toImage());
		md->setText(DRAP_COPY);
		md->setObjectName(modelType);
		dg->setMimeData(md);
		dg->exec();
	}
}

void ToolDragStack::putImage(QString path, QLabel *label) {
	QPixmap *pixmap = new QPixmap("./Icon/simutool/" + path);
	pixmap->scaled(label->size(), Qt::KeepAspectRatio);
	label->setScaledContents(true);
	label->setPixmap(*pixmap);
}