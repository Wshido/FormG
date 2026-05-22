#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QDebug>

/*!
 * @brief Конструктор окна регистрации.
 * @param parent Родительский виджет.
 */
RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    // Инициализация пользовательского интерфейса
    ui->setupUi(this);
}

/*!
 * @brief Деструктор класса RegisterWindow.
 */
RegisterWindow::~RegisterWindow()
{
    delete ui;
}

/*!
 * @brief Обработчик кнопки создания аккаунта.
 *
 * Выполняет проверку введенных данных
 * и регистрацию нового пользователя в базе данных.
 */
void RegisterWindow::on_createButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString email = ui->emailEdit->text();
    QString pass1 = ui->passwordEdit->text();
    QString pass2 = ui->repeatPasswordEdit->text();

    qDebug() << "=== РЕГИСТРАЦИЯ ===";
    qDebug() << "Логин:" << login;
    qDebug() << "Email:" << email;

    // Проверка заполнения полей
    if (login.isEmpty() ||
        email.isEmpty() ||
        pass1.isEmpty()) {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните все поля!");
        return;
    }

    // Проверка длины логина
    if (login.length() < 3) {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Логин должен содержать "
                             "не менее 3 символов!");
        return;
    }

    // Проверка длины пароля
    if (pass1.length() < 4) {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Пароль должен содержать "
                             "не менее 4 символов!");
        return;
    }

    // Проверка корректности email
    if (!email.contains('@') ||
        !email.contains('.')) {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Введите корректный email!");
        return;
    }

    // Проверка совпадения паролей
    if (pass1 != pass2) {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Пароли не совпадают!");
        return;
    }

    // Регистрация пользователя в базе данных
    if (DatabaseManager::instance()
            .registerUser(login, email, pass1)) {

        QMessageBox::information(this,
                                 "Успех",
                                 "Регистрация завершена успешно!");

        // Очистка полей ввода
        ui->loginEdit->clear();
        ui->emailEdit->clear();
        ui->passwordEdit->clear();
        ui->repeatPasswordEdit->clear();

        // Возврат к предыдущему окну
        emit backRequested();

        // Скрытие текущего окна
        this->hide();

    } else {

        // Проверка существования логина
        if (DatabaseManager::instance().userExists(login)) {

            QMessageBox::warning(
                this,
                "Ошибка",
                "Пользователь с таким логином уже существует!"
                );

            // Проверка существования email
        } else if (DatabaseManager::instance()
                       .emailExists(email)) {

            QMessageBox::warning(
                this,
                "Ошибка",
                "Пользователь с таким email "
                "уже зарегистрирован!"
                );

        } else {

            QMessageBox::warning(
                this,
                "Ошибка",
                "Не удалось зарегистрировать пользователя!\n"
                "Проверьте права доступа к папке программы."
                );
        }
    }
}

/*!
 * @brief Обработчик кнопки возврата.
 *
 * Выполняет возврат к предыдущему окну.
 */
void RegisterWindow::on_backButton_clicked()
{
    emit backRequested();

    // Скрытие текущего окна
    this->hide();
}