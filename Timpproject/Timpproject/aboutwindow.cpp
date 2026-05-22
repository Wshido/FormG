#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "logintimp.h"
#include "welcomewindow.h"

/*!
 * @brief Конструктор окна AboutWindow.
 * @param parent Родительский виджет.
 */
AboutWindow::AboutWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(900, 600);
}

/*!
 * @brief Деструктор класса AboutWindow.
 */
AboutWindow::~AboutWindow()
{
    delete ui;
}

/*!
 * @brief Обработчик нажатия кнопки перехода.
 *
 * Открывает окно авторизации пользователя.
 * При успешном входе отображается приветственное окно.
 */
void AboutWindow::on_nextButton_clicked()
{
    LoginTimp login(this);

    // Запуск диалогового окна авторизации
    int result = login.exec();

    if (result == QDialog::Accepted) {

        // Создание и отображение приветственного окна
        WelcomeWindow *ww = new WelcomeWindow();

        ww->show();

        // Скрытие текущего окна
        this->hide();
    }
}