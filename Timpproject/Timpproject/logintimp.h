#ifndef LOGINTIMP_H
#define LOGINTIMP_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginTimp;
}
QT_END_NAMESPACE

/*!
 * @brief Окно авторизации пользователя.
 *
 * Класс реализует интерфейс входа в систему,
 * а также переходы к регистрации и восстановлению пароля.
 */
class LoginTimp : public QDialog
{
    Q_OBJECT

public:
    /*!
     * @brief Конструктор окна LoginTimp.
     * @param parent Родительский виджет.
     */
    explicit LoginTimp(QWidget *parent = nullptr);

    /*!
     * @brief Деструктор класса LoginTimp.
     */
    ~LoginTimp();

private slots:
    /*!
     * @brief Обработчик нажатия кнопки входа.
     */
    void on_loginButton_clicked();

    /*!
     * @brief Обработчик нажатия кнопки возврата.
     */
    void on_backButton_clicked();

    /*!
     * @brief Обработчик перехода по ссылке восстановления пароля.
     * @param link Текст ссылки.
     */
    void on_forgotLabel_linkActivated(const QString &link);

    /*!
     * @brief Обработчик нажатия кнопки регистрации.
     */
    void on_registerButton_clicked();

private:
    /*!
     * @brief Указатель на пользовательский интерфейс окна.
     */
    Ui::LoginTimp *ui;
};

#endif // LOGINTIMP_H