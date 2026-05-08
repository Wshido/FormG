#include "graphwindow.h"
#include "ui_graphwindow.h"

#include <QSlider>
#include <QAbstractSocket>
#include <QDebug>

GraphWindow::GraphWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead,
            this, &GraphWindow::onReadyRead);

    connect(socket, &QTcpSocket::connected, this, [](){
        qDebug() << "Connected";
    });

    socket->connectToHost("127.0.0.1", 11999);

    // QCustomPlot init
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");

    connect(ui->sliderSin, &QSlider::valueChanged,
            this, &GraphWindow::onSliderChanged);

    connect(ui->sliderSqrt, &QSlider::valueChanged,
            this, &GraphWindow::onSliderChanged);

    connect(ui->sliderFrac, &QSlider::valueChanged,
            this, &GraphWindow::onSliderChanged);
}

void GraphWindow::onReadyRead()
{
    buffer += socket->readAll();

    // Временные векторы для новых данных
    QVector<double> newXData;
    QVector<double> newYData;

    while (buffer.contains('\n'))
    {
        int idx = buffer.indexOf('\n');
        QByteArray line = buffer.left(idx);
        buffer = buffer.mid(idx + 1);

        if (line.isEmpty())
            continue;

        auto parts = line.split(' ');
        if (parts.size() != 2)
            continue;

        bool ok1 = false, ok2 = false;
        double x = parts[0].toDouble(&ok1);
        double y = parts[1].toDouble(&ok2);

        if (!ok1 || !ok2)
            continue;

        newXData.push_back(x);
        newYData.push_back(y);
    }

    // Полностью заменяем старые данные новыми
    if (!newXData.isEmpty())
    {
        xData = newXData;
        yData = newYData;

        ui->customPlot->graph(0)->setData(xData, yData);
        ui->customPlot->xAxis->setRange(-10, 10);
        ui->customPlot->yAxis->setRange(-10, 10);
        ui->customPlot->replot();
    }
}

void GraphWindow::onSliderChanged()
{
    if (socket->state() != QAbstractSocket::ConnectedState)
        return;

    data[0] = ui->sliderSin->value() / 2.0;
    data[1] = ui->sliderSqrt->value() / 5.0;
    data[2] = ui->sliderFrac->value() / 5.0;
    data[3] = 0.01;

    socket->write(reinterpret_cast<char*>(data), sizeof(data));
    socket->flush();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}