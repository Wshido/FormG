#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QWidget>

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
    void on_sendButton_clicked();
    void on_backButton_clicked();
    void on_confirmCodeButton_clicked();
    void on_changePasswordButton_clicked();

private:
    Ui::ForgotPassword *ui;
};

#endif