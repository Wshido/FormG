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
    QSpacerItem *topSpacer;
    QLabel *titleLabel;
    QSpacerItem *spacer1;
    QLineEdit *loginEdit;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QLineEdit *repeatPasswordEdit;
    QSpacerItem *spacer2;
    QPushButton *getCodeButton;
    QLineEdit *codeEdit;
    QPushButton *createButton;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *backButton;
    QSpacerItem *bottomSpacer;

    void setupUi(QWidget *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->resize(440, 600);
        RegisterWindow->setStyleSheet(QString::fromUtf8("\n"
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
"    font-size: 28px;\n"
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
"QPushButton#getCodeButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 12px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
""
                        "    border: none;\n"
"}\n"
"\n"
"QPushButton#getCodeButton:hover {\n"
"    background-color: #5dade2;\n"
"}\n"
"\n"
"QPushButton#getCodeButton:pressed {\n"
"    background-color: #2471a3;\n"
"}\n"
"\n"
"QPushButton#getCodeButton:disabled {\n"
"    background-color: #bdc3c7;\n"
"}\n"
"\n"
"QPushButton#createButton {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 12px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#createButton:hover {\n"
"    background-color: #2ecc71;\n"
"}\n"
"\n"
"QPushButton#createButton:pressed {\n"
"    background-color: #1e8449;\n"
"}\n"
"\n"
"QPushButton#createButton:disabled {\n"
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
"    background-colo"
                        "r: #d5dbdb;\n"
"}\n"
"   "));
        vboxLayout = new QVBoxLayout(RegisterWindow);
        vboxLayout->setObjectName("vboxLayout");
        frame = new QFrame(RegisterWindow);
        frame->setObjectName("frame");
        vboxLayout1 = new QVBoxLayout(frame);
        vboxLayout1->setObjectName("vboxLayout1");
        topSpacer = new QSpacerItem(0, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout1->addItem(topSpacer);

        titleLabel = new QLabel(frame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(titleLabel);

        spacer1 = new QSpacerItem(0, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout1->addItem(spacer1);

        loginEdit = new QLineEdit(frame);
        loginEdit->setObjectName("loginEdit");

        vboxLayout1->addWidget(loginEdit);

        emailEdit = new QLineEdit(frame);
        emailEdit->setObjectName("emailEdit");

        vboxLayout1->addWidget(emailEdit);

        passwordEdit = new QLineEdit(frame);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        vboxLayout1->addWidget(passwordEdit);

        repeatPasswordEdit = new QLineEdit(frame);
        repeatPasswordEdit->setObjectName("repeatPasswordEdit");
        repeatPasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        vboxLayout1->addWidget(repeatPasswordEdit);

        spacer2 = new QSpacerItem(0, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout1->addItem(spacer2);

        getCodeButton = new QPushButton(frame);
        getCodeButton->setObjectName("getCodeButton");

        vboxLayout1->addWidget(getCodeButton);

        codeEdit = new QLineEdit(frame);
        codeEdit->setObjectName("codeEdit");
        codeEdit->setEnabled(false);
        codeEdit->setMaxLength(6);

        vboxLayout1->addWidget(codeEdit);

        createButton = new QPushButton(frame);
        createButton->setObjectName("createButton");
        createButton->setEnabled(false);

        vboxLayout1->addWidget(createButton);

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


        vboxLayout->addWidget(frame);


        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        titleLabel->setText(QCoreApplication::translate("RegisterWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        loginEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\233\320\276\320\263\320\270\320\275 (\320\274\320\270\320\275. 3 \321\201\320\270\320\274\320\262\320\276\320\273\320\260)", nullptr));
        emailEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\255\320\273\320\265\320\272\321\202\321\200\320\276\320\275\320\275\320\260\321\217 \320\277\320\276\321\207\321\202\320\260", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\237\320\260\321\200\320\276\320\273\321\214 (\320\274\320\270\320\275. 8 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262, \320\273\320\260\321\202\320\270\320\275\320\270\321\206\320\260/\321\206\320\270\321\204\321\200\321\213)", nullptr));
        repeatPasswordEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        getCodeButton->setText(QCoreApplication::translate("RegisterWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \320\272\320\276\320\264 \320\277\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        codeEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\264 \320\270\320\267 \320\277\320\270\321\201\321\214\320\274\320\260", nullptr));
        createButton->setText(QCoreApplication::translate("RegisterWindow", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        backButton->setText(QCoreApplication::translate("RegisterWindow", "\342\227\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
