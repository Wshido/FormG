#include "logintimp.h"
#include "ui_logintimp.h"
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include "registerwindow.h"
#include "forgotpassword.h"
#include "graphwindow.h"
#include "welcomewindow.h"
LoginTimp::LoginTimp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginTimp)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");
    setFixedSize(420, 420);

    // Применение стилей
    this->setStyleSheet(R"(
    QWidget {
        background-color: #ffffff;
        font-family: Segoe UI, Arial, sans-serif;
        font-size: 14px;
    }

    QFrame#frame {
        background-color: #d9ecff;
        border-radius: 20px;
        border: 1px solid #bcd6f0;
    }

    QLabel {
        color: black;
        background-color: transparent;
        border: none;
    }

    QLabel#titleLabel {
        font-size: 26px;
        font-weight: bold;
        background-color: transparent;
    }

    QLineEdit {
        background-color: white;
        border: 2px solid #b0c4de;
        border-radius: 10px;
        padding: 8px;
    }

    QLineEdit:focus {
        border: 2px solid #4a90e2;
    }

    QPushButton#loginButton {
        background-color: #7fb800;
        color: white;
        border-radius: 12px;
        padding: 10px;
        font-size: 16px;
        font-weight: bold;
    }

    QPushButton#loginButton:hover {
        background-color: #95c11f;
    }

    QLabel#forgotLabel {
        color: #1a73e8;
        text-decoration: underline;
        background-color: transparent;
    }
)");
    // Добавление тени
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 80));
    ui->frame->setGraphicsEffect(shadow);
}

LoginTimp::~LoginTimp()
{
    delete ui;
}
void LoginTimp::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username == "admin" && password == "1234") {

        QMessageBox::information(this,
                                 "Успех",
                                 "Вход выполнен успешно!");

        accept();
    }
    else {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Неверный логин или пароль!");
    }
}
void LoginTimp::on_backButton_clicked()
{
    reject();
}

void LoginTimp::on_forgotLabel_linkActivated(const QString &link)
{
    Q_UNUSED(link);

    ForgotPassword *fp = new ForgotPassword();

    fp->setWindowFlags(fp->windowFlags() | Qt::WindowStaysOnTopHint);

    connect(fp, &ForgotPassword::backRequested, this, [this, fp]() {
        this->show();
        fp->hide();
    });

    fp->show();

    this->hide();
}
void LoginTimp::on_registerButton_clicked()
{
    RegisterWindow *reg = new RegisterWindow();

    reg->setWindowFlags(reg->windowFlags() | Qt::WindowStaysOnTopHint);

    connect(reg, &RegisterWindow::backRequested, this, [this, reg]() {
        this->show();
        reg->hide();
    });

    reg->show();

    this->hide();
}