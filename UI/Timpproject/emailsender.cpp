#include "emailsender.h"

EmailSender& EmailSender::instance()
{
    static EmailSender instance;
    return instance;
}

EmailSender::EmailSender(QObject *parent)
    : QObject(parent)
{
}

void EmailSender::saveEmailToFile(const QString& to, const QString& subject, const QString& body)
{
    QFile file("emails_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "\n========================================\n";
        out << "Дата и время: " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") << "\n";
        out << "Кому: " << to << "\n";
        out << "Тема: " << subject << "\n";
        out << "Текст письма:\n" << body << "\n";
        out << "========================================\n";
        file.close();
        qDebug() << "Письмо сохранено в файл emails_log.txt, кому:" << to;
    } else {
        qDebug() << "Не удалось открыть файл для записи письма!";
    }
}

void EmailSender::sendVerificationCode(const QString& to, const QString& code)
{
    QString subject = "Код подтверждения для восстановления пароля";
    QString body = QString("Ваш код подтверждения: %1\n\nЕсли вы не запрашивали восстановление пароля, проигнорируйте это письмо.").arg(code);
    saveEmailToFile(to, subject, body);
}

void EmailSender::sendWelcomeEmail(const QString& to, const QString& username)
{
    QString subject = "Добро пожаловать!";
    QString body = QString("Здравствуйте, %1!\n\nВы успешно зарегистрировались в приложении.\n\nСпасибо, что выбрали нас!").arg(username);
    saveEmailToFile(to, subject, body);
}

void EmailSender::sendPasswordChangedEmail(const QString& to, const QString& username)
{
    QString subject = "Пароль был изменен";
    QString body = QString("Здравствуйте, %1!\n\nВаш пароль был успешно изменен.\n\nЕсли это были не вы, немедленно свяжитесь с поддержкой.").arg(username);
    saveEmailToFile(to, subject, body);
}