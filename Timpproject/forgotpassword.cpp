#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "servicemanager.h"
#include <QMessageBox>

ForgotPassword::ForgotPassword(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);

    // Изначально скрываем поля для кода и нового пароля
    ui->codeLabel->hide();
    ui->codeLineEdit->hide();
    ui->confirmCodeButton->hide();
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

// КНОПКА "ОТПРАВИТЬ" - запрос кода на email
void ForgotPassword::on_sendButton_clicked()
{
    QString email = ui->emailEdit->text();

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите email!");
        return;
    }

    if (!email.contains('@') || !email.contains('.')) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный email!");
        return;
    }

    if (!ServiceManager::instance().isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу!");
        return;
    }

    m_tempEmail = email;
    ui->sendButton->setEnabled(false);

    // Запрашиваем код у сервера
    ServiceManager::instance().sendRequestCode(email);

    // Обработка ответа сервера
    connect(&ServiceManager::instance(), &ServiceManager::codeRequestResult,
            this, [this](bool success) {
                ui->sendButton->setEnabled(true);

                if (success) {
                    QMessageBox::information(this, "Код отправлен",
                                             "Код подтверждения отправлен на вашу почту!");

                    // Показываем поля для ввода кода
                    ui->codeLabel->show();
                    ui->codeLineEdit->show();
                    ui->confirmCodeButton->show();
                } else {
                    QMessageBox::warning(this, "Ошибка",
                                         "Не удалось отправить код. Проверьте email!");
                }
            }, Qt::UniqueConnection);
}

// КНОПКА "ПОДТВЕРДИТЬ КОД"
void ForgotPassword::on_confirmCodeButton_clicked()
{
    QString code = ui->codeLineEdit->text();

    if (code.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите код подтверждения!");
        return;
    }

    if (code.length() != 6) {
        QMessageBox::warning(this, "Ошибка", "Код должен состоять из 6 цифр!");
        return;
    }

    QMessageBox::information(this, "Успех", "Код подтвержден!");

    // Показываем поля для нового пароля
    ui->newPasswordLabel->show();
    ui->newPasswordLineEdit->show();
    ui->repeatPasswordLabel->show();
    ui->repeatPasswordLineEdit->show();
    ui->changePasswordButton->show();
}

// КНОПКА "СМЕНИТЬ ПАРОЛЬ"
void ForgotPassword::on_changePasswordButton_clicked()
{
    QString code = ui->codeLineEdit->text();
    QString newPass = ui->newPasswordLineEdit->text();
    QString repeatPass = ui->repeatPasswordLineEdit->text();

    if (newPass.isEmpty() || repeatPass.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    // Проверка пароля: минимум 8 символов, только латиница и цифры
    bool validPassword = true;
    if (newPass.length() < 8) {
        validPassword = false;
    } else {
        for (int i = 0; i < newPass.length(); ++i) {
            QChar ch = newPass[i];
            bool isLetter = (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
            bool isDigit = (ch >= '0' && ch <= '9');
            if (!isLetter && !isDigit) {
                validPassword = false;
                break;
            }
        }
    }

    if (!validPassword) {
        QMessageBox::warning(this, "Ошибка",
                             "Пароль должен содержать минимум 8 символов и только латинские буквы и цифры!");
        return;
    }

    if (newPass != repeatPass) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
        return;
    }

    if (!ServiceManager::instance().isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу!");
        return;
    }

    ui->changePasswordButton->setEnabled(false);

    // Отправляем запрос на смену пароля с кодом
    ServiceManager::instance().sendChangePasswordWithCode(m_tempEmail, code, newPass);

    // Обработка ответа сервера
    connect(&ServiceManager::instance(), &ServiceManager::passwordChangeWithCodeResult,
            this, [this](bool success) {
                ui->changePasswordButton->setEnabled(true);

                if (success) {
                    QMessageBox::information(this, "Успех", "Пароль успешно изменен!");
                    emit backRequested();
                    this->hide();
                } else {
                    QMessageBox::warning(this, "Ошибка",
                                         "Неверный код или email! Попробуйте снова.");
                }
            }, Qt::UniqueConnection);
}

// КНОПКА "НАЗАД"
void ForgotPassword::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}