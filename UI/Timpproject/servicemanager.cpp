#include "servicemanager.h"

ServiceManager& ServiceManager::instance()
{
    static ServiceManager instance;
    return instance;
}

ServiceManager::ServiceManager(QObject *parent)
    : QObject(parent)
    , m_socket(nullptr)
    , m_receivingGraphData(false)
    , m_reconnectAttempts(0)
    , m_reconnectTimer(nullptr)
    , m_host("127.0.0.1")
    , m_port(11999)
{
    m_reconnectTimer = new QTimer(this);
    connect(m_reconnectTimer, &QTimer::timeout, this, &ServiceManager::onReconnectTimer);
}

ServiceManager::~ServiceManager()
{
    if (m_reconnectTimer) {
        m_reconnectTimer->stop();
    }
    disconnectFromServer();
}

void ServiceManager::connectToServer(const QString& host, int port)
{
    m_host = host;
    m_port = port;

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
    m_reconnectAttempts = MAX_RECONNECT_ATTEMPTS;

    if (m_reconnectTimer) {
        m_reconnectTimer->stop();
    }

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
    m_socket->write(request.toUtf8() + "\n");
    m_socket->flush();
}

// ========== РЕГИСТРАЦИЯ (2 шага) ==========
void ServiceManager::sendRegRequestCode(const QString& email)
{
    QString request = QString("reg_request_code&%1").arg(email);
    sendRequest(request);
}

void ServiceManager::sendRegConfirm(const QString& login, const QString& password, const QString& email, const QString& code)
{
    QString request = QString("reg_confirm&%1&%2&%3&%4").arg(login).arg(password).arg(email).arg(code);
    sendRequest(request);
}

// ========== АВТОРИЗАЦИЯ (2 шага) ==========
void ServiceManager::sendAuthRequestCode(const QString& login, const QString& password)
{
    QString request = QString("auth_request_code&%1&%2").arg(login).arg(password);
    sendRequest(request);
}

void ServiceManager::sendAuthConfirm(const QString& email, const QString& code)
{
    QString request = QString("auth_confirm&%1&%2").arg(email).arg(code);
    sendRequest(request);
}

// ========== ВОССТАНОВЛЕНИЕ ПАРОЛЯ (по ЛОГИНУ) ==========
void ServiceManager::sendRequestCode(const QString& login)
{
    QString request = QString("reset_request_code&%1").arg(login);
    sendRequest(request);
}

void ServiceManager::sendChangePasswordWithCode(const QString& login, const QString& code, const QString& newPassword)
{
    QString request = QString("reset_confirm&%1&%2&%3").arg(login).arg(code).arg(newPassword);
    sendRequest(request);
}

// ========== LOGOUT ==========
void ServiceManager::sendLogout(const QString& login)
{
    QString request = QString("logout&%1").arg(login);
    sendRequest(request);
    m_currentLogin.clear();
    m_currentToken.clear();
}

void ServiceManager::sendLogoutAll(const QString& login)
{
    QString request = QString("logout_all&%1").arg(login);
    sendRequest(request);
    m_currentLogin.clear();
    m_currentToken.clear();
}

// ========== REFRESH TOKEN ==========
void ServiceManager::sendRefreshToken(const QString& login, const QString& oldToken)
{
    QString request = QString("refresh_token&%1&%2").arg(login).arg(oldToken);
    sendRequest(request);
}

// ========== SESSION ==========
void ServiceManager::setCurrentLogin(const QString& login)
{
    m_currentLogin = login;
}

QString ServiceManager::currentLogin() const
{
    return m_currentLogin;
}

void ServiceManager::setCurrentToken(const QString& token)
{
    m_currentToken = token;
}

QString ServiceManager::currentToken() const
{
    return m_currentToken;
}

// ========== ДЛЯ ГРАФИКА ==========
void ServiceManager::sendFunctionParams(double a, double b, double c)
{
    double step = 0.1;
    QByteArray sendData;
    sendData.append('F');
    sendData.append(reinterpret_cast<const char*>(&a), sizeof(double));
    sendData.append(reinterpret_cast<const char*>(&b), sizeof(double));
    sendData.append(reinterpret_cast<const char*>(&c), sizeof(double));
    sendData.append(reinterpret_cast<const char*>(&step), sizeof(double));

    if (isConnected()) {
        m_socket->write(sendData);
        m_socket->flush();
    }
}

// ========== СТАРЫЕ МЕТОДЫ (для совместимости) ==========
void ServiceManager::sendAuth(const QString& login, const QString& password)
{
    Q_UNUSED(login)
    Q_UNUSED(password)
    sendAuthRequestCode(login, password);
}

void ServiceManager::sendReg(const QString& login, const QString& password, const QString& email)
{
    Q_UNUSED(login)
    Q_UNUSED(password)
    sendRegRequestCode(email);
}

