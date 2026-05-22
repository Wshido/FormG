#include "maintimp.h"
#include "ui_maintimp.h"

/*!
 * @brief Конструктор главного окна приложения.
 * @param parent Родительский виджет.
 */
MainTimp::MainTimp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainTimp)
{
    // Инициализация пользовательского интерфейса
    ui->setupUi(this);
}

/*!
 * @brief Деструктор класса MainTimp.
 */
MainTimp::~MainTimp()
{
    // Освобождение памяти интерфейса
    delete ui;
}