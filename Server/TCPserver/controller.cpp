#include "controller.h"
#include <cmath>
#include <QDebug>

Controller::Controller()
{
}

void Controller::setSmtpConfig(const QString &host, quint16 port,
                               const QString &user, const QString &pass,
                               const QString &from)
{
    m_emailService.setSmtpConfig(host, port, user, pass, from);
}

QStringList Controller::split(const QString &str, QChar delim)
{
    return str.split(delim);
}

double Controller::calculateFunction(double a, double b, double c, double x)
{
    if (x < 0) {
        return sin(a * x);
    } else if (x < 1) {
        if (b * x < 0) return 0;
        return sqrt(b * x);
    } else {
        if (fabs(c * x - 1.0) < 0.0001) {
            return 0;
        }
        return 1.0 / (c * x - 1.0);
    }
}

bool Controller::sendEmail(const QString &to, const QString &subject, const QString &body)
{
    qDebug() << "=== ОТПРАВКА EMAIL ===";
    qDebug() << "Кому:" << to;
    qDebug() << "Тема:" << subject;

    bool sent = m_emailService.sendEmail(to, subject, body);

    if (sent) {
        qDebug() << "=== EMAIL ОТПРАВЛЕН ===";
    } else {
        qDebug() << "=== ОШИБКА ОТПРАВКИ EMAIL ===";
    }
    return sent;
}

