#include <QApplication>
#include "aboutwindow.h"
#include "emailsender.h"
#include <QDebug>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "=== ЗАПУСК КЛИЕНТА ===";
    qDebug() << "SSL доступен:" << QSslSocket::supportsSsl();

    EmailSender::instance().setSmtpConfig(
        "smtp.gmail.com",
        465,
        "forproject2026FormG@gmail.com",
        "Forproject2026!",
        "forproject2026FormG@gmail.com"
    );

    AboutWindow w;
    w.show();

    return a.exec();
}
