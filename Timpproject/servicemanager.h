#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QString>

class ServiceManager : public QObject
{
    Q_OBJECT

public:
    static ServiceManager& instance();

    void connectToServer(const QString& host = "172.20.10.3", int port = 11999);
    void disconnectFromServer();
    bool isConnected() const;

    void sendAuth(const QString& login, const QString& password);
    void sendReg(const QString& login, const QString& password, const QString& email);
    void sendFunctionParams(double a, double b, double c);

    // НОВЫЕ МЕТОДЫ ДЛЯ ВОССТАНОВЛЕНИЯ ПАРОЛЯ
    void sendRequestCode(const QString& email);
    void sendChangePasswordWithCode(const QString& email, const QString& code, const QString& newPassword);

signals:
    void connected();
    void disconnected();
    void authResult(bool success, const QString& login);
    void regResult(bool success);
    void functionDataReceived(const QString& data);
    void error(const QString& message);

    // НОВЫЕ СИГНАЛЫ
    void codeRequestResult(bool success);
    void passwordChangeWithCodeResult(bool success);

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

private:
    explicit ServiceManager(QObject *parent = nullptr);
    ~ServiceManager();

    void sendRequest(const QString& request);

    QTcpSocket* m_socket;
};

#endif // SERVICEMANAGER_H