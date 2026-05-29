#include "serverdb.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QDateTime>
#include <cstdlib>

ServerDB::ServerDB()
    : m_conn(nullptr)
{
    connectToDB();
}

ServerDB::~ServerDB()
{
    if (m_conn) {
        PQfinish(m_conn);
    }
}

bool ServerDB::connectToDB()
{
    const char* envHost = std::getenv("DB_HOST");
    const char* envPort = std::getenv("DB_PORT");
    const char* envName = std::getenv("DB_NAME");
    const char* envUser = std::getenv("DB_USER");
    const char* envPass = std::getenv("DB_PASSWORD");

    QString host = envHost ? envHost : "127.0.0.1";
    QString port = envPort ? envPort : "5432";
    QString dbname = envName ? envName : "postgres";
    QString user = envUser ? envUser : "postgres";
    QString password = envPass ? envPass : "1234";

    QString conninfo = "host=" + host +
                       " port=" + port +
                       " dbname=" + dbname +
                       " user=" + user +
                       " password=" + password;

    m_conn = PQconnectdb(conninfo.toUtf8().constData());

    if (PQstatus(m_conn) != CONNECTION_OK) {
        qDebug() << "Ошибка подключения к БД:" << PQerrorMessage(m_conn);
        return false;
    }

    const char* createTableSQL =
        "CREATE TABLE IF NOT EXISTS users ("
        "    id              SERIAL PRIMARY KEY,"
        "    name            VARCHAR(100) NOT NULL,"
        "    login           VARCHAR(16) UNIQUE NOT NULL,"
        "    email           VARCHAR(100) UNIQUE NOT NULL,"
        "    password_hash   TEXT NOT NULL,"
        "    created_at      TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");"
        "CREATE INDEX IF NOT EXISTS idx_users_email ON users(email);"
        "CREATE INDEX IF NOT EXISTS idx_users_login ON users(login);";

    PGresult* res = PQexec(m_conn, createTableSQL);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "Ошибка создания таблицы:" << PQerrorMessage(m_conn);
        PQclear(res);
        return false;
    }
    PQclear(res);

    qDebug() << "Подключение к PostgreSQL успешно!";
    return true;
}

QString ServerDB::hashPassword(const QString &password, const QString &salt)
{
    QString actualSalt = salt;
    if (actualSalt.isEmpty()) {
        actualSalt = generateSalt();
    }
    QByteArray data = (password + actualSalt).toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    return actualSalt + ":" + hash.toHex();
}

QString ServerDB::generateSalt()
{
    QByteArray salt;
    salt.resize(16);
    for (int i = 0; i < 16; ++i) {
        salt[i] = static_cast<char>(QRandomGenerator::global()->bounded(33, 127));
    }
    return QString::fromLatin1(salt);
}

QString ServerDB::generateSessionToken(const QString &login)
{
    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch());
    QString random = QString::number(QRandomGenerator::global()->generate());
    QString hash = hashPassword(login + timestamp + random);
    return hash.left(32);
}

QString ServerDB::generateVerificationCode()
{
    int code = QRandomGenerator::global()->bounded(100000, 999999);
    return QString::number(code);
}

void ServerDB::cleanupExpiredCodes()
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();

    auto it = m_tempRegs.begin();
    while (it != m_tempRegs.end()) {
        if (now - it.value().createdAt > CODE_EXPIRY_MS) {
            qDebug() << "Код регистрации" << it.key() << "истёк — очищен";
            it = m_tempRegs.erase(it);
        } else {
            ++it;
        }
    }

    auto it2 = m_tempAuths.begin();
    while (it2 != m_tempAuths.end()) {
        if (now - it2.value().createdAt > CODE_EXPIRY_MS) {
            qDebug() << "Код авторизации" << it2.key() << "истёк — очищен";
            it2 = m_tempAuths.erase(it2);
        } else {
            ++it2;
        }
    }

    auto it3 = m_tempResets.begin();
    while (it3 != m_tempResets.end()) {
        if (now - it3.value().createdAt > CODE_EXPIRY_MS) {
            qDebug() << "Код восстановления" << it3.key() << "истёк — очищен";
            it3 = m_tempResets.erase(it3);
        } else {
            ++it3;
        }
    }
}

