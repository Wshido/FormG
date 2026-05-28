#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#pragma once

#include <QWidget>
#include <QTcpSocket>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui
{
class GraphWindow;
}
QT_END_NAMESPACE

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

    QTcpSocket* socket;

    void drawGraph(QString response);

    // данные графиков

    QVector<double> x1, y1;

    QVector<double> x2, y2;

    QVector<double> x3, y3;
};

#endif