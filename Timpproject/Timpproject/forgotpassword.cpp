#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QMessageBox>
#include "databasemanager.h"
#include <QRandomGenerator>  // генератор случайного кода

// Временное хранение кода подтверждения
static QString g_tempCode;

/*!
 * @brief Конструктор окна ForgotPassword.
 * @param parent Родительский виджет.
 */
ForgotPassword::ForgotPassword(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);

    // Скрываем элементы ввода кода подтверждения
    ui->codeLabel->hide();
    ui->codeLineEdit->hide();
    ui->confirmCodeButton->hide();

    // Скрываем элементы смены пароля
    ui->newPasswordLabel->hide();
    ui->newPasswordLineEdit->hide();

    ui->repeatPasswordLabel->hide();
    ui->repeatPasswordLineEdit->hide();

    ui->changePasswordButton->hide();
}

/*!
 * @brief Деструктор класса ForgotPassword.
 */
ForgotPassword::~ForgotPassword()
{
    delete ui;
}

/*!
 * @brief Обработчик отправки кода подтверждения.
 *
 * Проверяет существование пользователя
 * и генерирует временный код подтверждения.
 */
void ForgotPassword::on_sendButton_clicked()
{
    QString login = ui->emailEdit->text();

    // Проверка заполнения поля логина
    if (login.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин!");
        return;
    }

    // Проверка существования пользователя
    if (!DatabaseManager::instance().userExists(login)) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Пользователь с таким логином не найден!");
        return;
    }

    // Генерация случайного кода подтверждения
    g_tempCode = QString::number(
        QRandomGenerator::global()->bounded(1000, 9999)
        );

    // Вывод сообщения с кодом
    QMessageBox::information(
        this,
        "Код отправлен",
        QString("Код подтверждения: %1\n"
                "(В реальном приложении код отправляется на email)")
            .arg(g_tempCode)
        );

    // Отображение элементов подтверждения кода
    ui->codeLabel->show();
    ui->codeLineEdit->show();
    ui->confirmCodeButton->show();
}

/*!
 * @brief Обработчик подтверждения кода.
 *
 * Проверяет введенный код и открывает
 * форму смены пароля.
 */
void ForgotPassword::on_confirmCodeButton_clicked()
{
    QString code = ui->codeLineEdit->text();

    // Проверка правильности кода
    if (code != g_tempCode) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Неверный код!");
        return;
    }

    QMessageBox::information(this,
                             "Успех",
                             "Код подтвержден!");

    // Отображение полей нового пароля
    ui->newPasswordLabel->show();
    ui->newPasswordLineEdit->show();

    ui->repeatPasswordLabel->show();
    ui->repeatPasswordLineEdit->show();

    ui->changePasswordButton->show();
}

/*!
 * @brief Обработчик смены пароля.
 *
 * Проверяет корректность введенных паролей
 * и обновляет пароль пользователя в базе данных.
 */
void ForgotPassword::on_changePasswordButton_clicked()
{
    QString login = ui->emailEdit->text();
    QString pass1 = ui->newPasswordLineEdit->text();
    QString pass2 = ui->repeatPasswordLineEdit->text();

    // Проверка заполнения полей
    if (pass1.isEmpty() || pass2.isEmpty()) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните все поля!");
        return;
    }

    // Проверка совпадения паролей
    if (pass1 != pass2) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Пароли не совпадают!");
        return;
    }

    // Изменение пароля в базе данных
    if (DatabaseManager::instance().changePassword(login, pass1)) {

        QMessageBox::information(this,
                                 "Успех",
                                 "Пароль успешно изменен!");

        // Возврат к предыдущему окну
        emit backRequested();
        this->hide();

    } else {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Не удалось изменить пароль!");
    }
}

/*!
 * @brief Обработчик кнопки возврата.
 *
 * Возвращает пользователя к предыдущему окну.
 */
void ForgotPassword::on_backButton_clicked()
{
    emit backRequested();

    // Скрытие текущего окна
    this->hide();
}