// ========== AUTO-RECONNECT ==========
void ServiceManager::attemptReconnect()
{
    if (m_reconnectAttempts >= MAX_RECONNECT_ATTEMPTS) {
        qDebug() << "Превышено максимальное количество попыток переподключения";
        if (m_reconnectTimer) {
            m_reconnectTimer->stop();
        }
        emit connectionFailed();
        return;
    }

    m_reconnectAttempts++;
    qDebug() << "Попытка переподключения #" << m_reconnectAttempts;

    emit reconnecting();

    if (m_socket) {
        m_socket->deleteLater();
        m_socket = nullptr;
    }

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &ServiceManager::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ServiceManager::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ServiceManager::onReadyRead);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &ServiceManager::onError);

    m_socket->connectToHost(m_host, m_port);
}

void ServiceManager::onReconnectTimer()
{
    attemptReconnect();
}

void ServiceManager::onReadyRead()
{
    m_readBuffer.append(m_socket->readAll());

    while (m_readBuffer.contains('\n')) {
        int idx = m_readBuffer.indexOf('\n');
        QByteArray line = m_readBuffer.left(idx);
        m_readBuffer.remove(0, idx + 1);

        QString response = QString::fromUtf8(line).trimmed();
        if (response.isEmpty()) continue;

        qDebug() << "Получено:" << response;

        // Graph data lines start with "1 ", "2 ", or "3 "
        if (response.startsWith("1 ") || response.startsWith("2 ") || response.startsWith("3 ")) {
            if (!m_receivingGraphData) {
                m_receivingGraphData = true;
                m_graphDataBuffer.clear();
            }
            m_graphDataBuffer.append((response + "\n").toUtf8());
            continue;
        }

        // If we were accumulating graph data, emit it now
        if (m_receivingGraphData) {
            emit functionDataReceived(QString::fromUtf8(m_graphDataBuffer));
            m_graphDataBuffer.clear();
            m_receivingGraphData = false;
        }

        QStringList parts = response.split('&');

        if (parts[0] == "reg_request_code+") {
            emit regRequestCodeResult(true, "");
        }
        else if (parts[0] == "reg_request_code-") {
            emit regRequestCodeResult(false, "");
        }
        else if (parts[0] == "reg_confirm+") {
            emit regConfirmResult(true);
        }
        else if (parts[0] == "reg_confirm-") {
            emit regConfirmResult(false);
        }
        else if (parts[0] == "auth_request_code+") {
            QString email = parts.size() > 1 ? parts[1] : "";
            emit authRequestCodeResult(true, email, "");
        }
        else if (parts[0] == "auth_request_code-") {
            emit authRequestCodeResult(false, "", "");
        }
        else if (parts[0] == "auth_confirm+") {
            QString sessionToken = parts.size() > 1 ? parts[1] : "";
            emit authConfirmResult(true, sessionToken);
            emit authResult(true, "");
        }
        else if (parts[0] == "auth_confirm-") {
            emit authConfirmResult(false, "");
            emit authResult(false, "");
        }
        else if (parts[0] == "reset_request_code+") {
            emit codeRequestResult(true);
        }
        else if (parts[0] == "reset_request_code-") {
            emit codeRequestResult(false);
        }
        else if (parts[0] == "reset_confirm+") {
            emit passwordChangeWithCodeResult(true);
        }
        else if (parts[0] == "reset_confirm-") {
            emit passwordChangeWithCodeResult(false);
        }
        else if (parts[0] == "logout+") {
            emit logoutResult(true);
        }
        else if (parts[0] == "logout-") {
            emit logoutResult(false);
        }
        else if (parts[0] == "logout_all+") {
            emit logoutAllResult(true);
        }
        else if (parts[0] == "logout_all-") {
            emit logoutAllResult(false);
        }
        else if (parts[0] == "refresh_token+") {
            QString newToken = parts.size() > 1 ? parts[1] : "";
            m_currentToken = newToken;
            emit refreshTokenResult(true, newToken);
        }
        else if (parts[0] == "refresh_token-") {
            emit refreshTokenResult(false, "");
        }
        else {
            emit functionDataReceived(response);
        }
    }

    // Emit any remaining graph data
    if (m_receivingGraphData && !m_graphDataBuffer.isEmpty()) {
        emit functionDataReceived(QString::fromUtf8(m_graphDataBuffer));
        m_graphDataBuffer.clear();
        m_receivingGraphData = false;
    }
}

void ServiceManager::onConnected()
{
    qDebug() << "Подключен к серверу";

    m_reconnectAttempts = 0;
    if (m_reconnectTimer) {
        m_reconnectTimer->stop();
    }

    emit connected();
}

void ServiceManager::onDisconnected()
{
    qDebug() << "Отключен от сервера";

    if (m_receivingGraphData && !m_graphDataBuffer.isEmpty()) {
        emit functionDataReceived(QString::fromUtf8(m_graphDataBuffer));
        m_graphDataBuffer.clear();
        m_receivingGraphData = false;
    }

    emit disconnected();

    // Start auto-reconnect
    m_reconnectAttempts = 0;
    if (m_reconnectTimer && !m_reconnectTimer->isActive()) {
        m_reconnectTimer->start(RECONNECT_INTERVAL_MS);
    }
}

void ServiceManager::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug() << "Ошибка сокета:" << m_socket->errorString();
    emit error(m_socket->errorString());
}
