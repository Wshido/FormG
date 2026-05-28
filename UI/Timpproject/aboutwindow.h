#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutWindow;
}
QT_END_NAMESPACE

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private slots:
    void on_nextButton_clicked();

private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H