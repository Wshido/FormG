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
    QLabel *titleLabel;
    QLabel *infoLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *bottomLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *nextButton;

    void setupUi(QWidget *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName("AboutWindow");
        AboutWindow->resize(900, 600);
        AboutWindow->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QWidget {\n"
"    background-color: #eef3fb;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QFrame#mainFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"    border: 1px solid #cfd8e3;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: black;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #e0e6ef;\n"
"    border-radius: 8px;\n"
"    padding: 6px 14px;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #cfd8e3;\n"
"}\n"
"\n"
"   "));
        mainLayout = new QVBoxLayout(AboutWindow);
        mainLayout->setObjectName("mainLayout");
        mainFrame = new QFrame(AboutWindow);
        mainFrame->setObjectName("mainFrame");
        verticalLayout = new QVBoxLayout(mainFrame);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(mainFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        infoLabel = new QLabel(mainFrame);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setWordWrap(true);
        infoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(infoLabel);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName("bottomLayout");
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bottomLayout->addItem(horizontalSpacer);

        nextButton = new QPushButton(mainFrame);
        nextButton->setObjectName("nextButton");
        nextButton->setMinimumSize(QSize(60, 40));

        bottomLayout->addWidget(nextButton);


        verticalLayout->addLayout(bottomLayout);


        mainLayout->addWidget(mainFrame);


        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QWidget *AboutWindow)
    {
        AboutWindow->setWindowTitle(QCoreApplication::translate("AboutWindow", "\320\236 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\321\207\320\270\320\272\320\265", nullptr));
        titleLabel->setText(QCoreApplication::translate("AboutWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\321\207\320\270\320\272\320\265", nullptr));
        infoLabel->setText(QCoreApplication::translate("AboutWindow", "\n"
"\320\237\321\200\320\276\320\265\320\272\321\202 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\320\260\320\275 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\276\320\274.\n"
"\n"
"\320\232\320\276\320\274\320\260\320\275\320\264\320\260 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\320\272\320\270:\n"
"\342\200\242 \320\230\320\274\321\217 1\n"
"\342\200\242 \320\230\320\274\321\217 2\n"
"\342\200\242 \320\230\320\274\321\217 3\n"
"\n"
"\320\232\321\203\321\200\321\201\320\276\320\262\320\276\320\271 \320\277\321\200\320\276\320\265\320\272\321\202 \320\275\320\260 Qt Creator.\n"
"         ", nullptr));
        nextButton->setText(QCoreApplication::translate("AboutWindow", "\342\226\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
