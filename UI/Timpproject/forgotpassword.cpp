#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "servicemanager.h"
#include <QMessageBox>

ForgotPassword::ForgotPassword(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ForgotPassword)
    , m_remainingSeconds(0)
{
    ui->setupUi(this);

    // Изначально показываем только поле для логина и кнопку отправки
    ui->loginEdit->setVisible(true);
    ui->sendButton->setVisible(true);

    // Скрываем поля для кода и пароля
    ui->codeLabel->setVisible(false);
    ui->codeEdit->setVisible(false);
    ui->confirmCodeButton->setVisible(false);
    ui->timerLabel->setVisible(false);
    ui->newPasswordLabel->setVisible(false);
    ui->newPasswordLineEdit->setVisible(false);
    ui->repeatPasswordLabel->setVisible(false);
    ui->repeatPasswordLineEdit->setVisible(false);
    ui->changePasswordButton->setVisible(false);

    // Подключаем сигналы
    connect(&ServiceManager::instance(), &ServiceManager::codeRequestResult,
            this, &ForgotPassword::onCodeRequestResult);
    connect(&ServiceManager::instance(), &ServiceManager::passwordChangeWithCodeResult,
            this, &ForgotPassword::onPasswordChangeResult);

    // Таймер для обратного отсчета
    connect(&m_codeTimer, &QTimer::timeout, [this]() {
        if (m_remainingSeconds > 0) {
            m_remainingSeconds--;
            updateTimerDisplay();
        } else {
            m_codeTimer.stop();
            ui->timerLabel->setVisible(false);
            ui->confirmCodeButton->setEnabled(false);
            ui->codeEdit->setEnabled(false);
        }
    });
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::updateTimerDisplay()
{
    ui->timerLabel->setText(QString("Код действителен: %1 сек").arg(m_remainingSeconds));
}

void ForgotPassword::startCodeTimer()
{
    m_remainingSeconds = 300; // 5 минут
    ui->confirmCodeButton->setEnabled(true);
    ui->codeEdit->setEnabled(true);
    ui->timerLabel->setVisible(true);
    m_codeTimer.start(1000);
}

void ForgotPassword::showCodeInputStep()
{
    // Скрываем поле логина и кнопку отправки
    ui->loginEdit->setVisible(false);
    ui->sendButton->setVisible(false);

    // Показываем поля для кода
    ui->codeLabel->setVisible(true);
    ui->codeEdit->setVisible(true);
    ui->confirmCodeButton->setVisible(true);
    ui->codeEdit->clear();
    ui->codeEdit->setFocus();

    // Запускаем таймер
    startCodeTimer();
}

void ForgotPassword::showPasswordChangeStep()
{
    // Скрываем поля для кода
    ui->codeLabel->setVisible(false);
    ui->codeEdit->setVisible(false);
    ui->confirmCodeButton->setVisible(false);
    ui->timerLabel->setVisible(false);

    // Показываем поля для нового пароля
    ui->newPasswordLabel->setVisible(true);
    ui->newPasswordLineEdit->setVisible(true);
    ui->repeatPasswordLabel->setVisible(true);
    ui->repeatPasswordLineEdit->setVisible(true);
    ui->changePasswordButton->setVisible(true);
    ui->newPasswordLineEdit->setFocus();
}

// ШАГ 1: Запрос кода по логину
void ForgotPassword::on_sendButton_clicked()
{
    QString login = ui->loginEdit->text();

    if (login.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин!");
        return;
    }

    if (!ServiceManager::instance().isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу!");
        return;
    }

    m_tempLogin = login;

    ui->sendButton->setEnabled(false);
    ui->sendButton->setText("Отправка...");

    // Запрашиваем код у сервера (сервер найдет email по логину)
    ServiceManager::instance().sendRequestCode(login);
}

void ForgotPassword::onCodeRequestResult(bool success)
{
    ui->sendButton->setEnabled(true);
    ui->sendButton->setText("Отправить код");

    if (success) {
        QMessageBox::information(this, "Код отправлен",
                                 QString("На почту, привязанную к логину \"%1\", отправлен код подтверждения.\n\nКод действителен 5 минут.\n\nВведите его для сброса пароля.")
                                     .arg(m_tempLogin));

        showCodeInputStep();
    } else {
        QMessageBox::warning(this, "Ошибка",
                             "Пользователь с таким логином не найден!");
    }
}

// ШАГ 2: Подтверждение кода
void ForgotPassword::on_confirmCodeButton_clicked()
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

    m_tempCode = code;

    // Переходим к смене пароля
    showPasswordChangeStep();
}

// ШАГ 3: Смена пароля
void ForgotPassword::on_changePasswordButton_clicked()
{
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
    ui->changePasswordButton->setText("Смена пароля...");

    // Отправляем запрос на смену пароля (передаем логин, код и новый пароль)
    ServiceManager::instance().sendChangePasswordWithCode(m_tempLogin, m_tempCode, newPass);
}

void ForgotPassword::onPasswordChangeResult(bool success)
{
    ui->changePasswordButton->setEnabled(true);
    ui->changePasswordButton->setText("Сменить пароль");

    if (success) {
        QMessageBox::information(this, "Успех", "Пароль успешно изменен!");
        emit backRequested();
        this->hide();
    } else {
        QMessageBox::warning(this, "Ошибка",
                             "Неверный код подтверждения! Попробуйте запросить код заново.");
        // Возвращаемся к первому шагу
        ui->loginEdit->setVisible(true);
        ui->sendButton->setVisible(true);
        ui->loginEdit->clear();
        ui->sendButton->setEnabled(true);
        ui->codeLabel->setVisible(false);
        ui->codeEdit->setVisible(false);
        ui->confirmCodeButton->setVisible(false);
        ui->timerLabel->setVisible(false);
        ui->newPasswordLabel->setVisible(false);
        ui->newPasswordLineEdit->setVisible(false);
        ui->repeatPasswordLabel->setVisible(false);
        ui->repeatPasswordLineEdit->setVisible(false);
        ui->changePasswordButton->setVisible(false);
    }
}

void ForgotPassword::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}