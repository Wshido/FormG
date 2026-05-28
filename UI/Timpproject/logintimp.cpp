#include "logintimp.h"
#include "ui_logintimp.h"
#include "servicemanager.h"
#include "registerwindow.h"
#include "forgotpassword.h"
#include <QMessageBox>

LoginTimp::LoginTimp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginTimp)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");
    setFixedSize(420, 420);

    // Подключаемся к серверу одногруппника
    ServiceManager::instance().connectToServer("127.0.0.1", 11999);

    connect(&ServiceManager::instance(), &ServiceManager::codeRequestResult,
            this, [this](bool success) {
                // Можно добавить логирование или уведомление
                qDebug() << "Code request result:" << success;
            });

    connect(&ServiceManager::instance(), &ServiceManager::passwordChangeWithCodeResult,
            this, [this](bool success) {
                qDebug() << "Password change with code result:" << success;
            });

    // Подключаем сигналы
    connect(&ServiceManager::instance(), &ServiceManager::authResult,
            this, &LoginTimp::onAuthResult);
    connect(&ServiceManager::instance(), &ServiceManager::error,
            this, [this](const QString& error) {
                QMessageBox::warning(this, "Ошибка сервера", error);
            });
}

LoginTimp::~LoginTimp()
{
    delete ui;
}

void LoginTimp::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    if (!ServiceManager::instance().isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу!");
        return;
    }

    ui->loginButton->setEnabled(false);
    ServiceManager::instance().sendAuth(username, password);
}

void LoginTimp::onAuthResult(bool success, const QString& login)
{
    ui->loginButton->setEnabled(true);
    Q_UNUSED(login);

    if (success) {
        QMessageBox::information(this, "Успех", "Вход выполнен успешно!");
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
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
    fp->setAttribute(Qt::WA_DeleteOnClose);
    fp->setWindowFlags(fp->windowFlags() | Qt::WindowStaysOnTopHint);
    connect(fp, &ForgotPassword::backRequested, this, [this, fp]() {
        this->show();
        fp->close();
    });
    fp->show();
    this->hide();
}

void LoginTimp::on_registerButton_clicked()
{
    RegisterWindow *reg = new RegisterWindow();
    reg->setAttribute(Qt::WA_DeleteOnClose);
    reg->setWindowFlags(reg->windowFlags() | Qt::WindowStaysOnTopHint);
    connect(reg, &RegisterWindow::backRequested, this, [this, reg]() {
        this->show();
        reg->close();
    });
    reg->show();
    this->hide();
}