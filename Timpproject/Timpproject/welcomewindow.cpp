#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "graphwindow.h"
#include <QPixmap>

/*!
 * @brief Конструктор приветственного окна.
 * @param parent Родительский виджет.
 */
WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::WelcomeWindow)
{
    // Инициализация пользовательского интерфейса
    ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(900, 600);

    // Загрузка изображений
    QPixmap img1("funcqt.png");
    QPixmap img2("uniqueqt.png");

    // Отображение первого изображения
    ui->imageLabel1->setPixmap(
        img1.scaled(
            350,
            200,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );

    // Отображение второго изображения
    ui->imageLabel2->setPixmap(
        img2.scaled(
            450,
            200,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
}

/*!
 * @brief Деструктор класса WelcomeWindow.
 */
WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

/*!
 * @brief Обработчик кнопки перехода.
 *
 * Открывает окно построения графиков.
 */
void WelcomeWindow::on_nextButton_clicked()
{
    // Создание окна графиков
    GraphWindow *gw = new GraphWindow();

    // Отображение окна графиков
    gw->show();

    // Скрытие текущего окна
    this->hide();
}

/*!
 * @brief Обработчик кнопки возврата.
 *
 * Выполняет возврат к предыдущему окну.
 */
void WelcomeWindow::on_backButton_clicked()
{
    emit backRequested();

    // Скрытие текущего окна
    this->hide();
}