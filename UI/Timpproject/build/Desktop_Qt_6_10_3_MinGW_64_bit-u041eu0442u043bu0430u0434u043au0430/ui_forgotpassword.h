/********************************************************************************
** Form generated from reading UI file 'forgotpassword.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTPASSWORD_H
#define UI_FORGOTPASSWORD_H

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

class Ui_ForgotPassword
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *frame;
    QVBoxLayout *vboxLayout1;
    QLabel *titleLabel;
    QLineEdit *emailEdit;
    QPushButton *sendButton;
    QLabel *codeLabel;
    QLineEdit *codeLineEdit;
    QPushButton *confirmCodeButton;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordLineEdit;
    QLabel *repeatPasswordLabel;
    QLineEdit *repeatPasswordLineEdit;
    QPushButton *changePasswordButton;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *backButton;

    void setupUi(QWidget *ForgotPassword)
    {
        if (ForgotPassword->objectName().isEmpty())
            ForgotPassword->setObjectName("ForgotPassword");
        ForgotPassword->resize(400, 250);
        ForgotPassword->setStyleSheet(QString::fromUtf8("\n"
"QWidget {\n"
"    background-color: white;\n"
"    font-family: Segoe UI;\n"
"}\n"
"\n"
"QFrame#frame {\n"
"    background-color: #d9ecff;\n"
"    border-radius: 15px;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: black;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 20px;\n"
"    font-weight: bold;\n"
"        background: transparent;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background: white;\n"
"    border: 2px solid #b0c4de;\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #7fb800;\n"
"    color: white;\n"
"    border-radius: 12px;\n"
"    padding: 10px;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#backButton {\n"
"    background-color: white;\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    font-size: 18px;\n"
"    padding: 6px;\n"
"}\n"
"   "));
        vboxLayout = new QVBoxLayout(ForgotPassword);
        vboxLayout->setObjectName("vboxLayout");
        frame = new QFrame(ForgotPassword);
        frame->setObjectName("frame");
        vboxLayout1 = new QVBoxLayout(frame);
        vboxLayout1->setObjectName("vboxLayout1");
        titleLabel = new QLabel(frame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(titleLabel);

        emailEdit = new QLineEdit(frame);
        emailEdit->setObjectName("emailEdit");

        vboxLayout1->addWidget(emailEdit);

        sendButton = new QPushButton(frame);
        sendButton->setObjectName("sendButton");

        vboxLayout1->addWidget(sendButton);

        codeLabel = new QLabel(frame);
        codeLabel->setObjectName("codeLabel");

        vboxLayout1->addWidget(codeLabel);

        codeLineEdit = new QLineEdit(frame);
        codeLineEdit->setObjectName("codeLineEdit");

        vboxLayout1->addWidget(codeLineEdit);

        confirmCodeButton = new QPushButton(frame);
        confirmCodeButton->setObjectName("confirmCodeButton");

        vboxLayout1->addWidget(confirmCodeButton);

        newPasswordLabel = new QLabel(frame);
        newPasswordLabel->setObjectName("newPasswordLabel");

        vboxLayout1->addWidget(newPasswordLabel);

        newPasswordLineEdit = new QLineEdit(frame);
        newPasswordLineEdit->setObjectName("newPasswordLineEdit");
        newPasswordLineEdit->setEchoMode(QLineEdit::Password);

        vboxLayout1->addWidget(newPasswordLineEdit);

        repeatPasswordLabel = new QLabel(frame);
        repeatPasswordLabel->setObjectName("repeatPasswordLabel");

        vboxLayout1->addWidget(repeatPasswordLabel);

        repeatPasswordLineEdit = new QLineEdit(frame);
        repeatPasswordLineEdit->setObjectName("repeatPasswordLineEdit");
        repeatPasswordLineEdit->setEchoMode(QLineEdit::Password);

        vboxLayout1->addWidget(repeatPasswordLineEdit);

        changePasswordButton = new QPushButton(frame);
        changePasswordButton->setObjectName("changePasswordButton");

        vboxLayout1->addWidget(changePasswordButton);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        backButton = new QPushButton(frame);
        backButton->setObjectName("backButton");

        hboxLayout->addWidget(backButton);


        vboxLayout1->addLayout(hboxLayout);


        vboxLayout->addWidget(frame, 0, Qt::AlignCenter);


        retranslateUi(ForgotPassword);

        QMetaObject::connectSlotsByName(ForgotPassword);
    } // setupUi

    void retranslateUi(QWidget *ForgotPassword)
    {
        ForgotPassword->setWindowTitle(QCoreApplication::translate("ForgotPassword", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        titleLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        emailEdit->setPlaceholderText(QCoreApplication::translate("ForgotPassword", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        sendButton->setText(QCoreApplication::translate("ForgotPassword", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        codeLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\264", nullptr));
        codeLineEdit->setPlaceholderText(QCoreApplication::translate("ForgotPassword", "\320\232\320\276\320\264 \320\277\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        confirmCodeButton->setText(QCoreApplication::translate("ForgotPassword", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214 \320\272\320\276\320\264", nullptr));
        newPasswordLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        newPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("ForgotPassword", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        repeatPasswordLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        repeatPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("ForgotPassword", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        changePasswordButton->setText(QCoreApplication::translate("ForgotPassword", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        backButton->setText(QCoreApplication::translate("ForgotPassword", "\342\227\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForgotPassword: public Ui_ForgotPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPASSWORD_H
