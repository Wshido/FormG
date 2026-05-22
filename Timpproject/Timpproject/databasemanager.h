#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QCoreApplication>

/*!
 * @brief Класс для управления базой данных приложения.
 *
 * Выполняет подключение к базе данных, регистрацию
 * и авторизацию пользователей, а также работу
 * с пользовательскими данными.
 */
class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Получение единственного экземпляра менеджера базы данных.
     * @return Ссылка на объект DatabaseManager.
     */
    static DatabaseManager& instance();

    /*!
     * @brief Инициализация базы данных.
     * @return true при успешной инициализации.
     */
    bool initDatabase();

    /*!
     * @brief Регистрация нового пользователя.
     * @param login Логин пользователя.
     * @param email Электронная почта пользователя.
     * @param password Пароль пользователя.
     * @return true при успешной регистрации.
     */
    bool registerUser(const QString& login, const QString& email, const QString& password);

    /*!
     * @brief Авторизация пользователя.
     * @param login Логин пользователя.
     * @param password Пароль пользователя.
     * @return true при успешной авторизации.
     */
    bool loginUser(const QString& login, const QString& password);

    /*!
     * @brief Проверка существования пользователя.
     * @param login Логин пользователя.
     * @return true если пользователь существует.
     */
    bool userExists(const QString& login);

    /*!
     * @brief Проверка существования электронной почты.
     * @param email Адрес электронной почты.
     * @return true если email уже зарегистрирован.
     */
    bool emailExists(const QString& email);

    /*!
     * @brief Изменение пароля пользователя.
     * @param login Логин пользователя.
     * @param newPassword Новый пароль.
     * @return true при успешном изменении пароля.
     */
    bool changePassword(const QString& login, const QString& newPassword);

    /*!
     * @brief Хеширование пароля.
     * @param password Исходный пароль.
     * @return Хешированное значение пароля.
     */
    QString hashPassword(const QString& password);

    /*!
     * @brief Хеширование логина.
     * @param login Логин пользователя.
     * @return Хешированное значение логина.
     */
    QString hashLogin(const QString& login);

    /*!
     * @brief Хеширование электронной почты.
     * @param email Электронная почта пользователя.
     * @return Хешированное значение email.
     */
    QString hashEmail(const QString& email);

    /*!
     * @brief Вывод списка всех пользователей в консоль.
     */
    void printAllUsers();

private:
    /*!
     * @brief Конструктор класса DatabaseManager.
     * @param parent Родительский объект.
     */
    explicit DatabaseManager(QObject *parent = nullptr);

    /*!
     * @brief Деструктор класса DatabaseManager.
     */
    ~DatabaseManager();

    /*!
     * @brief Объект подключения к базе данных.
     */
    QSqlDatabase m_db;

    /*!
     * @brief Создание таблиц базы данных.
     * @return true при успешном создании таблиц.
     */
    bool createTables();
};

#endif // DATABASEMANAGER_H