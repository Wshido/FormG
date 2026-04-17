#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class WelcomeWindow;
}
QT_END_NAMESPACE

class LoginTimp;

class WelcomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void on_nextButton_clicked();
    void on_backButton_clicked();

private:
    Ui::WelcomeWindow *ui;
    LoginTimp *loginWindow;
};

#endif // WELCOMEWINDOW_H