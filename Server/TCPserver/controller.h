#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <QMap>
#include "serverdb.h"
#include "emailservice.h"

class Controller
{
public:
    Controller();

    QString process(const QString &request);
    double calculateFunction(double a, double b, double c, double x);
    void setSmtpConfig(const QString &host, quint16 port,
                       const QString &user, const QString &pass,
                       const QString &from);

    void handleClientDisconnect(const QString &login);

private:
    ServerDB m_db;
    EmailService m_emailService;

    bool checkTask(int task, int variant, int answer);
    QStringList split(const QString &str, QChar delim);
    bool sendEmail(const QString &to, const QString &subject, const QString &body);

    bool validatePassword(const QString &password);
    bool validateLogin(const QString &login);
    bool validateEmail(const QString &email);
};

#endif // CONTROLLER_H
