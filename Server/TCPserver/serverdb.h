#ifndef SERVERDB_H
#define SERVERDB_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QMutex>
#ifdef __linux__
#include <postgresql/libpq-fe.h>
#else
#include <libpq-fe.h>
#endif

class ServerDB
{
public:
    ServerDB();
    ~ServerDB();

    bool requestRegCode(const QString &email, QString &code);
    bool confirmReg(const QString &login, const QString &password, const QString &email, const QString &code);

    bool requestAuthCode(const QString &login, const QString &password, QString &email, QString &code);
    bool confirmAuth(const QString &email, const QString &code, QString &sessionToken);

    bool requestResetCode(const QString &loginOrEmail, QString &code, QString &outEmail);
    bool confirmResetPassword(const QString &email, const QString &code, const QString &newPassword);

    QString getStat(const QString &login);
    bool checkSession(const QString &login, const QString &sessionToken);

    QString getEmailByLoginOrEmail(const QString &loginOrEmail);

private:
    PGconn *m_conn;
    QMutex m_mutex;
    QMap<QString, QString> m_sessionCache;

    struct TempRegData {
        QString email;
        qint64 createdAt;
    };
    struct TempAuthData {
        QString login;
        QString email;
        qint64 createdAt;
    };
    struct TempResetData {
        QString email;
        qint64 createdAt;
    };

    QMap<QString, TempRegData> m_tempRegs;
    QMap<QString, TempAuthData> m_tempAuths;
    QMap<QString, TempResetData> m_tempResets;

    static const qint64 CODE_EXPIRY_MS = 5 * 60 * 1000;

    bool connectToDB();
    QString hashPassword(const QString &password, const QString &salt = QString());
    QString generateSalt();
    QString generateSessionToken(const QString &login);
    QString generateVerificationCode();
    void cleanupExpiredCodes();
    QString getEmailByLogin(const QString &login);
    bool checkEmailExists(const QString &email);
    bool checkLoginExists(const QString &login);
};

#endif // SERVERDB_H
