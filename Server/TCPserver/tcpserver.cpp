#include "tcpserver.h"
#include <QDebug>
#include <QByteArray>
#include <cstdio>
#include <cstring>
#include <cmath>

// ClientHandler implementation
ClientHandler::ClientHandler(qintptr socketDescriptor, Controller *controller, QObject *parent)
    : QObject(parent)
    , m_socketDescriptor(socketDescriptor)
    , m_controller(controller)
{
}

void ClientHandler::process()
{
    m_socket = new QTcpSocket(this);
    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
        qDebug() << "Ошибка установки дескриптора сокета";
        deleteLater();
        return;
    }

    connect(m_socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);

    qDebug() << "Клиент подключен:" << m_socket->peerAddress().toString();
}

void ClientHandler::onReadyRead()
{
    QByteArray data = m_socket->readAll();

    if (data.isEmpty()) return;

    char type = data[0];

    if (type == 'F') {
        qDebug() << "Получен бинарный запрос на построение графика";

        if (data.size() >= 1 + static_cast<int>(sizeof(double) * 4)) {
            double values[4];
            std::memcpy(values, data.constData() + 1, sizeof(double) * 4);
            double a = values[0];
            double b = values[1];
            double c = values[2];
            double step = values[3];

            qDebug() << "Параметры: a=" << a << "b=" << b << "c=" << c << "step=" << step;

            QByteArray response;
            response.reserve(65536);

            int count1 = 0, count2 = 0, count3 = 0;

            char numBuf[64];

            for (double x = -10.0; x <= 10.0 + 1e-9; x += step) {
                double y = m_controller->calculateFunction(a, b, c, x);

                int len1 = std::snprintf(numBuf, sizeof(numBuf), "%.6f %.6f\n", x, y);

                if (x < 0) {
                    response.append('1');
                    response.append(' ');
                    response.append(numBuf, len1);
                    count1++;
                } else if (x < 1) {
                    response.append('2');
                    response.append(' ');
                    response.append(numBuf, len1);
                    count2++;
                } else {
                    response.append('3');
                    response.append(' ');
                    response.append(numBuf, len1);
                    count3++;
                }
            }

            qDebug() << "Отправлено точек: ф1=" << count1 << "ф2=" << count2 << "ф3=" << count3;
            qDebug() << "Размер ответа:" << response.size() << "байт";

            m_socket->write(response);
            m_socket->flush();
        } else {
            qDebug() << "Недостаточно данных! Получено:" << data.size() << "байт, нужно 33";
        }
    }
    else {
        QString request = QString::fromUtf8(data).trimmed();
        qDebug() << "Текстовый запрос:" << request;

        QString response = m_controller->process(request);

        m_socket->write(response.toUtf8() + "\n");
        m_socket->flush();
    }
}

void ClientHandler::onDisconnected()
{
    qDebug() << "Клиент отключен:" << m_socket->peerAddress().toString();
    m_socket->deleteLater();
    deleteLater();
}

// TCPServer implementation
TCPServer::TCPServer(QObject *parent)
    : QTcpServer(parent)
{
}

void TCPServer::setSmtpConfig(const QString &host, quint16 port,
                               const QString &user, const QString &pass,
                               const QString &from)
{
    m_controller.setSmtpConfig(host, port, user, pass, from);
}

bool TCPServer::start(quint16 port)
{
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Ошибка запуска сервера:" << errorString();
        return false;
    }
    qDebug() << "Сервер запущен на порту" << port;
    return true;
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    ClientHandler *handler = new ClientHandler(socketDescriptor, &m_controller);
    QThread *thread = new QThread(this);

    handler->moveToThread(thread);

    connect(thread, &QThread::started, handler, &ClientHandler::process);
    connect(handler, &ClientHandler::destroyed, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}
