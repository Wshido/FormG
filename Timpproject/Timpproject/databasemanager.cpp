#include "databasemanager.h"
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

/*!
 * @brief Получение экземпляра DatabaseManager.
 * @return Ссылка на объект менеджера базы данных.
 */
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

/*!
 * @brief Конструктор класса DatabaseManager.
 * @param parent Родительский объект.
 */
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    // Инициализация базы данных при создании объекта
    initDatabase();
}

/*!
 * @brief Деструктор класса DatabaseManager.
 */
DatabaseManager::~DatabaseManager()
{
    // Закрытие соединения с базой данных
    if (m_db.isOpen())
        m_db.close();
}

/*!
 * @brief Инициализация базы данных SQLite.
 * @return true при успешной инициализации.
 */
bool DatabaseManager::initDatabase()
{
    qDebug() << "=== ИНИЦИАЛИЗАЦИЯ БАЗЫ ДАННЫХ ===";

    // Закрываем старую БД если открыта
    if (m_db.isOpen()) {
        m_db.close();
    }

    // Удаляем старое соединение
    QSqlDatabase::removeDatabase("qt_sql_default_connection");

    // Формирование пути к файлу базы данных
    QString appPath = QCoreApplication::applicationDirPath();
    QString dbPath = appPath + "/users.db";

    qDebug() << "Путь к БД:" << dbPath;

    // Проверка существования папки приложения
    QDir dir(appPath);
    qDebug() << "Папка приложения существует:" << dir.exists();

    // Проверка прав на запись
    bool canWrite = QFileInfo(appPath).isWritable();
    qDebug() << "Папка доступна для записи:" << canWrite;

    // Создание подключения SQLite
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    // Открытие базы данных
    if (!m_db.open()) {
        qDebug() << "ОШИБКА открытия базы данных:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "База данных открыта!";

    // Создание таблиц
    if (!createTables()) {
        qDebug() << "ОШИБКА создания таблиц";
        return false;
    }

    qDebug() << "База данных успешно инициализирована!";
    qDebug() << "===================================";
    return true;
}

/*!
 * @brief Создание таблиц базы данных.
 * @return true если таблицы успешно созданы.
 */
bool DatabaseManager::createTables()
{
    QSqlQuery query;

    qDebug() << "Проверка существования таблицы users...";

    // Проверка существования таблицы users
    if (!query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='users'")) {
        qDebug() << "Ошибка проверки таблицы:" << query.lastError().text();
        return false;
    }

    // Если таблица уже существует
    if (query.next()) {
        qDebug() << "Таблица users уже существует";
        return true;
    }

    qDebug() << "Создаем таблицу users...";

    // Удаление старой таблицы
    query.exec("DROP TABLE IF EXISTS users");

    // SQL-запрос создания таблицы пользователей
    QString createUsersTable = R"(
        CREATE TABLE users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            login_hash TEXT UNIQUE NOT NULL,
            email_hash TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            last_login TIMESTAMP
        )
    )";

    // Выполнение SQL-запроса
    if (!query.exec(createUsersTable)) {
        qDebug() << "Ошибка создания таблицы users:" << query.lastError().text();
        return false;
    }

    qDebug() << "Таблица users успешно создана!";
    return true;
}

/*!
 * @brief Хеширование логина пользователя.
 * @param login Логин пользователя.
 * @return Хешированное значение логина.
 */
QString DatabaseManager::hashLogin(const QString& login)
{
    QByteArray saltedLogin = login.toUtf8();
    saltedLogin.append("LoginSalt2024!");

    QByteArray hash = QCryptographicHash::hash(
        saltedLogin,
        QCryptographicHash::Sha256
        );

    return hash.toHex();
}

/*!
 * @brief Хеширование электронной почты пользователя.
 * @param email Электронная почта пользователя.
 * @return Хешированное значение email.
 */
QString DatabaseManager::hashEmail(const QString& email)
{
    QByteArray saltedEmail = email.toUtf8();
    saltedEmail.append("EmailSalt2024!");

    QByteArray hash = QCryptographicHash::hash(
        saltedEmail,
        QCryptographicHash::Sha256
        );

    return hash.toHex();
}

/*!
 * @brief Хеширование пароля пользователя.
 * @param password Пароль пользователя.
 * @return Хешированное значение пароля.
 */
QString DatabaseManager::hashPassword(const QString& password)
{
    QByteArray saltedPassword = password.toUtf8();
    saltedPassword.append("QCustomPlot2024Salt!");

    QByteArray hash = QCryptographicHash::hash(
        saltedPassword,
        QCryptographicHash::Sha256
        );

    return hash.toHex();
}

/*!
 * @brief Регистрация нового пользователя.
 * @param login Логин пользователя.
 * @param email Электронная почта пользователя.
 * @param password Пароль пользователя.
 * @return true при успешной регистрации.
 */
