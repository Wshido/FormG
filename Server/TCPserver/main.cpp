#include <QCoreApplication>
#include "tcpserver.h"
#include <QDebug>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "=== ЗАПУСК TCP СЕРВЕРА ===";
    qDebug() << "SSL доступен:" << QSslSocket::supportsSsl();
    qDebug() << "Версия SSL:" << QSslSocket::sslLibraryBuildVersionString();

    TCPServer server;

    server.setSmtpConfig(
        "smtp.gmail.com",
        465,
        "forproject2026formg@gmail.com",
        "vukjgfzhnrxyujwv",
        "forproject2026formg@gmail.com"
    );

    if (server.start(11999)) {
        qDebug() << "Сервер запущен на порту 11999";
    } else {
        qCritical() << "Не удалось запустить сервер";
        return 1;
    }

    return a.exec();
}
