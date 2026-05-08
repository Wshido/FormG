#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>

#include "qcustomplot.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

private slots:
    void onSliderChanged();
    void onReadyRead();

private:
    Ui::GraphWindow *ui;

    QTcpSocket *socket = nullptr;
    QByteArray buffer;

    double data[4] = {1, 2, 3, 0.01};

    QVector<double> xData;
    QVector<double> yData;
};

#endif