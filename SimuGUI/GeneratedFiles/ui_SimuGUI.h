/********************************************************************************
** Form generated from reading UI file 'SimuGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMUGUI_H
#define UI_SIMUGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimuGUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimuGUIClass)
    {
        if (SimuGUIClass->objectName().isEmpty())
            SimuGUIClass->setObjectName(QString::fromUtf8("SimuGUIClass"));
        SimuGUIClass->resize(600, 400);
        menuBar = new QMenuBar(SimuGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SimuGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimuGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimuGUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SimuGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SimuGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SimuGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimuGUIClass->setStatusBar(statusBar);

        retranslateUi(SimuGUIClass);

        QMetaObject::connectSlotsByName(SimuGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimuGUIClass)
    {
        SimuGUIClass->setWindowTitle(QApplication::translate("SimuGUIClass", "SimuGUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimuGUIClass: public Ui_SimuGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMUGUI_H
