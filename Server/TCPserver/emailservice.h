#ifndef EMAILSERVICE_H
#define EMAILSERVICE_H

#include <QSslSocket>
#include <QByteArray>
#include <QString>
#include <QMutex>

class EmailService
{
public:
    EmailService();

    void setSmtpConfig(const QString &host, quint16 port,
                       const QString &username, const QString &password,
                       const QString &fromEmail);

    bool sendEmail(const QString &to, const QString &subject, const QString &body);

private:
    QString m_smtpHost;
    quint16 m_smtpPort;
    QString m_smtpUsername;
    QString m_smtpPassword;
    QString m_fromEmail;
    bool m_configured;
    bool m_sslAvailable;
    mutable QMutex m_mutex;

    bool sendViaSmtp(const QString &to, const QString &subject, const QString &body);
    bool waitForResponse(QSslSocket &socket, int expectedCode = -1);
    QByteArray base64Encode(const QString &str);
    bool checkSslAvailable();
};

#endif // EMAILSERVICE_H
