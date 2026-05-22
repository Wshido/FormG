#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QWidget>

namespace Ui {
class ForgotPassword;
}

/*!
 * @brief Окно восстановления пароля.
 *
 * Класс реализует функционал восстановления пароля
 * пользователя с подтверждением через код.
 */
class ForgotPassword : public QWidget
{
    Q_OBJECT

public:
    /*!
     * @brief Конструктор окна ForgotPassword.
     * @param parent Родительский виджет.
     */
    explicit ForgotPassword(QWidget *parent = nullptr);

    /*!
     * @brief Деструктор класса ForgotPassword.
     */
    ~ForgotPassword();

signals:
    /*!
     * @brief Сигнал возврата к предыдущему окну.
     */
    void backRequested();

private slots:
    /*!
     * @brief Обработчик нажатия кнопки отправки кода.
     */
    void on_sendButton_clicked();

    /*!
     * @brief Обработчик нажатия кнопки возврата.
     */
    void on_backButton_clicked();

    /*!
     * @brief Обработчик подтверждения кода.
     */
    void on_confirmCodeButton_clicked();

    /*!
     * @brief Обработчик изменения пароля.
     */
    void on_changePasswordButton_clicked();

private:
    /*!
     * @brief Указатель на пользовательский интерфейс окна.
     */
    Ui::ForgotPassword *ui;

    /*!
     * @brief Временный код подтверждения.
     */
    QString m_tempCode;
};

#endif