bool DatabaseManager::registerUser(const QString& login,
                                   const QString& email,
                                   const QString& password)
{
    qDebug() << "=== НАЧАЛО РЕГИСТРАЦИИ ===";

    // Проверка существования логина
    if (userExists(login)) {
        qDebug() << "Ошибка: логин уже существует";
        return false;
    }

    // Проверка существования email
    if (emailExists(email)) {
        qDebug() << "Ошибка: email уже существует";
        return false;
    }

    // Вычисление хешей
    QString loginHash = hashLogin(login);
    QString emailHash = hashEmail(email);
    QString passwordHash = hashPassword(password);

    // Подготовка SQL-запроса
    QSqlQuery query;
    query.prepare(
        "INSERT INTO users "
        "(login_hash, email_hash, password_hash) "
        "VALUES (?, ?, ?)"
        );

    query.addBindValue(loginHash);
    query.addBindValue(emailHash);
    query.addBindValue(passwordHash);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "ОШИБКА SQL при регистрации:"
                 << query.lastError().text();
        return false;
    }

    qDebug() << "Пользователь успешно зарегистрирован";

    // Вывод пользователей для отладки
    printAllUsers();

    return true;
}

/*!
 * @brief Авторизация пользователя.
 * @param login Логин пользователя.
 * @param password Пароль пользователя.
 * @return true если авторизация успешна.
 */
bool DatabaseManager::loginUser(const QString& login,
                                const QString& password)
{
    qDebug() << "=== ПОПЫТКА ВХОДА ===";

    // Получение хеша логина
    QString loginHash = hashLogin(login);

    // Поиск пользователя в базе данных
    QSqlQuery query;
    query.prepare(
        "SELECT password_hash FROM users "
        "WHERE login_hash = ?"
        );

    query.addBindValue(loginHash);

    if (!query.exec()) {
        qDebug() << "Ошибка при проверке логина:"
                 << query.lastError().text();
        return false;
    }

    // Проверка найденного пользователя
    if (query.next()) {

        QString storedHash = query.value(0).toString();
        QString inputHash = hashPassword(password);

        // Сравнение хешей пароля
        if (storedHash == inputHash) {

            // Обновление времени последнего входа
            QSqlQuery updateQuery;
            updateQuery.prepare(
                "UPDATE users "
                "SET last_login = CURRENT_TIMESTAMP "
                "WHERE login_hash = ?"
                );

            updateQuery.addBindValue(loginHash);
            updateQuery.exec();

            qDebug() << "Вход выполнен успешно!";
            return true;
        }
    }

    qDebug() << "=== ВХОД НЕ УДАЛСЯ ===";
    return false;
}

/*!
 * @brief Проверка существования пользователя.
 * @param login Логин пользователя.
 * @return true если пользователь найден.
 */
bool DatabaseManager::userExists(const QString& login)
{
    QString loginHash = hashLogin(login);

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE login_hash = ?");
    query.addBindValue(loginHash);

    if (!query.exec()) {
        qDebug() << "Ошибка в userExists:"
                 << query.lastError().text();
        return false;
    }

    return query.next();
}

/*!
 * @brief Проверка существования email.
 * @param email Электронная почта пользователя.
 * @return true если email найден.
 */
bool DatabaseManager::emailExists(const QString& email)
{
    QString emailHash = hashEmail(email);

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE email_hash = ?");
    query.addBindValue(emailHash);

    if (!query.exec()) {
        qDebug() << "Ошибка в emailExists:"
                 << query.lastError().text();
        return false;
    }

    return query.next();
}

/*!
 * @brief Изменение пароля пользователя.
 * @param login Логин пользователя.
 * @param newPassword Новый пароль.
 * @return true при успешной смене пароля.
 */
bool DatabaseManager::changePassword(const QString& login,
                                     const QString& newPassword)
{
    QString loginHash = hashLogin(login);

    QSqlQuery query;
    query.prepare(
        "UPDATE users "
        "SET password_hash = ? "
        "WHERE login_hash = ?"
        );

    query.addBindValue(hashPassword(newPassword));
    query.addBindValue(loginHash);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Ошибка смены пароля:"
                 << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

/*!
 * @brief Вывод всех пользователей базы данных.
 *
 * Используется для отладки приложения.
 */
void DatabaseManager::printAllUsers()
{
    QSqlQuery query(
        "SELECT id, login_hash, email_hash FROM users"
        );

    qDebug() << "=== СОДЕРЖИМОЕ БАЗЫ ДАННЫХ ===";

    int count = 0;

    while (query.next()) {

        count++;

        int id = query.value(0).toInt();
        QString loginHash = query.value(1).toString();
        QString emailHash = query.value(2).toString();

        qDebug() << "ID:" << id
                 << "Login Hash:"
                 << loginHash.left(20) + "..."
                 << "Email Hash:"
                 << emailHash.left(20) + "...";
    }

    qDebug() << "Всего записей в БД:" << count;
    qDebug() << "=================================";
}