#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "servicemanager.h"
#include <QMessageBox>
#include <QRegularExpression>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow)
    , m_remainingSeconds(0)
{
    ui->setupUi(this);

    // По умолчанию кнопка регистрации выключена (пока не получим код)
    ui->createButton->setEnabled(false);
    ui->codeEdit->setEnabled(false);

    // Подключаем сигналы ServiceManager
    connect(&ServiceManager::instance(), &ServiceManager::regRequestCodeResult,
            this, &RegisterWindow::onRegRequestCodeResult);
    connect(&ServiceManager::instance(), &ServiceManager::regConfirmResult,
            this, &RegisterWindow::onRegConfirmResult);

    // Таймер для обратного отсчета
    connect(&m_codeTimer, &QTimer::timeout, [this]() {
        if (m_remainingSeconds > 0) {
            m_remainingSeconds--;
            updateTimerDisplay();
        } else {
            m_codeTimer.stop();
            ui->getCodeButton->setEnabled(true);
            ui->getCodeButton->setText("Получить код");
            ui->codeEdit->setEnabled(false);
            ui->createButton->setEnabled(false);
        }
    });
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::updateTimerDisplay()
{
    ui->getCodeButton->setText(QString("Повторить через %1 сек").arg(m_remainingSeconds));
}

void RegisterWindow::startCodeTimer()
{
    m_remainingSeconds = 60;
    ui->getCodeButton->setEnabled(false);
    m_codeTimer.start(1000);
}

// КНОПКА "ПОЛУЧИТЬ КОД"
void RegisterWindow::on_getCodeButton_clicked()
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

    QString login = ui->loginEdit->text();
    QString pass1 = ui->passwordEdit->text();

    if (login.isEmpty() || login.length() < 3) {
        QMessageBox::warning(this, "Ошибка", "Логин должен содержать не менее 3 символов!");
        return;
    }

    if (pass1.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите пароль!");
        return;
    }

    // Проверка пароля
    QRegularExpression passwordRegex("^[A-Za-z0-9]{8,}$");
    if (!passwordRegex.match(pass1).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Пароль должен содержать минимум 8 символов, только латиница и цифры!");
        return;
    }

    QString pass2 = ui->repeatPasswordEdit->text();
    if (pass1 != pass2) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
        return;
    }

    if (!ServiceManager::instance().isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу!");
        return;
    }

    // Сохраняем данные для второго шага
    m_tempLogin = login;
    m_tempPassword = pass1;
    m_tempEmail = email;

    // Запрашиваем код на email
    ui->getCodeButton->setEnabled(false);
    ui->getCodeButton->setText("Отправка...");
    ServiceManager::instance().sendRegRequestCode(email);
}

void RegisterWindow::onRegRequestCodeResult(bool success, const QString& code)
{
    if (success) {
        m_tempCode = code;
        ui->getCodeButton->setText("Код отправлен!");
        ui->codeEdit->setEnabled(true);
        ui->codeEdit->setFocus();
        ui->createButton->setEnabled(true);

        QMessageBox::information(this, "Код отправлен",
                                 QString("На почту %1 отправлен код подтверждения.\n\n"
                                         "Введите его для завершения регистрации.")
                                     .arg(m_tempEmail));

        startCodeTimer();
    } else {
        ui->getCodeButton->setEnabled(true);
        ui->getCodeButton->setText("Получить код");
        QMessageBox::warning(this, "Ошибка", "Не удалось отправить код. Email уже зарегистрирован или неверный формат!");
    }
}

// КНОПКА "ЗАРЕГИСТРИРОВАТЬСЯ" (createButton)
void RegisterWindow::on_createButton_clicked()
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

    ui->createButton->setEnabled(false);
    ui->createButton->setText("Регистрация...");

    ServiceManager::instance().sendRegConfirm(m_tempLogin, m_tempPassword, m_tempEmail, code);
}

void RegisterWindow::onRegConfirmResult(bool success)
{
    ui->createButton->setEnabled(true);
    ui->createButton->setText("Зарегистрироваться");

    if (success) {
        QMessageBox::information(this, "Успех", "Регистрация завершена успешно!");
        emit backRequested();
        this->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный код подтверждения!");
        ui->codeEdit->clear();
        ui->codeEdit->setFocus();
    }
}

void RegisterWindow::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}