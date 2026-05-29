#include "logintimp.h"
#include "ui_logintimp.h"
#include "servicemanager.h"
#include "emailsender.h"
#include "registerwindow.h"
#include "forgotpassword.h"
#include <QMessageBox>

LoginTimp::LoginTimp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginTimp)
    , m_remainingSeconds(0)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");
    setFixedSize(440, 560);

    // Подключаемся к серверу
    ServiceManager::instance().connectToServer("127.0.0.1", 11999);

    // Подключаем сигналы для двухфакторной авторизации
    connect(&ServiceManager::instance(), &ServiceManager::authRequestCodeResult,
            this, &LoginTimp::onAuthRequestCodeResult);
    connect(&ServiceManager::instance(), &ServiceManager::authConfirmResult,
            this, &LoginTimp::onAuthConfirmResult);

    // Изначально показываем поля логина/пароля, скрываем поля для кода
    ui->codeEdit->setVisible(false);
    ui->confirmCodeButton->setVisible(false);
    ui->codeLabel->setVisible(false);
    ui->timerLabel->setVisible(false);

    // Таймер для обратного отсчета
    connect(&m_codeTimer, &QTimer::timeout, [this]() {
        if (m_remainingSeconds > 0) {
            m_remainingSeconds--;
            updateTimerDisplay();
        } else {
            m_codeTimer.stop();
            ui->timerLabel->setVisible(false);
            ui->codeEdit->setEnabled(false);
            ui->confirmCodeButton->setEnabled(false);
            ui->loginButton->setEnabled(true);
            ui->loginButton->setText("Войти");
        }
    });
}

LoginTimp::~LoginTimp()
{
    delete ui;
}

void LoginTimp::updateTimerDisplay()
{
    ui->timerLabel->setText(QString("Код действителен: %1 сек").arg(m_remainingSeconds));
    ui->timerLabel->setVisible(true);
}

void LoginTimp::startCodeTimer()
{
    m_remainingSeconds = 300; // 5 минут = 300 секунд
    ui->confirmCodeButton->setEnabled(true);
    ui->codeEdit->setEnabled(true);
    m_codeTimer.start(1000);
}

// ШАГ 1: Ввод логина и пароля
void LoginTimp::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    if (password.length() < 8) {
        QMessageBox::warning(this, "Ошибка", "Пароль должен содержать минимум 8 символов!");
        return;
    }

    if (!ServiceManager::instance().isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу!");
        return;
    }

    ui->loginButton->setEnabled(false);
    ui->loginButton->setText("Проверка...");

    // Запрашиваем код на почту
    ServiceManager::instance().sendAuthRequestCode(username, password);
}

void LoginTimp::onAuthRequestCodeResult(bool success, const QString& email, const QString& /*code*/)
{
    ui->loginButton->setEnabled(true);
    ui->loginButton->setText("Войти");

    if (success) {
        m_tempEmail = email;

        // Показываем поля для ввода кода
        ui->codeLabel->setVisible(true);
        ui->codeEdit->setVisible(true);
        ui->confirmCodeButton->setVisible(true);
        ui->codeEdit->clear();
        ui->codeEdit->setFocus();

        // Скрываем поля логина/пароля во время ввода кода
        ui->usernameLineEdit->setEnabled(false);
        ui->passwordLineEdit->setEnabled(false);
        ui->loginButton->setVisible(false);

        // Запускаем таймер
        startCodeTimer();

        QMessageBox::information(this, "Код отправлен",
                                 QString("На почту %1 отправлен код подтверждения.\n\n"
                                         "Проверьте почту и введите код для входа.")
                                     .arg(email));
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}

// ШАГ 2: Подтверждение кода
void LoginTimp::on_confirmCodeButton_clicked()
{
    QString code = ui->codeEdit->text();

    if (code.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите код подтверждения!");
        return;
    }

    if (code.length() != 6) {
        QMessageBox::warning(this, "Ошибка", "Код должен состоять из 6 цифр!");
        return;
    }

    ui->confirmCodeButton->setEnabled(false);
    ui->confirmCodeButton->setText("Проверка...");

    ServiceManager::instance().sendAuthConfirm(m_tempEmail, code);
}

void LoginTimp::onAuthConfirmResult(bool success, const QString& /*sessionToken*/)
{
    ui->confirmCodeButton->setEnabled(true);
    ui->confirmCodeButton->setText("Подтвердить");
    m_codeTimer.stop();

    if (success) {
        QMessageBox::information(this, "Успех", "Вход выполнен успешно!");
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный код подтверждения!");
        ui->codeEdit->clear();
        ui->codeEdit->setFocus();
        // Продолжаем таймер, можно попробовать снова
        ui->confirmCodeButton->setEnabled(true);
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
    connect(reg, &RegisterWindow::backRequested, this, [this, reg]() {
        this->show();
        reg->close();
    });
    reg->show();
    this->hide();
}