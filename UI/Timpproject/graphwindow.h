#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include <QVector>
#include <QColor>
#include <QMap>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
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
    void onExportPNG();
    void onExportPDF();
    void onSaveToFile();
    void onLoadFromFile();
    void onDeleteFromFile();
    void onClearGraph();
    void onColorButtonClicked();
    void onZoomChanged();

private:
    Ui::GraphWindow *ui;

    QVector<double> xDataSin;
    QVector<double> yDataSin;

    QVector<double> xDataSqrt;
    QVector<double> yDataSqrt;

    QVector<double> xDataFrac;
    QVector<double> yDataFrac;

    QMap<QString, QPair<QVector<double>, QVector<double>>> m_cache;

    QColor m_sinColor;
    QColor m_sqrtColor;
    QColor m_fracColor;

    QTimer* m_sessionCheckTimer;
    int m_sessionCheckInterval;

    QPushButton* m_exportPNGBtn;
    QPushButton* m_exportPDFBtn;
    QPushButton* m_saveBtn;
    QPushButton* m_loadBtn;
    QPushButton* m_deleteBtn;
    QPushButton* m_clearBtn;
    QPushButton* m_colorBtn;

    void parseServerData(const QString& response);
    void computeLocal(double a, double b, double c);
    double calculateFunction(double a, double b, double c, double x);
    void updateParameterLabels();
    void setupGraphStyle();
    void setupExportButtons();
    void setupZoomDrag();
    void setupKeyboardNav();
    void updateGraphColors();
    QString getCacheKey(double a, double b, double c);
    bool checkSessionValid();
};

#endif
