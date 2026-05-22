#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutWindow;
}
QT_END_NAMESPACE

/*!
 * @brief Окно с информацией о программе.
 *
 * Класс отображает сведения о приложении и
 * обрабатывает действия пользователя в данном окне.
 */
class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    /*!
     * @brief Конструктор окна AboutWindow.
     * @param parent Родительский виджет.
     */
    explicit AboutWindow(QWidget *parent = nullptr);

    /*!
     * @brief Деструктор класса AboutWindow.
     */
    ~AboutWindow();

private slots:
    /*!
     * @brief Обработчик нажатия кнопки перехода.
     */
    void on_nextButton_clicked();

private:
    /*!
     * @brief Указатель на пользовательский интерфейс окна.
     */
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H