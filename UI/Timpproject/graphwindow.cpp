#include "graphwindow.h"
#include "ui_graphwindow.h"
#include "servicemanager.h"
#include <QSlider>
#include <QAbstractSocket>
#include <QDebug>
#include <cmath>

GraphWindow::GraphWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    setupGraphStyle();

    connect(&ServiceManager::instance(), &ServiceManager::functionDataReceived,
            this, &GraphWindow::parseServerData);

    if (!ServiceManager::instance().isConnected()) {
        ServiceManager::instance().connectToServer("127.0.0.1", 11999);
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor(231, 76, 60), 2.5));
    ui->customPlot->graph(0)->setName("sin(ax)");

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(QColor(46, 204, 113), 2.5));
    ui->customPlot->graph(1)->setName("sqrt(x+b)");

    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(QColor(52, 152, 219), 2.5));
    ui->customPlot->graph(2)->setName("1/(x-c)");

    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");
    ui->customPlot->xAxis->setRange(-10, 10);
    ui->customPlot->yAxis->setRange(-10, 10);

    ui->customPlot->setInteraction(QCP::iRangeZoom, false);
    ui->customPlot->setInteraction(QCP::iRangeDrag, false);

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 220)));
    ui->customPlot->legend->setBorderPen(QPen(QColor(200, 200, 200)));
    ui->customPlot->legend->setFont(QFont("Segoe UI", 10));
    ui->customPlot->legend->setRowSpacing(6);

    ui->customPlot->xAxis->setBasePen(QPen(QColor(150, 150, 150)));
    ui->customPlot->yAxis->setBasePen(QPen(QColor(150, 150, 150)));
    ui->customPlot->xAxis->setTickPen(QPen(QColor(150, 150, 150)));
    ui->customPlot->yAxis->setTickPen(QPen(QColor(150, 150, 150)));
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(230, 230, 230)));
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(230, 230, 230)));
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(240, 240, 240)));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(240, 240, 240)));

    connect(ui->sliderSin, &QSlider::valueChanged, this, &GraphWindow::onSliderChanged);
    connect(ui->sliderSqrt, &QSlider::valueChanged, this, &GraphWindow::onSliderChanged);
    connect(ui->sliderFrac, &QSlider::valueChanged, this, &GraphWindow::onSliderChanged);

    ui->sliderSin->setValue(1);
    ui->sliderSqrt->setValue(1);
    ui->sliderFrac->setValue(1);
}

void GraphWindow::setupGraphStyle()
{
    setStyleSheet(
        "QWidget { background-color: #f5f7fa; font-family: 'Segoe UI', Arial; }"
        "QLabel { color: #2c3e50; background: transparent; }"
    );
}

void GraphWindow::updateParameterLabels()
{
    double a = ui->sliderSin->value();
    double b = ui->sliderSqrt->value();
    double c = ui->sliderFrac->value();

    ui->labelSinValue->setText(QString("a = %1").arg(a));
    ui->labelSqrtValue->setText(QString("b = %1").arg(b));
    ui->labelFracValue->setText(QString("c = %1").arg(c));
}

double GraphWindow::calculateFunction(double a, double b, double c, double x)
{
    if (x < 0) {
        return sin(a * x);
    } else if (x < 1) {
        if (b * x < 0) return 0;
        return sqrt(b * x);
    } else {
        if (fabs(c * x - 1.0) < 0.0001) return 0;
        return 1.0 / (c * x - 1.0);
    }
}

void GraphWindow::computeLocal(double a, double b, double c)
{
    double step = 0.05;
    QVector<double> x1, y1, x2, y2, x3, y3;

    for (double x = -10.0; x <= 10.0; x += step) {
        double y = calculateFunction(a, b, c, x);

        if (y < -10 || y > 10 || std::isnan(y) || std::isinf(y)) continue;

        if (x < 0) {
            x1.append(x);
            y1.append(y);
        } else if (x < 1) {
            x2.append(x);
            y2.append(y);
        } else {
            x3.append(x);
            y3.append(y);
        }
    }

    if (!x1.isEmpty())
        ui->customPlot->graph(0)->setData(x1, y1);
    if (!x2.isEmpty())
        ui->customPlot->graph(1)->setData(x2, y2);
    if (!x3.isEmpty())
        ui->customPlot->graph(2)->setData(x3, y3);

    ui->customPlot->xAxis->setRange(-10, 10);
    ui->customPlot->yAxis->rescale();
    QCPRange yRange = ui->customPlot->yAxis->range();
    if (yRange.lower < -10) yRange.lower = -10;
    if (yRange.upper > 10) yRange.upper = 10;
    ui->customPlot->yAxis->setRange(yRange);

    ui->customPlot->replot();
}

void GraphWindow::parseServerData(const QString& response)
{
    if (response.isEmpty()) return;

    xDataSin.clear();
    yDataSin.clear();
    xDataSqrt.clear();
    yDataSqrt.clear();
    xDataFrac.clear();
    yDataFrac.clear();

    QStringList lines = response.split('\n', Qt::SkipEmptyParts);

    for (int i = 0; i < lines.size(); ++i) {
        QStringList parts = lines[i].split(' ', Qt::SkipEmptyParts);

        if (parts.size() != 3) continue;

        bool ok1, ok2, ok3;
        int type = parts[0].toInt(&ok1);
        double x = parts[1].toDouble(&ok2);
        double y = parts[2].toDouble(&ok3);

        if (!ok1 || !ok2 || !ok3) continue;

        if (y < -10 || y > 10 || std::isnan(y) || std::isinf(y)) continue;

        if (type == 1) {
            xDataSin.append(x);
            yDataSin.append(y);
        } else if (type == 2) {
            xDataSqrt.append(x);
            yDataSqrt.append(y);
        } else if (type == 3) {
            xDataFrac.append(x);
            yDataFrac.append(y);
        }
    }

    if (!xDataSin.isEmpty())
        ui->customPlot->graph(0)->setData(xDataSin, yDataSin);
    if (!xDataSqrt.isEmpty())
        ui->customPlot->graph(1)->setData(xDataSqrt, yDataSqrt);
    if (!xDataFrac.isEmpty())
        ui->customPlot->graph(2)->setData(xDataFrac, yDataFrac);

    ui->customPlot->xAxis->setRange(-10, 10);

    ui->customPlot->yAxis->rescale();
    QCPRange yRange = ui->customPlot->yAxis->range();
    if (yRange.lower < -10) yRange.lower = -10;
    if (yRange.upper > 10) yRange.upper = 10;
    ui->customPlot->yAxis->setRange(yRange);

    ui->customPlot->replot();
}

void GraphWindow::onSliderChanged()
{
    double a = ui->sliderSin->value();
    double b = ui->sliderSqrt->value();
    double c = ui->sliderFrac->value();

    updateParameterLabels();

    computeLocal(a, b, c);

    if (ServiceManager::instance().isConnected()) {
        ServiceManager::instance().sendFunctionParams(a, b, c);
    }
}

GraphWindow::~GraphWindow()
{
    delete ui;
}
