#include "emailservice.h"
#include <QDebug>
#include <cctype>

EmailService::EmailService()
    : m_smtpPort(465)
    , m_configured(false)
    , m_sslAvailable(true)
{
    m_sslAvailable = QSslSocket::supportsSsl();
    qDebug() << "EmailService: SSL доступен:" << m_sslAvailable;
    if (!m_sslAvailable) {
        qDebug() << "EmailService: OpenSSL НЕ найден! Письма не будут отправляться.";
        qDebug() << "EmailService: Скопируйте libssl-1_1-x64.dll и libcrypto-1_1-x64.dll рядом с exe.";
    }
}

bool EmailService::checkSslAvailable()
{
    return QSslSocket::supportsSsl();
}

void EmailService::setSmtpConfig(const QString &host, quint16 port,
                                 const QString &username, const QString &password,
                                 const QString &fromEmail)
{
    QMutexLocker locker(&m_mutex);
    m_smtpHost = host;
    m_smtpPort = port;
    m_smtpUsername = username;
    m_smtpPassword = password;
    m_fromEmail = fromEmail;
    m_configured = !host.isEmpty();
    qDebug() << "EmailService: SMTP настроен:" << host << ":" << port;
}

QByteArray EmailService::base64Encode(const QString &str)
{
    return str.toUtf8().toBase64();
}

bool EmailService::waitForResponse(QSslSocket &socket, int expectedCode)
{
    QByteArray response;

    while (true) {
        if (!socket.waitForReadyRead(20000)) {
            qDebug() << "SMTP: Timeout waiting for response";
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
                        qDebug() << "SMTP: Expected" << expectedCode << "but got" << code;
                        return false;
                    }
                }
                return true;
            }
        }
    }
}

bool EmailService::sendEmail(const QString &to, const QString &subject, const QString &body)
{
    QMutexLocker locker(&m_mutex);

    if (!m_configured) {
        qDebug() << "EmailService: SMTP не настроен, письмо НЕ отправлено на" << to;
        return false;
    }

    if (!m_sslAvailable) {
        qDebug() << "EmailService: SSL недоступен, письмо НЕ отправлено на" << to;
        return false;
    }

    locker.unlock();
    bool result = sendViaSmtp(to, subject, body);
    return result;
}

bool EmailService::sendViaSmtp(const QString &to, const QString &subject, const QString &body)
{
    QSslSocket socket;

    qDebug() << "SMTP: Подключение к" << m_smtpHost << ":" << m_smtpPort;

    // Порт 465 = прямой SSL. Сначала шифруем, потом общаемся.
    socket.connectToHostEncrypted(m_smtpHost, m_smtpPort);
    if (!socket.waitForEncrypted(20000)) {
        qDebug() << "SMTP: SSL handshake failed:" << socket.errorString();
        qDebug() << "SMTP: Проверьте что libssl-1_1-x64.dll рядом с exe!";
        socket.disconnectFromHost();
        return false;
    }

    qDebug() << "SMTP: SSL соединение установлено";

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
        qDebug() << "SMTP: Аутентификация провалилась! Проверьте логин/пароль.";
        socket.disconnectFromHost();
        return false;
    }

    qDebug() << "SMTP: Аутентификация успешна";

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

    qDebug() << "SMTP: === ПИСЬМО УСПЕШНО ОТПРАВЛЕНО на" << to << "===";
    return true;
}
