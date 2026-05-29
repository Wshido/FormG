#include "emailsender.h"
#include <QDebug>
#include <cctype>

EmailSender& EmailSender::instance()
{
    static EmailSender instance;
    return instance;
}

EmailSender::EmailSender(QObject *parent)
    : QObject(parent)
    , m_smtpPort(587)
    , m_configured(false)
    , m_sslAvailable(false)
{
    m_sslAvailable = QSslSocket::supportsSsl();
    if (!m_sslAvailable) {
        qDebug() << "EmailSender: SSL not available. Emails will not be sent.";
    }
}

bool EmailSender::isSslAvailable() const
{
    return m_sslAvailable;
}

void EmailSender::setSmtpConfig(const QString &host, quint16 port,
                                 const QString &username, const QString &password,
                                 const QString &fromEmail)
{
    m_smtpHost = host;
    m_smtpPort = port;
    m_smtpUsername = username;
    m_smtpPassword = password;
    m_fromEmail = fromEmail;
    m_configured = !host.isEmpty();
}

QByteArray EmailSender::base64Encode(const QString &str)
{
    return str.toUtf8().toBase64();
}

bool EmailSender::waitForResponse(QSslSocket &socket, int expectedCode)
{
    QByteArray response;

    while (true) {
        if (!socket.waitForReadyRead(15000)) {
            qDebug() << "EmailSender: Timeout";
            return false;
        }

        response += socket.readAll();

        QList<QByteArray> lines = response.split('\n');
        for (const QByteArray &line : lines) {
            QByteArray trimmed = line.trimmed();
            if (trimmed.length() >= 4 &&
                std::isdigit(static_cast<unsigned char>(trimmed[0])) &&
                std::isdigit(static_cast<unsigned char>(trimmed[1])) &&
                std::isdigit(static_cast<unsigned char>(trimmed[2])) &&
                trimmed[3] == ' ') {
                qDebug() << "SMTP <<" << trimmed;

                if (expectedCode != -1) {
                    int code = trimmed.left(3).toInt();
                    if (code != expectedCode) {
                        qDebug() << "EmailSender: Expected" << expectedCode << "got" << code;
                        return false;
                    }
                }
                return true;
            }
        }
    }
}

bool EmailSender::sendEmail(const QString &to, const QString &subject, const QString &body)
{
    if (!m_configured) {
        qDebug() << "EmailSender: Not configured, skipping email to" << to;
        return false;
    }

    if (!m_sslAvailable) {
        qDebug() << "EmailSender: SSL not available, skipping email to" << to;
        return false;
    }

    return sendViaSmtp(to, subject, body);
}

bool EmailSender::sendViaSmtp(const QString &to, const QString &subject, const QString &body)
{
    QSslSocket socket;

    qDebug() << "EmailSender: Connecting to" << m_smtpHost << ":" << m_smtpPort;
    // Порт 465 = прямой SSL
    socket.connectToHostEncrypted(m_smtpHost, m_smtpPort);
    if (!socket.waitForEncrypted(20000)) {
        qDebug() << "EmailSender: SSL failed:" << socket.errorString();
        socket.disconnectFromHost();
        return false;
    }

    if (!waitForResponse(socket, 220)) {
        socket.disconnectFromHost();
        return false;
    }

    socket.write("EHLO localhost\r\n");
    if (!waitForResponse(socket, 250)) {
        socket.disconnectFromHost();
        return false;
    }

    socket.write("AUTH LOGIN\r\n");
    if (!waitForResponse(socket, 334)) {
        socket.disconnectFromHost();
        return false;
    }

    socket.write(base64Encode(m_smtpUsername) + "\r\n");
    if (!waitForResponse(socket, 334)) {
        socket.disconnectFromHost();
        return false;
    }

    socket.write(base64Encode(m_smtpPassword) + "\r\n");
    if (!waitForResponse(socket, 235)) {
        qDebug() << "EmailSender: Auth failed";
        socket.disconnectFromHost();
        return false;
    }

    socket.write("MAIL FROM:<" + m_fromEmail.toUtf8() + ">\r\n");
    if (!waitForResponse(socket, 250)) {
        socket.disconnectFromHost();
        return false;
    }

    socket.write("RCPT TO:<" + to.toUtf8() + ">\r\n");
    if (!waitForResponse(socket, 250)) {
        socket.disconnectFromHost();
        return false;
    }

    socket.write("DATA\r\n");
    if (!waitForResponse(socket, 354)) {
        socket.disconnectFromHost();
        return false;
    }

    QByteArray message;
    message += "From: =?UTF-8?B?" + base64Encode(m_fromEmail) + "?= <" + m_fromEmail.toUtf8() + ">\r\n";
    message += "To: " + to.toUtf8() + "\r\n";
    message += "Subject: =?UTF-8?B?" + base64Encode(subject) + "?=\r\n";
    message += "MIME-Version: 1.0\r\n";
    message += "Content-Type: text/plain; charset=UTF-8\r\n";
    message += "Content-Transfer-Encoding: base64\r\n";
    message += "\r\n";
    message += base64Encode(body) + "\r\n";
    message += ".\r\n";

    socket.write(message);
    if (!waitForResponse(socket, 250)) {
        socket.disconnectFromHost();
        return false;
    }

    socket.write("QUIT\r\n");
    waitForResponse(socket, 221);

    socket.disconnectFromHost();
    qDebug() << "EmailSender: Email sent to" << to;
    return true;
}

bool EmailSender::sendVerificationCode(const QString &to, const QString &code)
{
    QString subject = "Код подтверждения";
    QString body = QString(
        "Здравствуйте!\n\n"
        "Ваш код подтверждения: %1\n\n"
        "Код действителен в течение 5 минут.\n\n"
        "Если вы не запрашивали этот код, проигнорируйте данное письмо."
    ).arg(code);

    return sendEmail(to, subject, body);
}

bool EmailSender::sendWelcomeEmail(const QString &to, const QString &username)
{
    QString subject = "Добро пожаловать!";
    QString body = QString(
        "Здравствуйте, %1!\n\n"
        "Вы успешно зарегистрировались в приложении.\n\n"
        "Спасибо, что выбрали нас!"
    ).arg(username);

    return sendEmail(to, subject, body);
}

bool EmailSender::sendPasswordChangedEmail(const QString &to, const QString &username)
{
    QString subject = "Пароль изменён";
    QString body = QString(
        "Здравствуйте, %1!\n\n"
        "Ваш пароль был успешно изменён.\n\n"
        "Если это были не вы, немедленно свяжитесь с поддержкой."
    ).arg(username);

    return sendEmail(to, subject, body);
}
