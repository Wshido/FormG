#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

signals:
    void backRequested();

private slots:
    void on_createButton_clicked();
    void on_backButton_clicked();

private:
    Ui::RegisterWindow *ui;
};

#endif