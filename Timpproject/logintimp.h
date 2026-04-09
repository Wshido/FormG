#ifndef LOGINTIMP_H
#define LOGINTIMP_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE

class LoginTimp : public QWidget
{
    Q_OBJECT

public:
    explicit LoginTimp(QWidget *parent = nullptr);
    ~LoginTimp();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Form *ui;
};

#endif // LOGINTIMP_H