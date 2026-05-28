#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QCoreApplication>
#include <QDateTime>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager& instance();

    bool initDatabase();
    bool registerUser(const QString& login, const QString& email, const QString& password);
    bool loginUser(const QString& login, const QString& password);
    bool userExists(const QString& login);
    bool emailExists(const QString& email);
    bool changePassword(const QString& login, const QString& newPassword);
    QString getEmailByLogin(const QString& login);

    // Функции для блокировки
    int getFailedAttempts(const QString& login);
    QDateTime getLockUntil(const QString& login);
    void incrementFailedAttempts(const QString& login);
    void resetFailedAttempts(const QString& login);

    QString hashPassword(const QString& password);

    void printAllUsers();

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    QSqlDatabase m_db;
    bool createTables();
};

#endif // DATABASEMANAGER_H