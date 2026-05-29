#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class ServiceManager : public QObject
{
    Q_OBJECT

public:
    static ServiceManager& instance();

    void connectToServer(const QString& host = "127.0.0.1", int port = 11999);
    void disconnectFromServer();
    bool isConnected() const;

    // Регистрация (2 шага)
    void sendRegRequestCode(const QString& email);
    void sendRegConfirm(const QString& login, const QString& password, const QString& email, const QString& code);

    // Авторизация (2 шага)
    void sendAuthRequestCode(const QString& login, const QString& password);
    void sendAuthConfirm(const QString& email, const QString& code);

    // Восстановление пароля (по логину)
    void sendRequestCode(const QString& login);
    void sendChangePasswordWithCode(const QString& login, const QString& code, const QString& newPassword);

    // Функция для графика
    void sendFunctionParams(double a, double b, double c);

    // Старые методы (для совместимости)
    void sendAuth(const QString& login, const QString& password);
    void sendReg(const QString& login, const QString& password, const QString& email);

signals:
    void connected();
    void disconnected();
    void error(const QString& message);

    // Сигналы для регистрации
    void regRequestCodeResult(bool success, const QString& code);
    void regConfirmResult(bool success);

    // Сигналы для авторизации
    void authRequestCodeResult(bool success, const QString& email, const QString& code);
    void authConfirmResult(bool success, const QString& sessionToken);

    // Сигналы для восстановления
    void codeRequestResult(bool success);
    void passwordChangeWithCodeResult(bool success);

    // Для графика
    void functionDataReceived(const QString& data);
    void authResult(bool success, const QString& login);

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
    QByteArray m_readBuffer;
    QByteArray m_graphDataBuffer;
    bool m_receivingGraphData;
};

#endif // SERVICEMANAGER_H