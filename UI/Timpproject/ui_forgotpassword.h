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
    QSpacerItem *topSpacer;
    QLabel *titleLabel;
    QSpacerItem *spacer1;
    QLabel *loginLabel;
    QLineEdit *loginEdit;
    QPushButton *sendButton;
    QFrame *line;
    QLabel *codeLabel;
    QLineEdit *codeEdit;
    QPushButton *confirmCodeButton;
    QLabel *timerLabel;
    QFrame *line2;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordLineEdit;
    QLabel *repeatPasswordLabel;
    QLineEdit *repeatPasswordLineEdit;
    QPushButton *changePasswordButton;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *backButton;
    QSpacerItem *bottomSpacer;

    void setupUi(QWidget *ForgotPassword)
    {
        if (ForgotPassword->objectName().isEmpty())
            ForgotPassword->setObjectName("ForgotPassword");
        ForgotPassword->resize(420, 560);
        ForgotPassword->setStyleSheet(QString::fromUtf8("\n"
"QWidget {\n"
"    background-color: #eef3fb;\n"
"    font-family: \"Segoe UI\", Arial;\n"
"}\n"
"\n"
"QFrame#frame {\n"
"    background-color: white;\n"
"    border-radius: 20px;\n"
"    border: 1px solid #d5dde8;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"    background: transparent;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"    color: #1a5276;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: #f8f9fa;\n"
"    border: 2px solid #d5dde8;\n"
"    border-radius: 10px;\n"
"    padding: 10px 12px;\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    selection-background-color: #3498db;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 12px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border:"
                        " none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2ecc71;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1e8449;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #bdc3c7;\n"
"}\n"
"\n"
"QPushButton#backButton {\n"
"    background-color: #ecf0f1;\n"
"    color: #7f8c8d;\n"
"    border-radius: 10px;\n"
"    font-size: 16px;\n"
"    padding: 6px 12px;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#backButton:hover {\n"
"    background-color: #d5dbdb;\n"
"}\n"
"\n"
"QLabel#timerLabel {\n"
"    color: #e67e22;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"Line {\n"
"    color: #ecf0f1;\n"
"}\n"
"   "));
        vboxLayout = new QVBoxLayout(ForgotPassword);
        vboxLayout->setObjectName("vboxLayout");
        frame = new QFrame(ForgotPassword);
        frame->setObjectName("frame");
        vboxLayout1 = new QVBoxLayout(frame);
        vboxLayout1->setObjectName("vboxLayout1");
        topSpacer = new QSpacerItem(0, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout1->addItem(topSpacer);

        titleLabel = new QLabel(frame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(titleLabel);

        spacer1 = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout1->addItem(spacer1);

        loginLabel = new QLabel(frame);
        loginLabel->setObjectName("loginLabel");

        vboxLayout1->addWidget(loginLabel);

        loginEdit = new QLineEdit(frame);
        loginEdit->setObjectName("loginEdit");

        vboxLayout1->addWidget(loginEdit);

        sendButton = new QPushButton(frame);
        sendButton->setObjectName("sendButton");

        vboxLayout1->addWidget(sendButton);

        line = new QFrame(frame);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        vboxLayout1->addWidget(line);

        codeLabel = new QLabel(frame);
        codeLabel->setObjectName("codeLabel");
        codeLabel->setVisible(false);

        vboxLayout1->addWidget(codeLabel);

        codeEdit = new QLineEdit(frame);
        codeEdit->setObjectName("codeEdit");
        codeEdit->setVisible(false);
        codeEdit->setMaxLength(6);

        vboxLayout1->addWidget(codeEdit);

        confirmCodeButton = new QPushButton(frame);
        confirmCodeButton->setObjectName("confirmCodeButton");
        confirmCodeButton->setVisible(false);

        vboxLayout1->addWidget(confirmCodeButton);

        timerLabel = new QLabel(frame);
        timerLabel->setObjectName("timerLabel");
        timerLabel->setAlignment(Qt::AlignCenter);
        timerLabel->setVisible(false);

        vboxLayout1->addWidget(timerLabel);

        line2 = new QFrame(frame);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::Shape::HLine);
        line2->setFrameShadow(QFrame::Shadow::Sunken);
        line2->setVisible(false);

        vboxLayout1->addWidget(line2);

        newPasswordLabel = new QLabel(frame);
        newPasswordLabel->setObjectName("newPasswordLabel");
        newPasswordLabel->setVisible(false);

        vboxLayout1->addWidget(newPasswordLabel);

        newPasswordLineEdit = new QLineEdit(frame);
        newPasswordLineEdit->setObjectName("newPasswordLineEdit");
        newPasswordLineEdit->setEchoMode(QLineEdit::Password);
        newPasswordLineEdit->setVisible(false);

        vboxLayout1->addWidget(newPasswordLineEdit);

        repeatPasswordLabel = new QLabel(frame);
        repeatPasswordLabel->setObjectName("repeatPasswordLabel");
        repeatPasswordLabel->setVisible(false);

        vboxLayout1->addWidget(repeatPasswordLabel);

        repeatPasswordLineEdit = new QLineEdit(frame);
        repeatPasswordLineEdit->setObjectName("repeatPasswordLineEdit");
        repeatPasswordLineEdit->setEchoMode(QLineEdit::Password);
        repeatPasswordLineEdit->setVisible(false);

        vboxLayout1->addWidget(repeatPasswordLineEdit);

        changePasswordButton = new QPushButton(frame);
        changePasswordButton->setObjectName("changePasswordButton");
        changePasswordButton->setVisible(false);

        vboxLayout1->addWidget(changePasswordButton);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        backButton = new QPushButton(frame);
        backButton->setObjectName("backButton");

        hboxLayout->addWidget(backButton);


        vboxLayout1->addLayout(hboxLayout);

        bottomSpacer = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout1->addItem(bottomSpacer);


        vboxLayout->addWidget(frame, 0, Qt::AlignCenter);


        retranslateUi(ForgotPassword);

        QMetaObject::connectSlotsByName(ForgotPassword);
    } // setupUi

    void retranslateUi(QWidget *ForgotPassword)
    {
        ForgotPassword->setWindowTitle(QCoreApplication::translate("ForgotPassword", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        titleLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\241\320\261\321\200\320\276\321\201 \320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        loginLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        loginEdit->setPlaceholderText(QCoreApplication::translate("ForgotPassword", "\320\222\320\260\321\210 \320\273\320\276\320\263\320\270\320\275", nullptr));
        sendButton->setText(QCoreApplication::translate("ForgotPassword", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\272\320\276\320\264", nullptr));
        codeLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\264 \320\270\320\267 \320\277\320\270\321\201\321\214\320\274\320\260", nullptr));
        codeEdit->setPlaceholderText(QCoreApplication::translate("ForgotPassword", "6-\320\267\320\275\320\260\321\207\320\275\321\213\320\271 \320\272\320\276\320\264", nullptr));
        confirmCodeButton->setText(QCoreApplication::translate("ForgotPassword", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214 \320\272\320\276\320\264", nullptr));
        timerLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\232\320\276\320\264 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\202\320\265\320\273\320\265\320\275: 5 \320\274\320\270\320\275\321\203\321\202", nullptr));
        newPasswordLabel->setText(QCoreApplication::translate("ForgotPassword", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        newPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("ForgotPassword", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274 8 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262, \320\273\320\260\321\202\320\270\320\275\320\270\321\206\320\260/\321\206\320\270\321\204\321\200\321\213", nullptr));
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
