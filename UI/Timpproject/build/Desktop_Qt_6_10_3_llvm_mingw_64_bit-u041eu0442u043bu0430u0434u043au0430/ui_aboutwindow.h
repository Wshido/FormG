/********************************************************************************
** Form generated from reading UI file 'aboutwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QVBoxLayout *mainLayout;
    QFrame *mainFrame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *topSpacer;
    QLabel *titleLabel;
    QSpacerItem *spacer1;
    QLabel *infoLabel;
    QSpacerItem *spacer2;
    QHBoxLayout *bottomLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *nextButton;
    QSpacerItem *bottomSpacer;

    void setupUi(QWidget *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName("AboutWindow");
        AboutWindow->resize(900, 600);
        AboutWindow->setStyleSheet(QString::fromUtf8("\n"
"QWidget {\n"
"    background-color: #eef3fb;\n"
"    font-family: \"Segoe UI\", Arial;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QFrame#mainFrame {\n"
"    background-color: white;\n"
"    border-radius: 16px;\n"
"    border: 1px solid #d5dde8;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 26px;\n"
"    font-weight: bold;\n"
"    color: #1a5276;\n"
"}\n"
"\n"
"QLabel#infoLabel {\n"
"    font-size: 14px;\n"
"    color: #555e68;\n"
"    line-height: 1.6;\n"
"}\n"
"\n"
"QPushButton#nextButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border-radius: 20px;\n"
"    font-size: 20px;\n"
"    min-width: 60px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton#nextButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton#nextButton:pressed {\n"
"    background-color: #1a5276;\n"
"}\n"
"   "));
        mainLayout = new QVBoxLayout(AboutWindow);
        mainLayout->setObjectName("mainLayout");
        mainFrame = new QFrame(AboutWindow);
        mainFrame->setObjectName("mainFrame");
        verticalLayout = new QVBoxLayout(mainFrame);
        verticalLayout->setObjectName("verticalLayout");
        topSpacer = new QSpacerItem(0, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(topSpacer);

        titleLabel = new QLabel(mainFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        spacer1 = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacer1);

        infoLabel = new QLabel(mainFrame);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->setWordWrap(true);

        verticalLayout->addWidget(infoLabel);

        spacer2 = new QSpacerItem(0, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacer2);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName("bottomLayout");
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bottomLayout->addItem(horizontalSpacer);

        nextButton = new QPushButton(mainFrame);
        nextButton->setObjectName("nextButton");
        nextButton->setMinimumSize(QSize(60, 40));

        bottomLayout->addWidget(nextButton);


        verticalLayout->addLayout(bottomLayout);

        bottomSpacer = new QSpacerItem(0, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(bottomSpacer);


        mainLayout->addWidget(mainFrame);


        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QWidget *AboutWindow)
    {
        AboutWindow->setWindowTitle(QCoreApplication::translate("AboutWindow", "\320\236 \320\277\321\200\320\276\320\265\320\272\321\202\320\265", nullptr));
        titleLabel->setText(QCoreApplication::translate("AboutWindow", "\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \321\206\320\270\321\204\321\200\320\276\320\262\320\276\320\271 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270", nullptr));
        infoLabel->setText(QCoreApplication::translate("AboutWindow", "\320\232\320\273\320\270\320\265\320\275\321\202-\321\201\320\265\321\200\320\262\320\265\321\200\320\275\320\276\320\265 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\264\320\273\321\217 \320\262\321\213\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217\n"
"\320\270 \320\262\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\320\270 \320\272\321\203\321\201\320\276\321\207\320\275\320\276-\320\267\320\260\320\264\320\260\320\275\320\275\321\213\321\205 \321\204\321\203\320\275\320\272\321\206\320\270\320\271\n"
"\n"
"\320\243\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\270 \320\277\321\200\320\276\320\265\320\272\321\202\320\260:\n"
"\n"
"    \320\241\320\274\320\270\321\200\320\275\320\276\320\262 \320\257\321\200\320\276\321\201\320\273\320\260\320\262\n"
"    \320\223\321\213\320\273\320\272\320\260 \320\223\320\273\320\265\320\261\n"
"    \320\227\320\262\321\221\320\267\320\264\320\272\320\270\320\275 \320\225"
                        "\320\263\320\276\321\200\n"
"    \320\230\320\262\320\260\320\275 \320\240\321\203\320\261\321\206\320\276\320\262\n"
"\n"
"\320\232\321\203\321\200\321\201\320\276\320\262\320\276\320\271 \320\277\321\200\320\276\320\265\320\272\321\202 \302\267 Qt Creator \302\267 2024", nullptr));
        nextButton->setText(QCoreApplication::translate("AboutWindow", "\342\226\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
