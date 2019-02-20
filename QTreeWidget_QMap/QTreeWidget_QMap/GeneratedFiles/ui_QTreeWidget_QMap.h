/********************************************************************************
** Form generated from reading UI file 'QTreeWidget_QMap.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTREEWIDGET_QMAP_H
#define UI_QTREEWIDGET_QMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTreeWidget_QMapClass
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTreeWidget_QMapClass)
    {
        if (QTreeWidget_QMapClass->objectName().isEmpty())
            QTreeWidget_QMapClass->setObjectName(QStringLiteral("QTreeWidget_QMapClass"));
        QTreeWidget_QMapClass->resize(600, 400);
        centralWidget = new QWidget(QTreeWidget_QMapClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        treeWidget = new QTreeWidget(centralWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(95, 21, 271, 261));
        QTreeWidget_QMapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTreeWidget_QMapClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        QTreeWidget_QMapClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTreeWidget_QMapClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTreeWidget_QMapClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTreeWidget_QMapClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTreeWidget_QMapClass->setStatusBar(statusBar);

        retranslateUi(QTreeWidget_QMapClass);

        QMetaObject::connectSlotsByName(QTreeWidget_QMapClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTreeWidget_QMapClass)
    {
        QTreeWidget_QMapClass->setWindowTitle(QApplication::translate("QTreeWidget_QMapClass", "QTreeWidget_QMap", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("QTreeWidget_QMapClass", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTreeWidget_QMapClass: public Ui_QTreeWidget_QMapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTREEWIDGET_QMAP_H
