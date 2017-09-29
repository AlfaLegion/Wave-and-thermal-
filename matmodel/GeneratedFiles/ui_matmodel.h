/********************************************************************************
** Form generated from reading UI file 'matmodel.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATMODEL_H
#define UI_MATMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_matmodelClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *matmodelClass)
    {
        if (matmodelClass->objectName().isEmpty())
            matmodelClass->setObjectName(QStringLiteral("matmodelClass"));
        matmodelClass->resize(600, 400);
        matmodelClass->setCursor(QCursor(Qt::CrossCursor));
        centralWidget = new QWidget(matmodelClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        matmodelClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(matmodelClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        matmodelClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(matmodelClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        matmodelClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(matmodelClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        matmodelClass->setStatusBar(statusBar);

        retranslateUi(matmodelClass);

        QMetaObject::connectSlotsByName(matmodelClass);
    } // setupUi

    void retranslateUi(QMainWindow *matmodelClass)
    {
        matmodelClass->setWindowTitle(QApplication::translate("matmodelClass", "matmodel", 0));
    } // retranslateUi

};

namespace Ui {
    class matmodelClass: public Ui_matmodelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATMODEL_H
