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
    Q_OBJECT   // ← Этот макрос ОБЯЗАТЕЛЕН

public:
    explicit LoginTimp(QWidget *parent = nullptr);
    ~LoginTimp();

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();
    void on_forgotLabel_linkActivated(const QString &link);
    void on_registerButton_clicked();

    void onAuthResult(bool success, const QString& login);

private:
    Ui::LoginTimp *ui;
};

#endif // LOGINTIMP_H