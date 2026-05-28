#include "servicemanager.h"

ServiceManager& ServiceManager::instance()
{
    static ServiceManager instance;
    return instance;
}

ServiceManager::ServiceManager(QObject *parent)
    : QObject(parent)
    , m_socket(nullptr)
{
}

ServiceManager::~ServiceManager()
{
    disconnectFromServer();
}

void ServiceManager::connectToServer(const QString& host, int port)
{
    if (m_socket) {
        disconnectFromServer();
    }

    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &ServiceManager::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ServiceManager::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ServiceManager::onReadyRead);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &ServiceManager::onError);

    qDebug() << "Подключение к серверу:" << host << ":" << port;
    m_socket->connectToHost(host, port);
}

void ServiceManager::disconnectFromServer()
{
    if (m_socket) {
        m_socket->disconnectFromHost();
        m_socket->deleteLater();
        m_socket = nullptr;
    }
}

bool ServiceManager::isConnected() const
{
    return m_socket && m_socket->state() == QTcpSocket::ConnectedState;
}

void ServiceManager::sendRequest(const QString& request)
{
    if (!isConnected()) {
        emit error("Не подключен к серверу");
        return;
    }

    qDebug() << "Отправка:" << request;
    m_socket->write(request.toUtf8());
    m_socket->flush();
}

void ServiceManager::sendAuth(const QString& login, const QString& password)
{
    QString request = QString("auth&%1&%2").arg(login).arg(password);
    sendRequest(request);
}

void ServiceManager::sendReg(const QString& login, const QString& password, const QString& email)
{
    QString request = QString("reg&%1&%2&%3").arg(login).arg(password).arg(email);
    sendRequest(request);
}

void ServiceManager::sendFunctionParams(double a, double b, double c)
{
    QString request = QString("func&%1&%2&%3").arg(a).arg(b).arg(c);
    sendRequest(request);
}

// НОВЫЙ МЕТОД: запрос кода подтверждения
void ServiceManager::sendRequestCode(const QString& email)
{
    QString request = QString("request_code&%1").arg(email);
    sendRequest(request);
}

// НОВЫЙ МЕТОД: смена пароля с кодом
void ServiceManager::sendChangePasswordWithCode(const QString& email, const QString& code, const QString& newPassword)
{
    QString request = QString("changepass_code&%1&%2&%3").arg(email).arg(code).arg(newPassword);
    sendRequest(request);
}

void ServiceManager::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    QString response = QString::fromUtf8(data);

    qDebug() << "Получено:" << response;

    QStringList parts = response.split('&');

    if (parts[0] == "auth+") {
        emit authResult(true, parts[1]);
    }
    else if (parts[0] == "auth-") {
        emit authResult(false, "");
    }
    else if (parts[0] == "reg+") {
        emit regResult(true);
    }
    else if (parts[0] == "reg-") {
        emit regResult(false);
    }
    // НОВЫЕ ОБРАБОТЧИКИ
    else if (parts[0] == "code_sent+") {
        emit codeRequestResult(true);
    }
    else if (parts[0] == "code_sent-") {
        emit codeRequestResult(false);
    }
    else if (parts[0] == "changepass+") {
        emit passwordChangeWithCodeResult(true);
    }
    else if (parts[0] == "changepass-") {
        emit passwordChangeWithCodeResult(false);
    }
    else {
        emit functionDataReceived(response);
    }
}

void ServiceManager::onConnected()
{
    qDebug() << "Подключен к серверу";
    emit connected();
}

void ServiceManager::onDisconnected()
{
    qDebug() << "Отключен от сервера";
    emit disconnected();
}

void ServiceManager::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug() << "Ошибка сокета:" << m_socket->errorString();
    emit error(m_socket->errorString());
}