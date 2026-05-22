#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>

#include "qcustomplot.h"

namespace Ui {
class GraphWindow;
}

/*!
 * @brief Окно отображения графиков.
 *
 * Класс предназначен для получения данных по сети
 * и построения графиков с использованием библиотеки QCustomPlot.
 */
class GraphWindow : public QWidget
{
    Q_OBJECT

public:
    /*!
     * @brief Конструктор окна GraphWindow.
     * @param parent Родительский виджет.
     */
    explicit GraphWindow(QWidget *parent = nullptr);

    /*!
     * @brief Деструктор класса GraphWindow.
     */
    ~GraphWindow();

private slots:
    /*!
     * @brief Обработчик изменения значения слайдера.
     *
     * Используется для обновления параметров графика.
     */
    void onSliderChanged();

    /*!
     * @brief Обработчик поступления данных от сокета.
     *
     * Выполняет чтение входящих данных и обновление графика.
     */
    void onReadyRead();

private:
    /*!
     * @brief Указатель на пользовательский интерфейс окна.
     */
    Ui::GraphWindow *ui;

    /*!
     * @brief TCP-сокет для получения данных.
     */
    QTcpSocket *socket = nullptr;

    /*!
     * @brief Буфер для хранения входящих данных.
     */
    QByteArray buffer;

    /*!
     * @brief Массив параметров для построения графика.
     */
    double data[4] = {1, 2, 3, 0.01};

    /*!
     * @brief Массив данных по оси X.
     */
    QVector<double> xData;

    /*!
     * @brief Массив данных по оси Y.
     */
    QVector<double> yData;
};

#endif