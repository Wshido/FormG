/********************************************************************************
** Form generated from reading UI file 'logintimp.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINTIMP_H
#define UI_LOGINTIMP_H

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

class Ui_LoginTimp
{
public:
    QVBoxLayout *mainLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *loginLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QHBoxLayout *bottomButtonsLayout;
    QPushButton *registerButton;
    QLabel *forgotLabel;
    QHBoxLayout *bottomLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *backButton;

    void setupUi(QWidget *LoginTimp)
    {
        if (LoginTimp->objectName().isEmpty())
            LoginTimp->setObjectName("LoginTimp");
        LoginTimp->resize(420, 360);
        LoginTimp->setStyleSheet(QString::fromUtf8("\n"
"  QWidget#LoginTimp {\n"
"      font-family: Segoe UI, Arial, sans-serif;\n"
"      background-color: #d9ecff;\n"
"  }\n"
"\n"
"  /* \320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217 \320\272\320\260\321\200\321\202\320\276\321\207\320\272\320\260 */\n"
"  QFrame#frame {\n"
"      background-color: transparent;\n"
"      border-radius: 20px;\n"
"      border: 1px solid #d9ecff;\n"
"  }\n"
"\n"
"  /* \320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272 */\n"
"  QLabel#titleLabel {\n"
"      font-size: 26px;\n"
"      font-weight: bold;\n"
"      background: transparent;\n"
"  }\n"
"\n"
"  /* \320\237\320\276\320\264\320\267\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272 */\n"
"  QLabel#subtitleLabel {\n"
"      font-size: 14px;\n"
"      color: #000000;\n"
"      background: transparent;\n"
"  }\n"
"\n"
"  /* \320\236\320\261\321\213\321\207\320\275\321\213\320\265 \320\275\320\260\320\264\320\277\320\270\321\201\320\270 */\n"
"  Q"
                        "Label {\n"
"      color: #000000;\n"
"      background: transparent;\n"
"  }\n"
"\n"
"  /* \320\237\320\276\320\273\321\217 \320\262\320\262\320\276\320\264\320\260 */\n"
"  QLineEdit {\n"
"      background-color: #ffffff;\n"
"      border: 2px solid #b0c4de;\n"
"      border-radius: 10px;\n"
"      padding: 8px;\n"
"      color: #000000;\n"
"  }\n"
"\n"
"  QLineEdit:focus {\n"
"      border: 2px solid #4a90e2;\n"
"  }\n"
"\n"
"  /* \320\232\320\275\320\276\320\277\320\272\320\260 \320\262\321\205\320\276\320\264\320\260 */\n"
"  QPushButton#loginButton {\n"
"      background-color: #7fb800;\n"
"      color: #ffffff;\n"
"      border-radius: 12px;\n"
"      padding: 10px;\n"
"      font-size: 16px;\n"
"      font-weight: bold;\n"
"  }\n"
"\n"
"  QPushButton#loginButton:hover {\n"
"      background-color: #95c11f;\n"
"  }\n"
"\n"
"  QPushButton#loginButton:pressed {\n"
"      background-color: #6aa000;\n"
"  }\n"
"\n"
"  /*\"\320\227\320\260\320\261\321\213\320\273\320\270 \320\277\320\260\321\200\320\276\320\273"
                        "\321\214?\" */\n"
"  QLabel#forgotLabel {\n"
"      color: #1a73e8;\n"
"      text-decoration: underline;\n"
"  }\n"
"\n"
"  /* \320\232\320\275\320\276\320\277\320\272\320\260 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270 */\n"
"  QPushButton#registerButton {\n"
"      background-color: #4a90e2;\n"
"      color: white;\n"
"      border-radius: 10px;\n"
"      padding: 8px;\n"
"  }\n"
"\n"
"  QPushButton#registerButton:hover {\n"
"      background-color: #5aa0f2;\n"
"  }\n"
"  QPushButton#backButton {\n"
"      background-color: white;\n"
"      border-radius: 10px;\n"
"      font-size: 18px;\n"
"      padding: 6px;\n"
"      }\n"
"\n"
"   "));
        mainLayout = new QVBoxLayout(LoginTimp);
        mainLayout->setObjectName("mainLayout");
        frame = new QFrame(LoginTimp);
        frame->setObjectName("frame");
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(frame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        loginLabel = new QLabel(frame);
        loginLabel->setObjectName("loginLabel");

        verticalLayout->addWidget(loginLabel);

        usernameLineEdit = new QLineEdit(frame);
        usernameLineEdit->setObjectName("usernameLineEdit");

        verticalLayout->addWidget(usernameLineEdit);

        passwordLabel = new QLabel(frame);
        passwordLabel->setObjectName("passwordLabel");

        verticalLayout->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(frame);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordLineEdit);

        loginButton = new QPushButton(frame);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);

        bottomButtonsLayout = new QHBoxLayout();
        bottomButtonsLayout->setObjectName("bottomButtonsLayout");
        registerButton = new QPushButton(frame);
        registerButton->setObjectName("registerButton");

        bottomButtonsLayout->addWidget(registerButton);

        forgotLabel = new QLabel(frame);
        forgotLabel->setObjectName("forgotLabel");
        forgotLabel->setTextFormat(Qt::RichText);
        forgotLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
        forgotLabel->setOpenExternalLinks(false);

        bottomButtonsLayout->addWidget(forgotLabel);


        verticalLayout->addLayout(bottomButtonsLayout);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName("bottomLayout");
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bottomLayout->addItem(horizontalSpacer);

        backButton = new QPushButton(frame);
        backButton->setObjectName("backButton");
        backButton->setMinimumSize(QSize(40, 30));

        bottomLayout->addWidget(backButton);


        verticalLayout->addLayout(bottomLayout);


        mainLayout->addWidget(frame, 0, Qt::AlignCenter);


        retranslateUi(LoginTimp);

        QMetaObject::connectSlotsByName(LoginTimp);
    } // setupUi

    void retranslateUi(QWidget *LoginTimp)
    {
        LoginTimp->setWindowTitle(QCoreApplication::translate("LoginTimp", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginTimp", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        loginLabel->setText(QCoreApplication::translate("LoginTimp", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("LoginTimp", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginTimp", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginTimp", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginTimp", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginTimp", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        forgotLabel->setText(QCoreApplication::translate("LoginTimp", "<a href=\"#\">\320\227\320\260\320\261\321\213\320\273\320\270 \320\277\320\260\321\200\320\276\320\273\321\214?</a>", nullptr));
        backButton->setText(QCoreApplication::translate("LoginTimp", "\342\227\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginTimp: public Ui_LoginTimp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINTIMP_H
