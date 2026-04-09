#include "logintimp.h"
#include "ui_logintimp.h"

#include <QMessageBox>

LoginTimp::LoginTimp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");
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
        QMessageBox::information(this, "Успех", "Вход выполнен успешно!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}