void ServerDB::cleanupExpiredSessions()
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();

    auto it = m_sessionCache.begin();
    while (it != m_sessionCache.end()) {
        if (now - it.value().lastActivity > SESSION_TTL_MS) {
            qDebug() << "Сессия для" << it.key() << "истекла — очищена";
            it = m_sessionCache.erase(it);
        } else {
            ++it;
        }
    }
}

void ServerDB::updateSessionActivity(const QString &login)
{
    if (m_sessionCache.contains(login)) {
        m_sessionCache[login].lastActivity = QDateTime::currentMSecsSinceEpoch();
    }
}

void ServerDB::logoutSession(const QString &login)
{
    QMutexLocker locker(&m_mutex);
    if (m_sessionCache.remove(login) > 0) {
        qDebug() << "Сессия для" << login << "деактивирована";
    }
}

void ServerDB::logoutAllSessions(const QString &login)
{
    QMutexLocker locker(&m_mutex);
    m_sessionCache.remove(login);
    qDebug() << "Все сессии для" << login << "деактивированы";
}

bool ServerDB::refreshToken(const QString &login, const QString &oldToken, QString &newToken)
{
    QMutexLocker locker(&m_mutex);

    cleanupExpiredSessions();

    if (!m_sessionCache.contains(login)) {
        return false;
    }

    if (m_sessionCache[login].token != oldToken) {
        return false;
    }

    if (QDateTime::currentMSecsSinceEpoch() - m_sessionCache[login].lastActivity > SESSION_TTL_MS / 2) {
        newToken = generateSessionToken(login);
        m_sessionCache[login].token = newToken;
        m_sessionCache[login].lastActivity = QDateTime::currentMSecsSinceEpoch();
        qDebug() << "Токен обновлён для" << login;
        return true;
    }

    newToken = oldToken;
    return true;
}

// ==================== RATE LIMITING ====================
bool ServerDB::isRateLimited(const QString &identifier)
{
    QMutexLocker locker(&m_mutex);

    qint64 now = QDateTime::currentMSecsSinceEpoch();

    if (!m_rateLimits.contains(identifier)) {
        RateLimitData data;
        data.attemptCount = 1;
        data.windowStart = now;
        m_rateLimits[identifier] = data;
        return false;
    }

    RateLimitData &data = m_rateLimits[identifier];

    if (now - data.windowStart > RATE_LIMIT_WINDOW_MS) {
        data.attemptCount = 1;
        data.windowStart = now;
        return false;
    }

    if (data.attemptCount >= RATE_LIMIT_MAX_ATTEMPTS) {
        qDebug() << "Rate limit превышен для" << identifier;
        return true;
    }

    data.attemptCount++;
    return false;
}

// ==================== BRUTE FORCE ====================
bool ServerDB::isBruteForceBlocked(const QString &login)
{
    QMutexLocker locker(&m_mutex);

    if (!m_bruteForce.contains(login)) {
        return false;
    }

    BruteForceData &data = m_bruteForce[login];
    qint64 now = QDateTime::currentMSecsSinceEpoch();

    if (data.lockoutUntil > 0 && now < data.lockoutUntil) {
        qDebug() << "Brute force блокировка для" << login
                 << "до" << QDateTime::fromMSecsSinceEpoch(data.lockoutUntil).toString();
        return true;
    }

    if (data.lockoutUntil > 0 && now >= data.lockoutUntil) {
        data.failedAttempts = 0;
        data.lockoutUntil = 0;
        qDebug() << "Brute force блокировка снята для" << login;
    }

    return false;
}

