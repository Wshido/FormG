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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GraphWindow
{
public:
    QHBoxLayout *mainLayout;
    QFrame *infoFrame;
    QVBoxLayout *infoLayout;
    QSpacerItem *topSpacer;
    QLabel *titleLabel;
    QLabel *paramGroup;
    QSpacerItem *spacer1;
    QHBoxLayout *sinLayout;
    QLabel *labelSin;
    QLabel *labelSinValue;
    QSlider *sliderSin;
    QSpacerItem *spacer2;
    QHBoxLayout *sqrtLayout;
    QLabel *labelSqrt;
    QLabel *labelSqrtValue;
    QSlider *sliderSqrt;
    QSpacerItem *spacer3;
    QHBoxLayout *fracLayout;
    QLabel *labelFrac;
    QLabel *labelFracValue;
    QSlider *sliderFrac;
    QSpacerItem *bottomSpacer;
    QFrame *graphFrame;
    QVBoxLayout *graphLayout;
    QCustomPlot *customPlot;

    void setupUi(QWidget *GraphWindow)
    {
        if (GraphWindow->objectName().isEmpty())
            GraphWindow->setObjectName("GraphWindow");
        GraphWindow->resize(1050, 800);
        GraphWindow->setStyleSheet(QString::fromUtf8("\n"
"QWidget { background-color: #f5f7fa; font-family: 'Segoe UI', Arial; }\n"
"QLabel { color: #2c3e50; background: transparent; }\n"
"   "));
        mainLayout = new QHBoxLayout(GraphWindow);
        mainLayout->setObjectName("mainLayout");
        infoFrame = new QFrame(GraphWindow);
        infoFrame->setObjectName("infoFrame");
        infoFrame->setMinimumSize(QSize(250, 0));
        infoFrame->setMaximumSize(QSize(250, 16777215));
        infoFrame->setStyleSheet(QString::fromUtf8("\n"
"QFrame#infoFrame {\n"
"    background-color: white;\n"
"    border-radius: 12px;\n"
"    border: 1px solid #dfe6e9;\n"
"}\n"
"QLabel#titleLabel { font-size: 22px; font-weight: bold; color: #2c3e50; }\n"
"QLabel#paramGroup { font-size: 14px; font-weight: bold; color: #7f8c8d; }\n"
"QSlider::groove:horizontal {\n"
"    height: 6px;\n"
"    background: #dcdde1;\n"
"    border-radius: 3px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background: #3498db;\n"
"    width: 18px;\n"
"    height: 18px;\n"
"    margin: -6px 0;\n"
"    border-radius: 9px;\n"
"}\n"
"QSlider::handle:horizontal:hover { background: #2980b9; }\n"
"QSlider::handle:horizontal:pressed { background: #1a5276; }\n"
"      "));
        infoLayout = new QVBoxLayout(infoFrame);
        infoLayout->setObjectName("infoLayout");
        topSpacer = new QSpacerItem(0, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        infoLayout->addItem(topSpacer);

        titleLabel = new QLabel(infoFrame);
        titleLabel->setObjectName("titleLabel");

        infoLayout->addWidget(titleLabel);

        paramGroup = new QLabel(infoFrame);
        paramGroup->setObjectName("paramGroup");

        infoLayout->addWidget(paramGroup);

        spacer1 = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        infoLayout->addItem(spacer1);

        sinLayout = new QHBoxLayout();
        sinLayout->setObjectName("sinLayout");
        labelSin = new QLabel(infoFrame);
        labelSin->setObjectName("labelSin");

        sinLayout->addWidget(labelSin);

        labelSinValue = new QLabel(infoFrame);
        labelSinValue->setObjectName("labelSinValue");
        labelSinValue->setStyleSheet(QString::fromUtf8("color: #e74c3c; font-weight: bold;"));
        labelSinValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        sinLayout->addWidget(labelSinValue);


        infoLayout->addLayout(sinLayout);

        sliderSin = new QSlider(infoFrame);
        sliderSin->setObjectName("sliderSin");
        sliderSin->setMinimum(-10);
        sliderSin->setMaximum(10);
        sliderSin->setOrientation(Qt::Orientation::Horizontal);

        infoLayout->addWidget(sliderSin);

        spacer2 = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        infoLayout->addItem(spacer2);

        sqrtLayout = new QHBoxLayout();
        sqrtLayout->setObjectName("sqrtLayout");
        labelSqrt = new QLabel(infoFrame);
        labelSqrt->setObjectName("labelSqrt");

        sqrtLayout->addWidget(labelSqrt);

        labelSqrtValue = new QLabel(infoFrame);
        labelSqrtValue->setObjectName("labelSqrtValue");
        labelSqrtValue->setStyleSheet(QString::fromUtf8("color: #27ae60; font-weight: bold;"));
        labelSqrtValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        sqrtLayout->addWidget(labelSqrtValue);


        infoLayout->addLayout(sqrtLayout);

        sliderSqrt = new QSlider(infoFrame);
        sliderSqrt->setObjectName("sliderSqrt");
        sliderSqrt->setMinimum(-10);
        sliderSqrt->setMaximum(10);
        sliderSqrt->setOrientation(Qt::Orientation::Horizontal);

        infoLayout->addWidget(sliderSqrt);

        spacer3 = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        infoLayout->addItem(spacer3);

        fracLayout = new QHBoxLayout();
        fracLayout->setObjectName("fracLayout");
        labelFrac = new QLabel(infoFrame);
        labelFrac->setObjectName("labelFrac");

        fracLayout->addWidget(labelFrac);

        labelFracValue = new QLabel(infoFrame);
        labelFracValue->setObjectName("labelFracValue");
        labelFracValue->setStyleSheet(QString::fromUtf8("color: #2980b9; font-weight: bold;"));
        labelFracValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        fracLayout->addWidget(labelFracValue);


        infoLayout->addLayout(fracLayout);

        sliderFrac = new QSlider(infoFrame);
        sliderFrac->setObjectName("sliderFrac");
        sliderFrac->setMinimum(-10);
        sliderFrac->setMaximum(10);
        sliderFrac->setOrientation(Qt::Orientation::Horizontal);

        infoLayout->addWidget(sliderFrac);

        bottomSpacer = new QSpacerItem(0, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        infoLayout->addItem(bottomSpacer);


        mainLayout->addWidget(infoFrame);

        graphFrame = new QFrame(GraphWindow);
        graphFrame->setObjectName("graphFrame");
        graphFrame->setStyleSheet(QString::fromUtf8("\n"
"QFrame#graphFrame {\n"
"    background-color: white;\n"
"    border-radius: 12px;\n"
"    border: 1px solid #dfe6e9;\n"
"}\n"
"      "));
        graphLayout = new QVBoxLayout(graphFrame);
        graphLayout->setContentsMargins(10, 10, 10, 10);
        graphLayout->setObjectName("graphLayout");
        customPlot = new QCustomPlot(graphFrame);
        customPlot->setObjectName("customPlot");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);

        graphLayout->addWidget(customPlot);


        mainLayout->addWidget(graphFrame);


        retranslateUi(GraphWindow);

        QMetaObject::connectSlotsByName(GraphWindow);
    } // setupUi

    void retranslateUi(QWidget *GraphWindow)
    {
        GraphWindow->setWindowTitle(QCoreApplication::translate("GraphWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\204\321\203\320\275\320\272\321\206\320\270\320\270", nullptr));
        titleLabel->setText(QCoreApplication::translate("GraphWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        paramGroup->setText(QCoreApplication::translate("GraphWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\204\321\203\320\275\320\272\321\206\320\270\320\271", nullptr));
        labelSin->setText(QCoreApplication::translate("GraphWindow", "sin(ax)", nullptr));
        labelSinValue->setText(QCoreApplication::translate("GraphWindow", "a = 1", nullptr));
        labelSqrt->setText(QCoreApplication::translate("GraphWindow", "sqrt(x+b)", nullptr));
        labelSqrtValue->setText(QCoreApplication::translate("GraphWindow", "b = 1", nullptr));
        labelFrac->setText(QCoreApplication::translate("GraphWindow", "1 / (x - c)", nullptr));
        labelFracValue->setText(QCoreApplication::translate("GraphWindow", "c = 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphWindow: public Ui_GraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHWINDOW_H
