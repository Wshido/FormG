/********************************************************************************
** Form generated from reading UI file 'welcomewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEWINDOW_H
#define UI_WELCOMEWINDOW_H

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

class Ui_WelcomeWindow
{
public:
    QVBoxLayout *mainLayout;
    QFrame *mainFrame;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QHBoxLayout *imagesLayout;
    QVBoxLayout *vboxLayout;
    QLabel *imageLabel1;
    QLabel *imageTitle1;
    QVBoxLayout *vboxLayout1;
    QLabel *imageLabel2;
    QLabel *imageTitle2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *navigationLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *backButton;
    QPushButton *nextButton;

    void setupUi(QWidget *WelcomeWindow)
    {
        if (WelcomeWindow->objectName().isEmpty())
            WelcomeWindow->setObjectName("WelcomeWindow");
        WelcomeWindow->resize(900, 600);
        WelcomeWindow->setStyleSheet(QString::fromUtf8("\n"
"QWidget {\n"
"    background-color: #eef3fb;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QFrame#mainFrame {\n"
"    background-color: #ffffff;\n"
"    border-radius: 12px;\n"
"    border: 1px solid #cfd8e3;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #000000;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #e0e6ef;\n"
"    border-radius: 6px;\n"
"    padding: 5px 12px;\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #d0d8e5;\n"
"}\n"
"   "));
        mainLayout = new QVBoxLayout(WelcomeWindow);
        mainLayout->setObjectName("mainLayout");
        mainFrame = new QFrame(WelcomeWindow);
        mainFrame->setObjectName("mainFrame");
        verticalLayout = new QVBoxLayout(mainFrame);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(mainFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        descriptionLabel = new QLabel(mainFrame);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setWordWrap(true);

        verticalLayout->addWidget(descriptionLabel);

        imagesLayout = new QHBoxLayout();
        imagesLayout->setObjectName("imagesLayout");
        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName("vboxLayout");
        imageLabel1 = new QLabel(mainFrame);
        imageLabel1->setObjectName("imageLabel1");
        imageLabel1->setMinimumSize(QSize(150, 150));
        imageLabel1->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(imageLabel1);

        imageTitle1 = new QLabel(mainFrame);
        imageTitle1->setObjectName("imageTitle1");
        imageTitle1->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(imageTitle1);


        imagesLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName("vboxLayout1");
        imageLabel2 = new QLabel(mainFrame);
        imageLabel2->setObjectName("imageLabel2");
        imageLabel2->setMinimumSize(QSize(150, 150));
        imageLabel2->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(imageLabel2);

        imageTitle2 = new QLabel(mainFrame);
        imageTitle2->setObjectName("imageTitle2");
        imageTitle2->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(imageTitle2);


        imagesLayout->addLayout(vboxLayout1);


        verticalLayout->addLayout(imagesLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        navigationLayout = new QHBoxLayout();
        navigationLayout->setObjectName("navigationLayout");
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navigationLayout->addItem(horizontalSpacer);

        backButton = new QPushButton(mainFrame);
        backButton->setObjectName("backButton");
        backButton->setEnabled(false);

        navigationLayout->addWidget(backButton);

        nextButton = new QPushButton(mainFrame);
        nextButton->setObjectName("nextButton");

        navigationLayout->addWidget(nextButton);


        verticalLayout->addLayout(navigationLayout);


        mainLayout->addWidget(mainFrame);


        retranslateUi(WelcomeWindow);

        QMetaObject::connectSlotsByName(WelcomeWindow);
    } // setupUi

    void retranslateUi(QWidget *WelcomeWindow)
    {
        WelcomeWindow->setWindowTitle(QCoreApplication::translate("WelcomeWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\275\320\260 \320\272\321\203\321\200\321\201\320\276\320\262\320\276\320\271 \320\277\321\200\320\276\320\265\320\272\321\202", nullptr));
        titleLabel->setText(QCoreApplication::translate("WelcomeWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\275\320\260 \320\272\321\203\321\200\321\201\320\276\320\262\320\276\320\271 \320\277\321\200\320\276\320\265\320\272\321\202", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("WelcomeWindow", "\320\222 \320\275\320\260\321\201\321\202\320\276\321\217\321\211\320\265\320\274 \320\272\321\203\321\200\321\201\320\276\320\262\320\276\320\274 \320\277\321\200\320\276\320\265\320\272\321\202\320\265 \320\275\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\320\276 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 \"\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \321\206\320\270\321\204\321\200\320\276\320\262\320\276\320\271 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\262 \320\272\320\273\320\270\320\265\320\275\321\202-\321\201\320\265\321\200\320\262\320\265\321\200\320\275\320\276\320\274 \320\277\321\200\320\276\320\265\320\272\321\202\320\265\" \320\275\320\260 \321\217\320\267\321\213\320\272\320\265 C++ \321\201 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\320\276"
                        "\320\262\320\260\320\275\320\270\320\265\320\274 Qt \320\264\320\273\321\217 \320\262\321\213\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217 \320\270 \320\262\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\320\270 \321\204\321\203\320\275\320\272\321\206\320\270\320\270.", nullptr));
        imageLabel1->setText(QCoreApplication::translate("WelcomeWindow", "IMG1", nullptr));
        imageTitle1->setText(QCoreApplication::translate("WelcomeWindow", "\320\230\321\201\321\201\320\273\320\265\320\264\321\203\320\265\320\274\320\260\321\217 \321\204\321\203\320\275\320\272\321\206\320\270\321\217", nullptr));
        imageLabel2->setText(QCoreApplication::translate("WelcomeWindow", "IMG2", nullptr));
        imageTitle2->setText(QCoreApplication::translate("WelcomeWindow", "\320\236\321\201\320\276\320\261\320\265\320\275\320\275\320\276\321\201\321\202\320\270 \321\204\321\203\320\275\320\272\321\206\320\270\320\270", nullptr));
        backButton->setText(QCoreApplication::translate("WelcomeWindow", "\342\227\200", nullptr));
        nextButton->setText(QCoreApplication::translate("WelcomeWindow", "\342\226\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomeWindow: public Ui_WelcomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEWINDOW_H
