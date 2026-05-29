#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class WelcomeWindow;
}
QT_END_NAMESPACE


class WelcomeWindow : public QWidget
{
    Q_OBJECT
signals:
    void backRequested();
    void logoutRequested();
public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void on_nextButton_clicked();
    void on_backButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::WelcomeWindow *ui;
};


#endif // WELCOMEWINDOW_H
