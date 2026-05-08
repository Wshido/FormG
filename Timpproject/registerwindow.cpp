#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_createButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString email = ui->emailEdit->text();
    QString pass1 = ui->passwordEdit->text();
    QString pass2 = ui->repeatPasswordEdit->text();

    if (login.isEmpty() || email.isEmpty() || pass1.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    if (pass1 != pass2) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
        return;
    }

    QMessageBox::information(this, "Успех", "Регистрация завершена!");
}

void RegisterWindow::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}