void ServerDB::recordFailedAttempt(const QString &login)
{
    QMutexLocker locker(&m_mutex);

    if (!m_bruteForce.contains(login)) {
        BruteForceData data;
        data.failedAttempts = 1;
        data.lockoutUntil = 0;
        m_bruteForce[login] = data;
        return;
    }

    BruteForceData &data = m_bruteForce[login];
    data.failedAttempts++;

    if (data.failedAttempts >= BRUTE_FORCE_MAX_ATTEMPTS) {
        data.lockoutUntil = QDateTime::currentMSecsSinceEpoch() + BRUTE_FORCE_LOCKOUT_MS;
        qDebug() << "Brute force блокировка установлена для" << login
                 << "на 15 минут (попыток:" << data.failedAttempts << ")";
    }
}

void ServerDB::resetFailedAttempts(const QString &login)
{
    QMutexLocker locker(&m_mutex);

    if (m_bruteForce.contains(login)) {
        m_bruteForce[login].failedAttempts = 0;
        m_bruteForce[login].lockoutUntil = 0;
    }
}

// ==================== INPUT VALIDATION ====================
bool ServerDB::validateInputLength(const QString &login, const QString &email, const QString &password)
{
    if (!login.isEmpty() && login.length() > MAX_LOGIN_LENGTH) {
        qDebug() << "Логин слишком длинный:" << login.length() << ">" << MAX_LOGIN_LENGTH;
        return false;
    }
    if (!email.isEmpty() && email.length() > MAX_EMAIL_LENGTH) {
        qDebug() << "Email слишком длинный:" << email.length() << ">" << MAX_EMAIL_LENGTH;
        return false;
    }
    if (!password.isEmpty() && password.length() > MAX_PASSWORD_LENGTH) {
        qDebug() << "Пароль слишком длинный:" << password.length() << ">" << MAX_PASSWORD_LENGTH;
        return false;
    }
    return true;
}

// ==================== DB OPERATIONS ====================
QString ServerDB::getEmailByLogin(const QString &login)
{
    QString sql = "SELECT email FROM users WHERE login = $1";
    const char* params[1] = {login.toUtf8().constData()};

    PGresult* res = PQexecParams(m_conn, sql.toUtf8().constData(), 1, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        PQclear(res);
        return QString();
    }

    QString email = PQgetvalue(res, 0, 0);
    PQclear(res);
    return email;
}

QString ServerDB::getEmailByLoginOrEmail(const QString &loginOrEmail)
{
    if (checkEmailExists(loginOrEmail)) {
        return loginOrEmail;
    }
    return getEmailByLogin(loginOrEmail);
}

bool ServerDB::checkEmailExists(const QString &email)
{
    QString sql = "SELECT id FROM users WHERE email = $1";
    const char* params[1] = {email.toUtf8().constData()};

    PGresult* res = PQexecParams(m_conn, sql.toUtf8().constData(), 1, NULL, params, NULL, NULL, 0);

    bool exists = (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0);
    PQclear(res);
    return exists;
}

bool ServerDB::checkLoginExists(const QString &login)
{
    QString sql = "SELECT id FROM users WHERE login = $1";
    const char* params[1] = {login.toUtf8().constData()};

    PGresult* res = PQexecParams(m_conn, sql.toUtf8().constData(), 1, NULL, params, NULL, NULL, 0);

    bool exists = (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0);
    PQclear(res);
    return exists;
}

