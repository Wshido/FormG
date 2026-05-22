#ifndef MAINTIMP_H
#define MAINTIMP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainTimp;
}
QT_END_NAMESPACE

/*!
 * @brief Главное окно приложения.
 *
 * Класс представляет основной интерфейс программы
 * и содержит главный функционал приложения.
 */
class MainTimp : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * @brief Конструктор главного окна.
     * @param parent Родительский виджет.
     */
    explicit MainTimp(QWidget *parent = nullptr);

    /*!
     * @brief Деструктор главного окна.
     */
    ~MainTimp() override;

private:
    /*!
     * @brief Указатель на пользовательский интерфейс окна.
     */
    Ui::MainTimp *ui;
};

#endif // MAINTIMP_H