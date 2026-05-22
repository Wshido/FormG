#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class WelcomeWindow;
}
QT_END_NAMESPACE

/*!
 * @brief Приветственное окно приложения.
 *
 * Класс отображает стартовый экран программы
 * и обрабатывает навигацию между окнами.
 */
class WelcomeWindow : public QWidget
{
    Q_OBJECT

signals:
    /*!
     * @brief Сигнал возврата к предыдущему окну.
     */
    void backRequested();

public:
    /*!
     * @brief Конструктор окна WelcomeWindow.
     * @param parent Родительский виджет.
     */
    explicit WelcomeWindow(QWidget *parent = nullptr);

    /*!
     * @brief Деструктор класса WelcomeWindow.
     */
    ~WelcomeWindow();

private slots:
    /*!
     * @brief Обработчик нажатия кнопки перехода.
     */
    void on_nextButton_clicked();

    /*!
     * @brief Обработчик нажатия кнопки возврата.
     */
    void on_backButton_clicked();

private:
    /*!
     * @brief Указатель на пользовательский интерфейс окна.
     */
    Ui::WelcomeWindow *ui;
};

#endif // WELCOMEWINDOW_H