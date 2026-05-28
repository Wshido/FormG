/********************************************************************************
** Form generated from reading UI file 'registerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *frame;
    QVBoxLayout *vboxLayout1;
    QLabel *titleLabel;
    QLineEdit *loginEdit;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QLineEdit *repeatPasswordEdit;
    QPushButton *createButton;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *backButton;

    void setupUi(QWidget *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->resize(420, 460);
        RegisterWindow->setStyleSheet(QString::fromUtf8("\n"
"QWidget {\n"
"    background-color: #f2f4f8;\n"
"    font-family: Segoe UI, Arial;\n"
"}\n"
"\n"
"QFrame#frame {\n"
"    background-color: #d9ecff;\n"
"    border-radius: 20px;\n"
"    border: 1px solid #bcd6f0;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: black;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 26px;\n"
"    font-weight: bold;\n"
"    color: black;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background: white;\n"
"    border: 2px solid #b0c4de;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #4a90e2;\n"
"}\n"
"\n"
"QPushButton#createButton {\n"
"    background-color: #7fb800;\n"
"    color: white;\n"
"    border-radius: 12px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton#createButton:hover {\n"
"    background-color: #95c11f;\n"
"}\n"
"\n"
"QPushButton#backButton {\n"
"    font-size: 18px;\n"
"    padding: 6px;\n"
"    border-radius: 10px;\n"
"}\n"
"   "));
        vboxLayout = new QVBoxLayout(RegisterWindow);
        vboxLayout->setObjectName("vboxLayout");
        frame = new QFrame(RegisterWindow);
        frame->setObjectName("frame");
        vboxLayout1 = new QVBoxLayout(frame);
        vboxLayout1->setObjectName("vboxLayout1");
        titleLabel = new QLabel(frame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(titleLabel);

        loginEdit = new QLineEdit(frame);
        loginEdit->setObjectName("loginEdit");

        vboxLayout1->addWidget(loginEdit);

        emailEdit = new QLineEdit(frame);
        emailEdit->setObjectName("emailEdit");

        vboxLayout1->addWidget(emailEdit);

        passwordEdit = new QLineEdit(frame);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        vboxLayout1->addWidget(passwordEdit);

        repeatPasswordEdit = new QLineEdit(frame);
        repeatPasswordEdit->setObjectName("repeatPasswordEdit");
        repeatPasswordEdit->setEchoMode(QLineEdit::Password);

        vboxLayout1->addWidget(repeatPasswordEdit);

        createButton = new QPushButton(frame);
        createButton->setObjectName("createButton");

        vboxLayout1->addWidget(createButton);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        backButton = new QPushButton(frame);
        backButton->setObjectName("backButton");

        hboxLayout->addWidget(backButton);


        vboxLayout1->addLayout(hboxLayout);


        vboxLayout->addWidget(frame, 0, Qt::AlignCenter);


        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        titleLabel->setText(QCoreApplication::translate("RegisterWindow", "  \320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217  ", nullptr));
        loginEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        emailEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\276\321\207\321\202\321\203", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        repeatPasswordEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        createButton->setText(QCoreApplication::translate("RegisterWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        backButton->setText(QCoreApplication::translate("RegisterWindow", "\342\227\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
