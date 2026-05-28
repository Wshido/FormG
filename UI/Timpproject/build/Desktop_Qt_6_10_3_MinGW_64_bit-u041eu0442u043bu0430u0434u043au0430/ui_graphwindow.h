/********************************************************************************
** Form generated from reading UI file 'graphwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHWINDOW_H
#define UI_GRAPHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GraphWindow
{
public:
    QCustomPlot *customPlot;
    QLabel *titleLabel;
    QLabel *labelSin;
    QSlider *sliderSin;
    QLabel *labelSqrt;
    QSlider *sliderSqrt;
    QLabel *labelFrac;
    QSlider *sliderFrac;

    void setupUi(QWidget *GraphWindow)
    {
        if (GraphWindow->objectName().isEmpty())
            GraphWindow->setObjectName("GraphWindow");
        GraphWindow->resize(1000, 800);
        customPlot = new QCustomPlot(GraphWindow);
        customPlot->setObjectName("customPlot");
        customPlot->setGeometry(QRect(250, 40, 700, 650));
        titleLabel = new QLabel(GraphWindow);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(10, 20, 231, 30));
        titleLabel->setStyleSheet(QString::fromUtf8("\n"
"font-size:20px;\n"
"font-weight:bold;\n"
"    "));
        labelSin = new QLabel(GraphWindow);
        labelSin->setObjectName("labelSin");
        labelSin->setGeometry(QRect(20, 90, 150, 20));
        sliderSin = new QSlider(GraphWindow);
        sliderSin->setObjectName("sliderSin");
        sliderSin->setGeometry(QRect(20, 120, 180, 22));
        sliderSin->setMinimum(-10);
        sliderSin->setMaximum(10);
        sliderSin->setOrientation(Qt::Orientation::Horizontal);
        labelSqrt = new QLabel(GraphWindow);
        labelSqrt->setObjectName("labelSqrt");
        labelSqrt->setGeometry(QRect(20, 180, 150, 20));
        sliderSqrt = new QSlider(GraphWindow);
        sliderSqrt->setObjectName("sliderSqrt");
        sliderSqrt->setGeometry(QRect(20, 210, 180, 22));
        sliderSqrt->setMinimum(-10);
        sliderSqrt->setMaximum(10);
        sliderSqrt->setOrientation(Qt::Orientation::Horizontal);
        labelFrac = new QLabel(GraphWindow);
        labelFrac->setObjectName("labelFrac");
        labelFrac->setGeometry(QRect(20, 270, 150, 20));
        sliderFrac = new QSlider(GraphWindow);
        sliderFrac->setObjectName("sliderFrac");
        sliderFrac->setGeometry(QRect(20, 300, 180, 22));
        sliderFrac->setMinimum(-10);
        sliderFrac->setMaximum(10);
        sliderFrac->setOrientation(Qt::Orientation::Horizontal);

        retranslateUi(GraphWindow);

        QMetaObject::connectSlotsByName(GraphWindow);
    } // setupUi

    void retranslateUi(QWidget *GraphWindow)
    {
        GraphWindow->setWindowTitle(QCoreApplication::translate("GraphWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\204\321\203\320\275\320\272\321\206\320\270\320\270", nullptr));
        titleLabel->setText(QCoreApplication::translate("GraphWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\274", nullptr));
        labelSin->setText(QCoreApplication::translate("GraphWindow", "sin(ax)", nullptr));
        labelSqrt->setText(QCoreApplication::translate("GraphWindow", "sqrt(x+b)", nullptr));
        labelFrac->setText(QCoreApplication::translate("GraphWindow", "1 / (x - c)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphWindow: public Ui_GraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHWINDOW_H
