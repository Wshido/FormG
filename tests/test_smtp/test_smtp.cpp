#include <QCoreApplication>
#include <QSslSocket>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <cctype>

static QFile logFile;

static void log(const QString &msg) {
    qDebug().noquote() << msg;
    QTextStream ts(&logFile);
    ts << msg << "\n";
    ts.flush();
}

static QByteArray b64(const QString &s) { return s.toUtf8().toBase64(); }

static bool readResponse(QSslSocket &sock, int expected) {
    QByteArray buf;
    while (true) {
        if (!sock.waitForReadyRead(15000)) {
            log("[ERR] Timeout");
            return false;
        }
        buf += sock.readAll();
        for (const QByteArray &ln : buf.split('\n')) {
            QByteArray t = ln.trimmed();
            if (t.length() >= 4 && std::isdigit((unsigned char)t[0]) &&
                std::isdigit((unsigned char)t[1]) &&
                std::isdigit((unsigned char)t[2]) && t[3] == ' ') {
                log("<<" + t);
                if (expected != -1 && t.left(3).toInt() != expected) {
                    log("[ERR] Expected " + QByteArray::number(expected) + " got " + t.left(3));
                    return false;
                }
                return true;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    logFile.setFileName("smtp_log.txt");
    logFile.open(QIODevice::WriteOnly | QIODevice::Text);

    log("=== SMTP TEST ===");
    log("SSL supported: " + QString(QSslSocket::supportsSsl() ? "YES" : "NO"));
    log("SSL build: " + QSslSocket::sslLibraryBuildVersionString());
    log("SSL runtime: " + QSslSocket::sslLibraryVersionString());

    if (!QSslSocket::supportsSsl()) {
        log("[FATAL] OpenSSL NOT available!");
        logFile.close();
        return 1;
    }

    QString host = "smtp.gmail.com";
    quint16 port = 465;
    QString user = "forproject2026formg@gmail.com";
    QString pass = "vukjgfzhnrxyujwv";
    QString from = "forproject2026formg@gmail.com";
    QString to = "rfox2410@gmail.com";

    log("\n--- Connecting to " + host + ":" + QString::number(port) + " ---");
    QSslSocket sock;
    sock.connectToHostEncrypted(host, port);
    if (!sock.waitForEncrypted(20000)) {
        log("[FATAL] SSL failed: " + sock.errorString());
        logFile.close();
        return 1;
    }
    log("[OK] SSL connected");
    if (!readResponse(sock, 220)) { logFile.close(); return 1; }

    log("\n--- EHLO ---");
    sock.write("EHLO localhost\r\n");
    if (!readResponse(sock, 250)) { logFile.close(); return 1; }

    log("\n--- AUTH LOGIN ---");
    sock.write("AUTH LOGIN\r\n");
    if (!readResponse(sock, 334)) { logFile.close(); return 1; }

    log("Username: " + user);
    sock.write(b64(user) + "\r\n");
    if (!readResponse(sock, 334)) { logFile.close(); return 1; }

    log("Password: [hidden]");
    sock.write(b64(pass) + "\r\n");
    if (!readResponse(sock, 235)) {
        log("[FATAL] AUTH FAILED!");
        logFile.close();
        return 1;
    }
    log("[OK] Authenticated!");

    log("\n--- MAIL FROM ---");
    sock.write("MAIL FROM:<" + from.toUtf8() + ">\r\n");
    if (!readResponse(sock, 250)) { logFile.close(); return 1; }

    log("--- RCPT TO ---");
    sock.write("RCPT TO:<" + to.toUtf8() + ">\r\n");
    if (!readResponse(sock, 250)) { logFile.close(); return 1; }

    log("--- DATA ---");
    sock.write("DATA\r\n");
    if (!readResponse(sock, 354)) { logFile.close(); return 1; }

    QByteArray msg;
    msg += "From: =?UTF-8?B?" + b64("Server") + "?= <" + from.toUtf8() + ">\r\n";
    msg += "To: " + to.toUtf8() + "\r\n";
    msg += "Subject: =?UTF-8?B?" + b64("Test email") + "?=\r\n";
    msg += "MIME-Version: 1.0\r\n";
    msg += "Content-Type: text/plain; charset=UTF-8\r\n";
    msg += "Content-Transfer-Encoding: base64\r\n";
    msg += "\r\n";
    msg += b64("Test email from server.\nIf you see this - SMTP works!") + "\r\n";
    msg += ".\r\n";

    sock.write(msg);
    if (!readResponse(sock, 250)) { logFile.close(); return 1; }

    log("\n--- QUIT ---");
    sock.write("QUIT\r\n");
    readResponse(sock, 221);

    sock.disconnectFromHost();
    log("\n=== SUCCESS: EMAIL SENT ===");
    logFile.close();
    return 0;
}
