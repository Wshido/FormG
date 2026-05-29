#ifndef LOGINTIMP_H
#define LOGINTIMP_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class LoginTimp;
}

class LoginTimp : public QDialog
{
    Q_OBJECT

public:
    explicit LoginTimp(QWidget *parent = nullptr);
    ~LoginTimp();

private slots:
    void on_loginButton_clicked();           // Шаг 1: ввод логина/пароля
    void on_confirmCodeButton_clicked();     // Шаг 2: подтверждение кода
    void on_backButton_clicked();
    void on_forgotLabel_linkActivated(const QString &link);
    void on_registerButton_clicked();

    void onAuthRequestCodeResult(bool success, const QString& email, const QString& code);
    void onAuthConfirmResult(bool success, const QString& sessionToken);

private:
    Ui::LoginTimp *ui;
    QString m_tempEmail;
    QString m_tempCode;
    QTimer m_codeTimer;
    int m_remainingSeconds;

    void startCodeTimer();
    void updateTimerDisplay();
};

#endif // LOGINTIMP_H