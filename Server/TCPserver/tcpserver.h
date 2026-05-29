#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMap>
#include "controller.h"

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(qintptr socketDescriptor, Controller *controller, QObject *parent = nullptr);

public slots:
    void process();

signals:
    void clientDisconnected(const QString &login);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_socket;
    qintptr m_socketDescriptor;
    Controller *m_controller;
    QString m_currentLogin;
};

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    bool start(quint16 port);
    void setSmtpConfig(const QString &host, quint16 port,
                       const QString &user, const QString &pass,
                       const QString &from);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    Controller m_controller;
};

#endif // TCPSERVER_H