// ==================== РЕГИСТРАЦИЯ ====================
bool ServerDB::requestRegCode(const QString &email, QString &code)
{
    QMutexLocker locker(&m_mutex);

    cleanupExpiredCodes();

    if (checkEmailExists(email)) {
        qDebug() << "Email уже зарегистрирован:" << email;
        return false;
    }

    code = generateVerificationCode();

    TempRegData tempData;
    tempData.email = email;
    tempData.createdAt = QDateTime::currentMSecsSinceEpoch();
    m_tempRegs[code] = tempData;

    qDebug() << "==========================================";
    qDebug() << "  РЕГИСТРАЦИЯ — КОД ПОДТВЕРЖДЕНИЯ: " << code;
    qDebug() << "  Почта: " << email;
    qDebug() << "  Код действителен 5 минут";
    qDebug() << "==========================================";

    return true;
}

bool ServerDB::confirmReg(const QString &login, const QString &password, const QString &email, const QString &code)
{
    QMutexLocker locker(&m_mutex);

    if (!validateInputLength(login, email, password)) {
        return false;
    }

    cleanupExpiredCodes();

    if (!m_tempRegs.contains(code)) {
        qDebug() << "Неверный или просроченный код для регистрации";
        return false;
    }

    TempRegData tempData = m_tempRegs[code];
    if (tempData.email != email) {
        qDebug() << "Email не соответствует коду";
        return false;
    }

    if (checkLoginExists(login)) {
        qDebug() << "Логин уже занят:" << login;
        return false;
    }

    QString passwordHash = hashPassword(password);
    QString sql = "INSERT INTO users (name, login, email, password_hash) VALUES ($1, $2, $3, $4)";
    const char* params[4] = {
        login.toUtf8().constData(),
        login.toUtf8().constData(),
        email.toUtf8().constData(),
        passwordHash.toUtf8().constData()
    };

    PGresult* res = PQexecParams(m_conn, sql.toUtf8().constData(), 4, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "Ошибка SQL при регистрации:" << PQerrorMessage(m_conn);
        PQclear(res);
        return false;
    }

    PQclear(res);
    m_tempRegs.remove(code);

    qDebug() << "Пользователь" << login << "успешно зарегистрирован!";
    return true;
}

// ==================== АВТОРИЗАЦИЯ ====================
bool ServerDB::requestAuthCode(const QString &login, const QString &password, QString &email, QString &code)
{
    QMutexLocker locker(&m_mutex);

    if (isBruteForceBlocked(login)) {
        qDebug() << "Brute force блокировка для" << login;
        return false;
    }

    cleanupExpiredCodes();

    QString sql = "SELECT password_hash, email FROM users WHERE login = $1";
    const char* params[1] = {login.toUtf8().constData()};

    PGresult* res = PQexecParams(m_conn, sql.toUtf8().constData(), 1, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        PQclear(res);
        qDebug() << "Логин не найден:" << login;
        recordFailedAttempt(login);
        return false;
    }

    QString storedHash = PQgetvalue(res, 0, 0);
    email = PQgetvalue(res, 0, 1);
    PQclear(res);

    QString inputHash;
    if (storedHash.contains(':')) {
        QString salt = storedHash.section(':', 0, 0);
        inputHash = hashPassword(password, salt);
    } else {
        inputHash = hashPassword(password);
    }
    if (storedHash != inputHash) {
        qDebug() << "Неверный пароль для:" << login;
        recordFailedAttempt(login);
        return false;
    }

    resetFailedAttempts(login);

    code = generateVerificationCode();

    TempAuthData tempData;
    tempData.login = login;
    tempData.email = email;
    tempData.createdAt = QDateTime::currentMSecsSinceEpoch();
    m_tempAuths[code] = tempData;

    qDebug() << "==========================================";
    qDebug() << "  АВТОРИЗАЦИЯ — КОД ПОДТВЕРЖДЕНИЯ: " << code;
    qDebug() << "  Логин: " << login;
    qDebug() << "  Почта: " << email;
    qDebug() << "  Код действителен 5 минут";
    qDebug() << "==========================================";

    return true;
}