// ==================== VALIDATION ====================
bool Controller::validatePassword(const QString &password)
{
    if (password.length() < 8 || password.length() > ServerDB::MAX_PASSWORD_LENGTH) {
        return false;
    }
    for (int i = 0; i < password.length(); ++i) {
        QChar ch = password[i];
        bool isLetter = (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
        bool isDigit = (ch >= '0' && ch <= '9');
        if (!isLetter && !isDigit) {
            return false;
        }
    }
    return true;
}

bool Controller::validateLogin(const QString &login)
{
    return !login.isEmpty() && login.length() >= 3 && login.length() <= ServerDB::MAX_LOGIN_LENGTH;
}

bool Controller::validateEmail(const QString &email)
{
    return !email.isEmpty() && email.length() <= ServerDB::MAX_EMAIL_LENGTH && email.contains('@') && email.contains('.');
}

// ==================== CLIENT DISCONNECT ====================
void Controller::handleClientDisconnect(const QString &login)
{
    if (!login.isEmpty()) {
        qDebug() << "Клиент отключён, деактивация сессии:" << login;
        m_db.logoutSession(login);
    }
}

// ==================== MAIN PROCESS ====================
QString Controller::process(const QString &request)
{
    QStringList parts = split(request, '&');

    if (parts.isEmpty()) return "unknown";

    QString command = parts[0].trimmed();
    QString clientIP = parts.size() > 1 ? parts[parts.size()-1] : "";

    // ========== РЕГИСТРАЦИЯ: ЗАПРОС КОДА ==========
    if (command == "reg_request_code") {
        if (parts.size() >= 2) {
            QString email = parts[1];

            if (!validateEmail(email)) {
                return "reg_request_code-";
            }

            QString code;
            bool ok = m_db.requestRegCode(email, code);
            if (ok) {
                qDebug() << "reg_request_code+ для email:" << email;
                sendEmail(
                    email,
                    "Регистрация — код подтверждения",
                    "Здравствуйте!\n\n"
                    "Вы пытаетесь зарегистрироваться в приложении "
                    "\"Графическое отображение цифровой информации\".\n\n"
                    "Код подтверждения регистрации: " + code + "\n\n"
                    "Код действителен 5 минут.\n\n"
                    "Если вы не регистрировались — проигнорируйте письмо."
                );
                return "reg_request_code+";
            }
            qDebug() << "reg_request_code- (email уже существует)";
            return "reg_request_code-";
        }
        return "reg_request_code-";
    }

    // ========== РЕГИСТРАЦИЯ: ПОДТВЕРЖДЕНИЕ ==========
    if (command == "reg_confirm") {
        if (parts.size() >= 5) {
            QString login = parts[1];
            QString password = parts[2];
            QString email = parts[3];
            QString code = parts[4];

            if (!validateLogin(login)) {
                qDebug() << "reg_confirm- (неверный формат логина)";
                return "reg_confirm-";
            }

            if (!validateEmail(email)) {
                qDebug() << "reg_confirm- (неверный формат email)";
                return "reg_confirm-";
            }

            if (!validatePassword(password)) {
                qDebug() << "reg_confirm- (неверный формат пароля)";
                return "reg_confirm-";
            }

            bool ok = m_db.confirmReg(login, password, email, code);
            if (ok) {
                qDebug() << "reg_confirm+ для" << login;
                sendEmail(
                    email,
                    "Регистрация завершена",
                    "Здравствуйте, " + login + "!\n\n"
                    "Вы успешно зарегистрировались в приложении "
                    "\"Графическое отображение цифровой информации\".\n\n"
                    "Логин: " + login + "\n\n"
                    "Спасибо, что выбрали нас!"
                );
                return "reg_confirm+";
            }
            qDebug() << "reg_confirm- (неверный код или данные)";
            return "reg_confirm-";
        }
        return "reg_confirm-";
    }

    // ========== ВХОД: ЗАПРОС КОДА ==========
    if (command == "auth_request_code") {
        if (parts.size() >= 3) {
            QString login = parts[1];
            QString password = parts[2];

            QString code;
            QString email;
            bool ok = m_db.requestAuthCode(login, password, email, code);
            if (ok) {
                qDebug() << "auth_request_code+ для" << login;
                sendEmail(
                    email,
                    "Вход в приложение — код подтверждения",
                    "Здравствуйте!\n\n"
                    "Вы пытаетесь войти в приложение "
                    "\"Графическое отображение цифровой информации\" "
                    "с логином: " + login + "\n\n"
                    "Код подтверждения входа: " + code + "\n\n"
                    "Код действителен 5 минут.\n\n"
                    "Если вы не пытались войти — немедленно смените пароль."
                );
                return "auth_request_code+&" + email;
            }
            qDebug() << "auth_request_code- (неверный логин или пароль)";
            return "auth_request_code-";
        }
        return "auth_request_code-";
    }

    // ========== ВХОД: ПОДТВЕРЖДЕНИЕ ==========
    if (command == "auth_confirm") {
        if (parts.size() >= 3) {
            QString email = parts[1];
            QString code = parts[2];
            QString sessionToken;
            bool ok = m_db.confirmAuth(email, code, sessionToken);
            if (ok) {
                qDebug() << "auth_confirm+";
                sendEmail(
                    email,
                    "Вход в приложение выполнен",
                    "Здравствуйте!\n\n"
                    "Вход в приложение выполнен успешно.\n\n"
                    "Если это были не вы — свяжитесь с поддержкой."
                );
                return "auth_confirm+&" + sessionToken;
            }
            qDebug() << "auth_confirm- (неверный код)";
            return "auth_confirm-";
        }
        return "auth_confirm-";
    }

    // ========== СБРОС ПАРОЛЯ: ЗАПРОС КОДА ==========
    if (command == "reset_request_code") {
        if (parts.size() >= 2) {
            QString loginOrEmail = parts[1];
            QString code;
            QString email;
            bool ok = m_db.requestResetCode(loginOrEmail, code, email);
            if (ok) {
                qDebug() << "reset_request_code+ для" << loginOrEmail;
                sendEmail(
                    email,
                    "Сброс пароля — код подтверждения",
                    "Здравствуйте!\n\n"
                    "Вы запросили сброс пароля для аккаунта.\n\n"
                    "Код подтверждения сброса: " + code + "\n\n"
                    "Код действителен 5 минут.\n\n"
                    "Если вы не запрашивали сброс — проигнорируйте письмо."
                );
                return "reset_request_code+";
            }
            qDebug() << "reset_request_code- (пользователь не найден)";
            return "reset_request_code-";
        }
        return "reset_request_code-";
    }

    // ========== СБРОС ПАРОЛЯ: ПОДТВЕРЖДЕНИЕ ==========
    if (command == "reset_confirm") {
        if (parts.size() >= 4) {
            QString loginOrEmail = parts[1];
            QString code = parts[2];
            QString newPassword = parts[3];

            if (!validatePassword(newPassword)) {
                qDebug() << "reset_confirm- (неверный формат пароля)";
                return "reset_confirm-";
            }

            bool ok = m_db.confirmResetPassword(loginOrEmail, code, newPassword);
            if (ok) {
                qDebug() << "reset_confirm+";
                QString email = m_db.getEmailByLoginOrEmail(loginOrEmail);
                if (!email.isEmpty()) {
                    sendEmail(
                        email,
                        "Пароль успешно изменён",
                        "Здравствуйте!\n\n"
                        "Ваш пароль был успешно изменён.\n\n"
                        "Если это были не вы — немедленно свяжитесь с поддержкой."
                    );
                }
                return "reset_confirm+";
            }
            qDebug() << "reset_confirm- (неверный код)";
            return "reset_confirm-";
        }
        return "reset_confirm-";
    }

    // ========== ПРОВЕРКА СЕССИИ ==========
    if (command == "checksession") {
        if (parts.size() >= 3) {
            bool ok = m_db.checkSession(parts[1], parts[2]);
            if (ok) {
                qDebug() << "checksession+";
                return "checksession+";
            }
            qDebug() << "checksession-";
            return "checksession-";
        }
        return "checksession-";
    }

    // ========== ОБНОВЛЕНИЕ ТОКЕНА ==========
    if (command == "refresh_token") {
        if (parts.size() >= 3) {
            QString login = parts[1];
            QString oldToken = parts[2];
            QString newToken;
            bool ok = m_db.refreshToken(login, oldToken, newToken);
            if (ok) {
                qDebug() << "refresh_token+ для" << login;
                return "refresh_token+&" + newToken;
            }
            qDebug() << "refresh_token-";
            return "refresh_token-";
        }
        return "refresh_token-";
    }

    // ========== LOGOUT ==========
    if (command == "logout") {
        if (parts.size() >= 2) {
            QString login = parts[1];
            m_db.logoutSession(login);
            qDebug() << "logout+ для" << login;
            return "logout+";
        }
        return "logout-";
    }

    // ========== LOGOUT ALL ==========
    if (command == "logout_all") {
        if (parts.size() >= 2) {
            QString login = parts[1];
            m_db.logoutAllSessions(login);
            qDebug() << "logout_all+ для" << login;
            return "logout_all+";
        }
        return "logout_all-";
    }

    // ========== СТАТИСТИКА ==========
    if (command == "stat") {
        if (parts.size() >= 2) {
            return m_db.getStat(parts[1]);
        }
        return "stat&0&0&0";
    }

    // ========== ПРОВЕРКА ЗАДАНИЯ ==========
    if (command == "check") {
        if (parts.size() >= 4) {
            bool ok = checkTask(parts[1].toInt(), parts[2].toInt(), parts[3].toInt());
            if (ok) {
                qDebug() << "check+";
                return "check+";
            }
            qDebug() << "check-";
            return "check-";
        }
        return "check-";
    }

    return "unknown";
}

bool Controller::checkTask(int task, int variant, int answer)
{
    if (task == 1 && variant == 15 && answer == 42) {
        return true;
    }
    return false;
}
