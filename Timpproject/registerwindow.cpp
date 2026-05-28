#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "servicemanager.h"
#include "databasemanager.h"
#include "emailsender.h"
#include <QMessageBox>
#include <QRegularExpression>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow)
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

    qDebug() << "=== РЕГИСТРАЦИЯ ===";
    qDebug() << "Логин:" << login;
    qDebug() << "Email:" << email;

    // Валидация
    if (login.isEmpty() || email.isEmpty() || pass1.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    if (login.length() < 3) {
        QMessageBox::warning(this, "Ошибка", "Логин должен содержать не менее 3 символов!");
        return;
    }

    // Проверка пароля: только латиница и цифры, минимум 8 символов
    QRegularExpression passwordRegex("^[A-Za-z0-9]{8,}$");
    if (!passwordRegex.match(pass1).hasMatch()) {
        QMessageBox::warning(this, "Ошибка пароля",
                             "Пароль должен содержать минимум 8 символов и только латинские буквы и цифры!");
        return;
    }

    if (!email.contains('@') || !email.contains('.')) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный email!");
        return;
    }

    if (pass1 != pass2) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
        return;
    }

    // Отправляем на сервер
    if (!ServiceManager::instance().isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу!");
        return;
    }

    ui->createButton->setEnabled(false);
    ServiceManager::instance().sendReg(login, pass1, email);

    // Обработка ответа от сервера
    static bool connected = false;
    if (!connected) {
        connect(&ServiceManager::instance(), &ServiceManager::regResult,
                this, [this](bool success) {
                    ui->createButton->setEnabled(true);

                    if (success) {
                        QMessageBox::information(this, "Успех", "Регистрация завершена успешно!");
                        EmailSender::instance().sendWelcomeEmail(ui->emailEdit->text(), ui->loginEdit->text());
                        emit backRequested();
                        this->hide();
                    } else {
                        QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином или email уже существует!");
                    }
                });
        connected = true;
    }
}

void RegisterWindow::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}