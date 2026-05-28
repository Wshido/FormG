#include "databasemanager.h"
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    initDatabase();
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen())
        m_db.close();
}

bool DatabaseManager::initDatabase()
{
    qDebug() << "=== ИНИЦИАЛИЗАЦИЯ БАЗЫ ДАННЫХ ===";

    if (m_db.isOpen()) {
        m_db.close();
    }

    QSqlDatabase::removeDatabase("qt_sql_default_connection");

    QString appPath = QCoreApplication::applicationDirPath();
    QString dbPath = appPath + "/users.db";

    qDebug() << "Путь к БД:" << dbPath;

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "ОШИБКА открытия базы данных:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "База данных открыта!";

    if (!createTables()) {
        qDebug() << "ОШИБКА создания таблиц";
        return false;
    }

    qDebug() << "База данных успешно инициализирована!";
    return true;
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;

    qDebug() << "Проверка существования таблицы users...";

    if (!query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='users'")) {
        qDebug() << "Ошибка проверки таблицы:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        qDebug() << "Таблица users уже существует";
        // Проверяем, есть ли нужные колонки
        query.exec("PRAGMA table_info(users)");
        bool hasFailedAttempts = false;
        bool hasLockUntil = false;
        while (query.next()) {
            QString colName = query.value(1).toString();
            if (colName == "failed_attempts") hasFailedAttempts = true;
            if (colName == "lock_until") hasLockUntil = true;
        }
        if (!hasFailedAttempts) {
            qDebug() << "Добавляем колонку failed_attempts";
            query.exec("ALTER TABLE users ADD COLUMN failed_attempts INTEGER DEFAULT 0");
        }
        if (!hasLockUntil) {
            qDebug() << "Добавляем колонку lock_until";
            query.exec("ALTER TABLE users ADD COLUMN lock_until INTEGER DEFAULT 0");
        }
        return true;
    }

    qDebug() << "Создаем таблицу users...";

    query.exec("DROP TABLE IF EXISTS users");

    // НОВАЯ СТРУКТУРА: логин и email в открытом виде!
    QString createUsersTable = R"(
        CREATE TABLE users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            login TEXT UNIQUE NOT NULL,
            email TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            last_login TIMESTAMP,
            failed_attempts INTEGER DEFAULT 0,
            lock_until INTEGER DEFAULT 0
        )
    )";

    if (!query.exec(createUsersTable)) {
        qDebug() << "Ошибка создания таблицы users:" << query.lastError().text();
        return false;
    }

    qDebug() << "Таблица users успешно создана!";
    return true;
}

// ТОЛЬКО хэширование пароля
QString DatabaseManager::hashPassword(const QString& password)
{
    QByteArray saltedPassword = password.toUtf8();
    saltedPassword.append("QCustomPlot2024Salt!");
    QByteArray hash = QCryptographicHash::hash(saltedPassword, QCryptographicHash::Sha256);
    return hash.toHex();
}

QString DatabaseManager::getEmailByLogin(const QString& login)
{
    QSqlQuery query;
    query.prepare("SELECT email FROM users WHERE login = ?");
    query.addBindValue(login);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return QString();
}

bool DatabaseManager::registerUser(const QString& login, const QString& email, const QString& password)
{
    qDebug() << "=== НАЧАЛО РЕГИСТРАЦИИ ===";

    if (userExists(login)) {
        qDebug() << "Ошибка: логин уже существует";
        return false;
    }

    if (emailExists(email)) {
        qDebug() << "Ошибка: email уже существует";
        return false;
    }

    QString passwordHash = hashPassword(password);

    QSqlQuery query;
    // Логин и email в открытом виде!
    query.prepare("INSERT INTO users (login, email, password_hash) VALUES (?, ?, ?)");
    query.addBindValue(login);
    query.addBindValue(email);
    query.addBindValue(passwordHash);

    if (!query.exec()) {
        qDebug() << "ОШИБКА SQL при регистрации:" << query.lastError().text();
        return false;
    }

    qDebug() << "Пользователь" << login << "успешно зарегистрирован!";
    return true;
}

