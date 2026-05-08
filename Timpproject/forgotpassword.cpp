#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QMessageBox>

ForgotPassword::ForgotPassword(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);

    // Скрываем ввод кода
    ui->codeLabel->hide();
    ui->codeLineEdit->hide();
    ui->confirmCodeButton->hide();

    // Скрываем смену пароля
    ui->newPasswordLabel->hide();
    ui->newPasswordLineEdit->hide();

    ui->repeatPasswordLabel->hide();
    ui->repeatPasswordLineEdit->hide();

    ui->changePasswordButton->hide();
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_sendButton_clicked()
{
    QString email = ui->emailEdit->text();

    if (email.isEmpty()) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Введите логин!");
        return;
    }

    QMessageBox::information(this,
                             "Код отправлен",
                             "Код подтверждения отправлен.");

    // Показываем ввод кода
    ui->codeLabel->show();
    ui->codeLineEdit->show();
    ui->confirmCodeButton->show();
}

void ForgotPassword::on_confirmCodeButton_clicked()
{
    QString code = ui->codeLineEdit->text();

    // Тестовый код
    if (code == "1234") {

        QMessageBox::information(this,
                                 "Успех",
                                 "Код подтвержден!");

        // Показываем поля нового пароля
        ui->newPasswordLabel->show();
        ui->newPasswordLineEdit->show();

        ui->repeatPasswordLabel->show();
        ui->repeatPasswordLineEdit->show();

        ui->changePasswordButton->show();
    }
    else {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Неверный код!");
    }
}

void ForgotPassword::on_changePasswordButton_clicked()
{
    QString pass1 = ui->newPasswordLineEdit->text();
    QString pass2 = ui->repeatPasswordLineEdit->text();

    if (pass1.isEmpty() || pass2.isEmpty()) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните все поля!");
        return;
    }

    if (pass1 != pass2) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Пароли не совпадают!");
        return;
    }

    QMessageBox::information(this,
                             "Успех",
                             "Пароль успешно изменен!");

    this->hide();
}

void ForgotPassword::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}