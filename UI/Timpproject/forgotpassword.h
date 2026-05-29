#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();

signals:
    void backRequested();

private slots:
    void on_sendButton_clicked();           // Шаг 1: запрос кода по логину
    void on_confirmCodeButton_clicked();    // Шаг 2: подтверждение кода
    void on_changePasswordButton_clicked(); // Шаг 3: смена пароля
    void on_backButton_clicked();

    void onCodeRequestResult(bool success);
    void onPasswordChangeResult(bool success);

private:
    Ui::ForgotPassword *ui;
    QString m_tempLogin;
    QString m_tempCode;
    QTimer m_codeTimer;
    int m_remainingSeconds;

    void startCodeTimer();
    void updateTimerDisplay();
    void showCodeInputStep();
    void showPasswordChangeStep();
};

#endif // FORGOTPASSWORD_H