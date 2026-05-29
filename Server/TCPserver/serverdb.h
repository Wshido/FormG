#ifndef SERVERDB_H
#define SERVERDB_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QMutex>
#include <QElapsedTimer>
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

    void logoutSession(const QString &login);
    void logoutAllSessions(const QString &login);
    void cleanupExpiredSessions();
    bool refreshToken(const QString &login, const QString &oldToken, QString &newToken);

    bool isRateLimited(const QString &identifier);
    bool isBruteForceBlocked(const QString &login);
    void recordFailedAttempt(const QString &login);
    void resetFailedAttempts(const QString &login);

    static const int MAX_LOGIN_LENGTH = 16;
    static const int MAX_EMAIL_LENGTH = 100;
    static const int MAX_PASSWORD_LENGTH = 64;

private:
    PGconn *m_conn;
    QMutex m_mutex;

    struct SessionData {
        QString token;
        qint64 createdAt;
        qint64 lastActivity;
    };
    QMap<QString, SessionData> m_sessionCache;

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

    struct RateLimitData {
        int attemptCount;
        qint64 windowStart;
    };
    QMap<QString, RateLimitData> m_rateLimits;

    struct BruteForceData {
        int failedAttempts;
        qint64 lockoutUntil;
    };
    QMap<QString, BruteForceData> m_bruteForce;

    static const qint64 CODE_EXPIRY_MS = 5 * 60 * 1000;
    static const qint64 SESSION_TTL_MS = 30 * 60 * 1000;
    static const int RATE_LIMIT_MAX_ATTEMPTS = 10;
    static const qint64 RATE_LIMIT_WINDOW_MS = 60 * 1000;
    static const int BRUTE_FORCE_MAX_ATTEMPTS = 5;
    static const qint64 BRUTE_FORCE_LOCKOUT_MS = 15 * 60 * 1000;

    bool connectToDB();
    QString hashPassword(const QString &password, const QString &salt = QString());
    QString generateSalt();
    QString generateSessionToken(const QString &login);
    QString generateVerificationCode();
    void cleanupExpiredCodes();
    QString getEmailByLogin(const QString &login);
    bool checkEmailExists(const QString &email);
    bool checkLoginExists(const QString &login);

    bool validateInputLength(const QString &login, const QString &email, const QString &password);
    void updateSessionActivity(const QString &login);
};

#endif // SERVERDB_H