bool ServerDB::confirmAuth(const QString &email, const QString &code, QString &sessionToken)
{
    QMutexLocker locker(&m_mutex);

    cleanupExpiredCodes();

    if (!m_tempAuths.contains(code)) {
        qDebug() << "Неверный или просроченный код для авторизации";
        return false;
    }

    TempAuthData tempData = m_tempAuths[code];
    if (tempData.email != email) {
        qDebug() << "Email не соответствует коду";
        return false;
    }

    sessionToken = generateSessionToken(tempData.login);

    SessionData session;
    session.token = sessionToken;
    session.createdAt = QDateTime::currentMSecsSinceEpoch();
    session.lastActivity = QDateTime::currentMSecsSinceEpoch();
    m_sessionCache[tempData.login] = session;

    m_tempAuths.remove(code);

    qDebug() << "Пользователь" << tempData.login << "успешно авторизован!";
    return true;
}

// ==================== ВОССТАНОВЛЕНИЕ ПАРОЛЯ ====================
bool ServerDB::requestResetCode(const QString &loginOrEmail, QString &code, QString &outEmail)
{
    QMutexLocker locker(&m_mutex);

    cleanupExpiredCodes();

    QString email;
    if (checkEmailExists(loginOrEmail)) {
        email = loginOrEmail;
    } else {
        email = getEmailByLogin(loginOrEmail);
        if (email.isEmpty()) {
            qDebug() << "Пользователь не найден:" << loginOrEmail;
            return false;
        }
    }

    code = generateVerificationCode();

    TempResetData tempData;
    tempData.email = email;
    tempData.createdAt = QDateTime::currentMSecsSinceEpoch();
    m_tempResets[code] = tempData;

    outEmail = email;

    qDebug() << "==========================================";
    qDebug() << "  ВОССТАНОВЛЕНИЕ ПАРОЛЯ — КОД: " << code;
    qDebug() << "  Почта: " << email;
    qDebug() << "  Код действителен 5 минут";
    qDebug() << "==========================================";

    return true;
}

bool ServerDB::confirmResetPassword(const QString &loginOrEmail, const QString &code, const QString &newPassword)
{
    QMutexLocker locker(&m_mutex);

    if (!validateInputLength("", "", newPassword)) {
        return false;
    }

    cleanupExpiredCodes();

    QString email;
    if (checkEmailExists(loginOrEmail)) {
        email = loginOrEmail;
    } else {
        email = getEmailByLogin(loginOrEmail);
        if (email.isEmpty()) {
            qDebug() << "Пользователь не найден:" << loginOrEmail;
            return false;
        }
    }

    if (!m_tempResets.contains(code)) {
        qDebug() << "Неверный или просроченный код для восстановления";
        return false;
    }

    TempResetData tempData = m_tempResets[code];
    if (tempData.email != email) {
        qDebug() << "Email не соответствует коду";
        return false;
    }

    QString newHash = hashPassword(newPassword);
    QString sql = "UPDATE users SET password_hash = $1 WHERE email = $2";
    const char* params[2] = {newHash.toUtf8().constData(), email.toUtf8().constData()};

    PGresult* res = PQexecParams(m_conn, sql.toUtf8().constData(), 2, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        return false;
    }

    PQclear(res);
    m_tempResets.remove(code);

    qDebug() << "Пароль для" << email << "успешно изменен!";
    return true;
}

bool ServerDB::checkSession(const QString &login, const QString &sessionToken)
{
    QMutexLocker locker(&m_mutex);

    cleanupExpiredSessions();

    if (!m_sessionCache.contains(login)) {
        return false;
    }

    if (m_sessionCache[login].token != sessionToken) {
        return false;
    }

    updateSessionActivity(login);
    return true;
}

QString ServerDB::getStat(const QString &login)
{
    Q_UNUSED(login)

    QString sql = "SELECT COUNT(*) FROM users";
    PGresult* res = PQexec(m_conn, sql.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        return "stat&0&0&0";
    }

    int userCount = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);

    return QString("stat&%1&3&21").arg(userCount);
}
