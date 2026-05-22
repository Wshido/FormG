#include "logintimp.h"
#include "ui_logintimp.h"
#include "databasemanager.h"
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include "registerwindow.h"
#include "forgotpassword.h"

/*!
 * @brief Конструктор окна авторизации.
 * @param parent Родительский виджет.
 */
LoginTimp::LoginTimp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginTimp)
{
    ui->setupUi(this);

    // Настройка параметров окна
    setWindowTitle("Авторизация");
    setFixedSize(420, 420);

    // Инициализация базы данных
    DatabaseManager::instance().initDatabase();

    // Применение пользовательских стилей интерфейса
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

    // Добавление эффекта тени для формы
    QGraphicsDropShadowEffect *shadow =
        new QGraphicsDropShadowEffect(this);

    shadow->setBlurRadius(25);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 80));

    ui->frame->setGraphicsEffect(shadow);
}

/*!
 * @brief Деструктор класса LoginTimp.
 */
LoginTimp::~LoginTimp()
{
    delete ui;
}

/*!
 * @brief Обработчик кнопки входа.
 *
 * Выполняет проверку введенных данных
 * и авторизацию пользователя через базу данных.
 */
void LoginTimp::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Проверка заполнения логина
    if (username.isEmpty()) {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Введите логин!");
        return;
    }

    // Проверка заполнения пароля
    if (password.isEmpty()) {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Введите пароль!");
        return;
    }

    // Проверка данных пользователя
    if (DatabaseManager::instance().loginUser(username, password)) {

        QMessageBox::information(this,
                                 "Успех",
                                 "Вход выполнен успешно!");

        // Закрытие окна с успешным результатом
        accept();

    } else {

        QMessageBox::warning(this,
                             "Ошибка",
                             "Неверный логин или пароль!");
    }
}

/*!
 * @brief Обработчик кнопки возврата.
 *
 * Закрывает окно авторизации.
 */
void LoginTimp::on_backButton_clicked()
{
    reject();
}

/*!
 * @brief Обработчик ссылки восстановления пароля.
 * @param link Текст активированной ссылки.
 */
void LoginTimp::on_forgotLabel_linkActivated(const QString &link)
{
    Q_UNUSED(link);

    // Создание окна восстановления пароля
    ForgotPassword *fp = new ForgotPassword();

    // Отображение окна поверх остальных
    fp->setWindowFlags(
        fp->windowFlags() | Qt::WindowStaysOnTopHint
        );

    // Возврат к окну авторизации
    connect(fp,
            &ForgotPassword::backRequested,
            this,
            [this, fp]() {

                this->show();
                fp->hide();
            });

    fp->show();

    // Скрытие текущего окна
    this->hide();
}

/*!
 * @brief Обработчик кнопки регистрации.
 *
 * Открывает окно регистрации нового пользователя.
 */
void LoginTimp::on_registerButton_clicked()
{
    // Создание окна регистрации
    RegisterWindow *reg = new RegisterWindow();

    // Отображение окна поверх остальных
    reg->setWindowFlags(
        reg->windowFlags() | Qt::WindowStaysOnTopHint
        );

    // Возврат к окну авторизации
    connect(reg,
            &RegisterWindow::backRequested,
            this,
            [this, reg]() {

                this->show();
                reg->hide();
            });

    reg->show();

    // Скрытие текущего окна
    this->hide();
}