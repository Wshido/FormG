#ifndef LOGINTIMP_H
#define LOGINTIMP_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginTimp;
}
QT_END_NAMESPACE

class LoginTimp : public QDialog
{
    Q_OBJECT

public:
    explicit LoginTimp(QWidget *parent = nullptr);
    ~LoginTimp();

signals:
    void backRequested();  // Сигнал возврата к приветственному окну

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();

private slots:
    void on_forgotLabel_linkActivated(const QString &link);

private slots:
    void on_registerButton_clicked();
private:
    Ui::LoginTimp *ui;
};

#endif // LOGINTIMP_H