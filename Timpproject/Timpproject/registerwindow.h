#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class RegisterWindow;
}

/*!
 * @brief Окно регистрации нового пользователя.
 *
 * Класс предоставляет интерфейс для создания
 * новой учетной записи пользователя.
 */
class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    /*!
     * @brief Конструктор окна RegisterWindow.
     * @param parent Родительский виджет.
     */
    explicit RegisterWindow(QWidget *parent = nullptr);

    /*!
     * @brief Деструктор класса RegisterWindow.
     */
    ~RegisterWindow();

signals:
    /*!
     * @brief Сигнал возврата к предыдущему окну.
     */
    void backRequested();

private slots:
    /*!
     * @brief Обработчик нажатия кнопки создания аккаунта.
     */
    void on_createButton_clicked();

    /*!
     * @brief Обработчик нажатия кнопки возврата.
     */
    void on_backButton_clicked();

private:
    /*!
     * @brief Указатель на пользовательский интерфейс окна.
     */
    Ui::RegisterWindow *ui;
};

#endif