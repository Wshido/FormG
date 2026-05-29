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
    QSpacerItem *topSpacer;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QSpacerItem *spacer1;
    QLabel *loginLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QSpacerItem *spacer2;
    QPushButton *loginButton;
    QFrame *line;
    QLabel *codeLabel;
    QLineEdit *codeEdit;
    QLabel *timerLabel;
    QPushButton *confirmCodeButton;
    QFrame *line2;
    QHBoxLayout *bottomButtonsLayout;
    QPushButton *registerButton;
    QLabel *forgotLabel;
    QHBoxLayout *bottomLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *backButton;
    QSpacerItem *bottomSpacer;

    void setupUi(QWidget *LoginTimp)
    {
        if (LoginTimp->objectName().isEmpty())
            LoginTimp->setObjectName("LoginTimp");
        LoginTimp->resize(440, 560);
        LoginTimp->setStyleSheet(QString::fromUtf8("\n"
"  QWidget#LoginTimp {\n"
"      font-family: \"Segoe UI\", Arial, sans-serif;\n"
"      background-color: #eef3fb;\n"
"  }\n"
"\n"
"  QFrame#frame {\n"
"      background-color: white;\n"
"      border-radius: 20px;\n"
"      border: 1px solid #d5dde8;\n"
"  }\n"
"\n"
"  QLabel#titleLabel {\n"
"      font-size: 28px;\n"
"      font-weight: bold;\n"
"      color: #1a5276;\n"
"      background: transparent;\n"
"  }\n"
"\n"
"  QLabel#subtitleLabel {\n"
"      font-size: 13px;\n"
"      color: #7f8c8d;\n"
"      background: transparent;\n"
"  }\n"
"\n"
"  QLabel {\n"
"      color: #2c3e50;\n"
"      background: transparent;\n"
"      font-size: 13px;\n"
"  }\n"
"\n"
"  QLineEdit {\n"
"      background-color: #f8f9fa;\n"
"      border: 2px solid #d5dde8;\n"
"      border-radius: 10px;\n"
"      padding: 10px 12px;\n"
"      color: #2c3e50;\n"
"      font-size: 14px;\n"
"      selection-background-color: #3498db;\n"
"  }\n"
"\n"
"  QLineEdit:focus {\n"
"      border: 2px solid #3498db;\n"
"      background-color"
                        ": #ffffff;\n"
"  }\n"
"\n"
"  QPushButton#loginButton {\n"
"      background-color: #27ae60;\n"
"      color: #ffffff;\n"
"      border-radius: 10px;\n"
"      padding: 12px;\n"
"      font-size: 15px;\n"
"      font-weight: bold;\n"
"      border: none;\n"
"  }\n"
"\n"
"  QPushButton#loginButton:hover {\n"
"      background-color: #2ecc71;\n"
"  }\n"
"\n"
"  QPushButton#loginButton:pressed {\n"
"      background-color: #1e8449;\n"
"  }\n"
"\n"
"  QPushButton#loginButton:disabled {\n"
"      background-color: #bdc3c7;\n"
"  }\n"
"\n"
"  QPushButton#confirmCodeButton {\n"
"      background-color: #3498db;\n"
"      color: white;\n"
"      border-radius: 10px;\n"
"      padding: 12px;\n"
"      font-size: 15px;\n"
"      font-weight: bold;\n"
"      border: none;\n"
"  }\n"
"\n"
"  QPushButton#confirmCodeButton:hover {\n"
"      background-color: #5dade2;\n"
"  }\n"
"\n"
"  QPushButton#confirmCodeButton:pressed {\n"
"      background-color: #2471a3;\n"
"  }\n"
"\n"
"  QPushButton#confirmCodeButton:disabled {\n"
""
                        "      background-color: #bdc3c7;\n"
"  }\n"
"\n"
"  QLabel#forgotLabel {\n"
"      color: #3498db;\n"
"      font-size: 13px;\n"
"  }\n"
"\n"
"  QPushButton#registerButton {\n"
"      background-color: #3498db;\n"
"      color: white;\n"
"      border-radius: 10px;\n"
"      padding: 10px;\n"
"      font-size: 13px;\n"
"      font-weight: bold;\n"
"      border: none;\n"
"  }\n"
"\n"
"  QPushButton#registerButton:hover {\n"
"      background-color: #5dade2;\n"
"  }\n"
"\n"
"  QPushButton#backButton {\n"
"      background-color: #ecf0f1;\n"
"      color: #7f8c8d;\n"
"      border-radius: 10px;\n"
"      font-size: 16px;\n"
"      padding: 6px 12px;\n"
"      border: none;\n"
"  }\n"
"\n"
"  QPushButton#backButton:hover {\n"
"      background-color: #d5dbdb;\n"
"  }\n"
"\n"
"  QLabel#timerLabel {\n"
"      color: #e67e22;\n"
"      font-size: 12px;\n"
"      font-weight: bold;\n"
"  }\n"
"\n"
"  Line {\n"
"      color: #ecf0f1;\n"
"  }\n"
"   "));
        mainLayout = new QVBoxLayout(LoginTimp);
        mainLayout->setObjectName("mainLayout");
        frame = new QFrame(LoginTimp);
        frame->setObjectName("frame");
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        topSpacer = new QSpacerItem(0, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(topSpacer);

        titleLabel = new QLabel(frame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(frame);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(subtitleLabel);

        spacer1 = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacer1);

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
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(passwordLineEdit);

        spacer2 = new QSpacerItem(0, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacer2);

        loginButton = new QPushButton(frame);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);

        line = new QFrame(frame);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        codeLabel = new QLabel(frame);
        codeLabel->setObjectName("codeLabel");
        codeLabel->setVisible(false);

        verticalLayout->addWidget(codeLabel);

        codeEdit = new QLineEdit(frame);
        codeEdit->setObjectName("codeEdit");
        codeEdit->setVisible(false);
        codeEdit->setMaxLength(6);

        verticalLayout->addWidget(codeEdit);

        timerLabel = new QLabel(frame);
        timerLabel->setObjectName("timerLabel");
        timerLabel->setAlignment(Qt::AlignCenter);
        timerLabel->setVisible(false);

        verticalLayout->addWidget(timerLabel);

        confirmCodeButton = new QPushButton(frame);
        confirmCodeButton->setObjectName("confirmCodeButton");
        confirmCodeButton->setVisible(false);

        verticalLayout->addWidget(confirmCodeButton);

        line2 = new QFrame(frame);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::Shape::HLine);
        line2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line2);

        bottomButtonsLayout = new QHBoxLayout();
        bottomButtonsLayout->setObjectName("bottomButtonsLayout");
        registerButton = new QPushButton(frame);
        registerButton->setObjectName("registerButton");

        bottomButtonsLayout->addWidget(registerButton);

        forgotLabel = new QLabel(frame);
        forgotLabel->setObjectName("forgotLabel");
        forgotLabel->setTextFormat(Qt::TextFormat::RichText);
        forgotLabel->setTextInteractionFlags(Qt::TextInteractionFlag::TextBrowserInteraction);
        forgotLabel->setOpenExternalLinks(false);

        bottomButtonsLayout->addWidget(forgotLabel);


        verticalLayout->addLayout(bottomButtonsLayout);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName("bottomLayout");
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bottomLayout->addItem(horizontalSpacer);

        backButton = new QPushButton(frame);
        backButton->setObjectName("backButton");
        backButton->setMinimumSize(QSize(40, 32));

        bottomLayout->addWidget(backButton);


        verticalLayout->addLayout(bottomLayout);

        bottomSpacer = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(bottomSpacer);


        mainLayout->addWidget(frame, 0, Qt::AlignCenter);


        retranslateUi(LoginTimp);

        QMetaObject::connectSlotsByName(LoginTimp);
    } // setupUi

    void retranslateUi(QWidget *LoginTimp)
    {
        LoginTimp->setWindowTitle(QCoreApplication::translate("LoginTimp", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginTimp", "\320\222\321\205\320\276\320\264 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("LoginTimp", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\262\320\260\321\210\320\270 \321\203\321\207\321\221\321\202\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        loginLabel->setText(QCoreApplication::translate("LoginTimp", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("LoginTimp", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginTimp", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginTimp", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginTimp", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        codeLabel->setText(QCoreApplication::translate("LoginTimp", "\320\232\320\276\320\264 \320\277\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\321\217 \320\270\320\267 \320\277\320\276\321\207\321\202\321\213", nullptr));
        codeEdit->setPlaceholderText(QCoreApplication::translate("LoginTimp", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 6-\320\267\320\275\320\260\321\207\320\275\321\213\320\271 \320\272\320\276\320\264", nullptr));
        timerLabel->setText(QCoreApplication::translate("LoginTimp", "\320\232\320\276\320\264 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\202\320\265\320\273\320\265\320\275: 5 \320\274\320\270\320\275\321\203\321\202", nullptr));
        confirmCodeButton->setText(QCoreApplication::translate("LoginTimp", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214 \320\272\320\276\320\264", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginTimp", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        forgotLabel->setText(QCoreApplication::translate("LoginTimp", "<a href=\"#\">\320\227\320\260\320\261\321\213\320\273\320\270 \320\277\320\260\321\200\320\276\320\273\321\214?</a>", nullptr));
        backButton->setText(QCoreApplication::translate("LoginTimp", "\342\227\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginTimp: public Ui_LoginTimp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINTIMP_H
