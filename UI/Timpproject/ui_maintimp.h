/********************************************************************************
** Form generated from reading UI file 'maintimp.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTIMP_H
#define UI_MAINTIMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainTimp
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainTimp)
    {
        if (MainTimp->objectName().isEmpty())
            MainTimp->setObjectName("MainTimp");
        MainTimp->resize(800, 600);
        centralwidget = new QWidget(MainTimp);
        centralwidget->setObjectName("centralwidget");
        MainTimp->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainTimp);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainTimp->setMenuBar(menubar);
        statusbar = new QStatusBar(MainTimp);
        statusbar->setObjectName("statusbar");
        MainTimp->setStatusBar(statusbar);

        retranslateUi(MainTimp);

        QMetaObject::connectSlotsByName(MainTimp);
    } // setupUi

    void retranslateUi(QMainWindow *MainTimp)
    {
        MainTimp->setWindowTitle(QCoreApplication::translate("MainTimp", "MainTimp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainTimp: public Ui_MainTimp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTIMP_H