int DatabaseManager::getFailedAttempts(const QString& login)
{
    QSqlQuery query;
    query.prepare("SELECT failed_attempts FROM users WHERE login = ?");
    query.addBindValue(login);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QDateTime DatabaseManager::getLockUntil(const QString& login)
{
    QSqlQuery query;
    query.prepare("SELECT lock_until FROM users WHERE login = ?");
    query.addBindValue(login);
    if (query.exec() && query.next()) {
        qint64 timestamp = query.value(0).toLongLong();
        if (timestamp > 0) {
            return QDateTime::fromSecsSinceEpoch(timestamp);
        }
    }
    return QDateTime();
}

void DatabaseManager::incrementFailedAttempts(const QString& login)
{
    int attempts = getFailedAttempts(login) + 1;
    QSqlQuery query;
    if (attempts >= 3) {
        qint64 lockUntil = QDateTime::currentDateTime().addSecs(30).toSecsSinceEpoch();
        query.prepare("UPDATE users SET failed_attempts = ?, lock_until = ? WHERE login = ?");
        query.addBindValue(attempts);
        query.addBindValue(lockUntil);
        query.addBindValue(login);
    } else {
        query.prepare("UPDATE users SET failed_attempts = ? WHERE login = ?");
        query.addBindValue(attempts);
        query.addBindValue(login);
    }
    query.exec();
}

void DatabaseManager::resetFailedAttempts(const QString& login)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET failed_attempts = 0, lock_until = 0 WHERE login = ?");
    query.addBindValue(login);
    query.exec();
}

bool DatabaseManager::loginUser(const QString& login, const QString& password)
{
    qDebug() << "=== ПОПЫТКА ВХОДА ===";

    // Проверка блокировки
    QDateTime lockUntil = getLockUntil(login);
    if (lockUntil.isValid() && lockUntil > QDateTime::currentDateTime()) {
        qDebug() << "Аккаунт заблокирован до:" << lockUntil;
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE login = ?");
    query.addBindValue(login);

    if (!query.exec()) {
        qDebug() << "Ошибка при проверке логина:" << query.lastError().text();
        incrementFailedAttempts(login);
        return false;
    }

    if (query.next()) {
        QString storedHash = query.value(0).toString();
        QString inputHash = hashPassword(password);

        if (storedHash == inputHash) {
            resetFailedAttempts(login);
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE users SET last_login = CURRENT_TIMESTAMP WHERE login = ?");
            updateQuery.addBindValue(login);
            updateQuery.exec();
            qDebug() << "Вход выполнен успешно!";
            return true;
        }
    }

    incrementFailedAttempts(login);
    qDebug() << "=== ВХОД НЕ УДАЛСЯ ===";
    return false;
}

bool DatabaseManager::userExists(const QString& login)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE login = ?");
    query.addBindValue(login);
    if (!query.exec()) return false;
    return query.next();
}

bool DatabaseManager::emailExists(const QString& email)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE email = ?");
    query.addBindValue(email);
    if (!query.exec()) return false;
    return query.next();
}

bool DatabaseManager::changePassword(const QString& login, const QString& newPassword)
{
    QString newPasswordHash = hashPassword(newPassword);
    QSqlQuery query;
    query.prepare("UPDATE users SET password_hash = ? WHERE login = ?");
    query.addBindValue(newPasswordHash);
    query.addBindValue(login);
    if (!query.exec()) return false;
    resetFailedAttempts(login);
    return query.numRowsAffected() > 0;
}

void DatabaseManager::printAllUsers()
{
    QSqlQuery query("SELECT id, login, email FROM users");
    qDebug() << "=== СОДЕРЖИМОЕ БАЗЫ ДАННЫХ ===";
    int count = 0;
    while (query.next()) {
        count++;
        int id = query.value(0).toInt();
        QString login = query.value(1).toString();
        QString email = query.value(2).toString();
        qDebug() << "ID:" << id << "Логин:" << login << "Email:" << email;
    }
    qDebug() << "Всего записей в БД:" << count;
    qDebug() << "=================================";
}