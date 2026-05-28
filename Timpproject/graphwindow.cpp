#include "graphwindow.h"
#include "ui_graphwindow.h"

#include <QDebug>
#include <QTcpSocket>
#include <QSlider>

GraphWindow::GraphWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    ui->tableWidget
        ->setColumnCount(2);

    QStringList headers;

    headers << "X" << "Y";

    ui->tableWidget
        ->setHorizontalHeaderLabels(headers);

    // убрать номера строк
    ui->tableWidget
        ->verticalHeader()
        ->setVisible(false);

    socket = new QTcpSocket(this);

    // подключение к серверу
    socket->connectToHost("127.0.0.1", 11999);

    connect(socket,
            &QTcpSocket::readyRead,
            this,
            &GraphWindow::onReadyRead);

    connect(socket,
            &QTcpSocket::connected,
            this,
            []()
            {
                qDebug() << "Connected";
            });

    // ===== ГРАФИКИ =====

    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();

    ui->customPlot->xAxis->setRange(-10, 10);
    ui->customPlot->yAxis->setRange(-10, 10);

    // ===== СЛАЙДЕРЫ =====

    connect(ui->sliderSin,
            &QSlider::valueChanged,
            this,
            &GraphWindow::onSliderChanged);

    connect(ui->sliderSqrt,
            &QSlider::valueChanged,
            this,
            &GraphWindow::onSliderChanged);

    connect(ui->sliderFrac,
            &QSlider::valueChanged,
            this,
            &GraphWindow::onSliderChanged);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::onReadyRead()
{
    QString response =
        QString::fromUtf8(
            socket->readAll());

    drawGraph(response);
}

void GraphWindow::onSliderChanged()
{
    if(socket->state()
        != QAbstractSocket::ConnectedState)
    {
        return;
    }

    double data[4];

    data[0] =
        ui->sliderSin->value() / 2.0;

    data[1] =
        ui->sliderSqrt->value() / 5.0;

    data[2] =
        ui->sliderFrac->value() / 5.0;

    data[3] = 0.1;

    QByteArray arr;

    // тип запроса
    arr.append('F');

    // параметры
    arr.append(
        (char*)data,
        sizeof(data));

    socket->write(arr);
}

void GraphWindow::drawGraph(
    QString response)
{
    x1.clear();
    y1.clear();

    x2.clear();
    y2.clear();

    x3.clear();
    y3.clear();

    QStringList lines =
        response.split("\n",
                       Qt::SkipEmptyParts);

    // очищаем таблицу
    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(0);

    int row = 0;

    for(QString line : lines)
    {
        QStringList values =
            line.split(" ");

        // type x y
        if(values.size() != 3)
            continue;

        int type =
            values[0].toInt();

        double x =
            values[1].toDouble();

        double y =
            values[2].toDouble();

        // ===== ТАБЛИЦА =====

        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(
            row,
            0,
            new QTableWidgetItem(
                QString::number(x)));

        ui->tableWidget->setItem(
            row,
            1,
            new QTableWidgetItem(
                QString::number(y)));

        row++;

        // ===== ГРАФИКИ =====

        if(type == 1)
        {
            x1.push_back(x);
            y1.push_back(y);
        }

        else if(type == 2)
        {
            x2.push_back(x);
            y2.push_back(y);
        }

        else if(type == 3)
        {
            x3.push_back(x);
            y3.push_back(y);
        }
    }

    // graph 1

    ui->customPlot
        ->graph(0)
        ->setData(x1, y1);

    // graph 2

    ui->customPlot
        ->graph(1)
        ->setData(x2, y2);

    // graph 3

    ui->customPlot
        ->graph(2)
        ->setData(x3, y3);

    ui->customPlot->replot();
}