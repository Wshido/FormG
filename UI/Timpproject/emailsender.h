#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

class EmailSender : public QObject
{
    Q_OBJECT
public:
    static EmailSender& instance();

    void sendVerificationCode(const QString& to, const QString& code);
    void sendWelcomeEmail(const QString& to, const QString& username);
    void sendPasswordChangedEmail(const QString& to, const QString& username);

private:
    explicit EmailSender(QObject *parent = nullptr);
    void saveEmailToFile(const QString& to, const QString& subject, const QString& body);
};

#endif // EMAILSENDER_H