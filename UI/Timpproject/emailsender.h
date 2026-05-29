#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QObject>
#include <QSslSocket>
#include <QByteArray>

class EmailSender : public QObject
{
    Q_OBJECT
public:
    static EmailSender& instance();

    void setSmtpConfig(const QString &host, quint16 port,
                       const QString &username, const QString &password,
                       const QString &fromEmail);

    bool sendVerificationCode(const QString &to, const QString &code);
    bool sendWelcomeEmail(const QString &to, const QString &username);
    bool sendPasswordChangedEmail(const QString &to, const QString &username);
    bool isSslAvailable() const;

private:
    explicit EmailSender(QObject *parent = nullptr);

    QString m_smtpHost;
    quint16 m_smtpPort;
    QString m_smtpUsername;
    QString m_smtpPassword;
    QString m_fromEmail;
    bool m_configured;
    bool m_sslAvailable;

    bool sendEmail(const QString &to, const QString &subject, const QString &body);
    bool sendViaSmtp(const QString &to, const QString &subject, const QString &body);
    bool waitForResponse(QSslSocket &socket, int expectedCode = -1);
    QByteArray base64Encode(const QString &str);
};

#endif // EMAILSENDER_H
