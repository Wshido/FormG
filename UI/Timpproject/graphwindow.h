#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
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

private:
    Ui::GraphWindow *ui;

    QVector<double> xDataSin;
    QVector<double> yDataSin;

    QVector<double> xDataSqrt;
    QVector<double> yDataSqrt;

    QVector<double> xDataFrac;
    QVector<double> yDataFrac;

    void parseServerData(const QString& response);
    void computeLocal(double a, double b, double c);
    double calculateFunction(double a, double b, double c, double x);
    void updateParameterLabels();
    void setupGraphStyle();
};

#endif
