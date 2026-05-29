#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QTimer>

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
    void on_getCodeButton_clicked();      // Кнопка "Получить код"
    void on_createButton_clicked();       // Кнопка "Зарегистрироваться" (createButton)
    void on_backButton_clicked();

    void onRegRequestCodeResult(bool success, const QString& code);
    void onRegConfirmResult(bool success);

private:
    Ui::RegisterWindow *ui;

    QString m_tempLogin;
    QString m_tempPassword;
    QString m_tempEmail;
    QString m_tempCode;

    QTimer m_codeTimer;
    int m_remainingSeconds;

    void startCodeTimer();
    void updateTimerDisplay();
};

#endif // REGISTERWINDOW_H