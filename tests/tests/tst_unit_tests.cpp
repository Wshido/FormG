#include <QtTest>
#include <QString>
#include <QRegularExpression>
#include <cmath>

class TimpUnitTests : public QObject
{
    Q_OBJECT

private:
    double calculateFunction(double a, double b, double c, double x)
    {
        if (x < 0) {
            return sin(a * x);
        } else if (x < 1) {
            if (b * x < 0) return 0;
            return sqrt(b * x);
        } else {
            if (fabs(c * x - 1.0) < 0.0001) return 0;
            return 1.0 / (c * x - 1.0);
        }
    }

    bool validateLogin(const QString &login)
    {
        return !login.isEmpty() && login.length() >= 3 && login.length() <= 16;
    }

    bool validateEmail(const QString &email)
    {
        return !email.isEmpty() && email.length() <= 100
               && email.contains('@') && email.contains('.');
    }

    bool validatePassword(const QString &password)
    {
        if (password.isEmpty() || password.length() < 8 || password.length() > 64)
            return false;
        QRegularExpression re("^[A-Za-z0-9]+$");
        return re.match(password).hasMatch();
    }

    QString hashPassword(const QString &password, const QString &salt)
    {
        QByteArray data = (password + salt).toUtf8();
        QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
        return salt + ":" + hash.toHex();
    }

    struct SessionData {
        QString token;
        qint64 lastActivity;
    };

    struct BruteForceData {
        int failedAttempts;
        qint64 lockoutUntil;
    };

private slots:
    // ========== calculateFunction ==========
    void testCalcSin()
    {
        QVERIFY(qAbs(calculateFunction(1, 1, 1, -1) - sin(-1.0)) < 0.0001);
        QVERIFY(qAbs(calculateFunction(2, 1, 1, -1) - sin(-2.0)) < 0.0001);
        QVERIFY(qAbs(calculateFunction(1, 1, 1, -0.5) - sin(-0.5)) < 0.0001);
    }

    void testCalcSqrt()
    {
        QVERIFY(qAbs(calculateFunction(1, 4, 1, 0.25) - 1.0) < 0.0001);
        QVERIFY(qAbs(calculateFunction(1, 1, 1, 0.5) - sqrt(0.5)) < 0.0001);
        QVERIFY(qAbs(calculateFunction(1, 1, 1, 0.9) - sqrt(0.9)) < 0.0001);
    }

    void testCalcSqrtNegative()
    {
        QCOMPARE(calculateFunction(1, -1, 1, 0.5), 0.0);
        QCOMPARE(calculateFunction(1, 0, 1, 0.5), 0.0);
    }

    void testCalcFraction()
    {
        QVERIFY(qAbs(calculateFunction(1, 1, 1, 2.0) - 1.0) < 0.0001);
        QVERIFY(qAbs(calculateFunction(1, 1, 1, 1.5) - 2.0) < 0.0001);
        QVERIFY(qAbs(calculateFunction(1, 1, 1, 3.0) - 0.5) < 0.0001);
    }

    void testCalcFractionDivByZero()
    {
        QCOMPARE(calculateFunction(1, 1, 1, 1.0), 0.0);
        QCOMPARE(calculateFunction(1, 1, 1, 1.0 / 1.0 + 0.00001), 0.0);
    }

    void testCalcFractionCustomC()
    {
        QVERIFY(qAbs(calculateFunction(1, 1, 2, 2.0) - 1.0 / 3.0) < 0.0001);
        QVERIFY(qAbs(calculateFunction(1, 1, 0.5, 4.0) - 1.0) < 0.0001);
    }

    void testCalcBoundaryX0()
    {
        QCOMPARE(calculateFunction(1, 1, 1, 0.0), 0.0);
    }

    void testCalcBoundaryX1()
    {
        QCOMPARE(calculateFunction(1, 1, 1, 1.0), 0.0);
    }

    void testCalcAllZeros()
    {
        QCOMPARE(calculateFunction(0, 0, 0, -1), 0.0);
        QCOMPARE(calculateFunction(0, 0, 0, 0.5), 0.0);
        QCOMPARE(calculateFunction(0, 0, 0, 2.0), 0.0);
    }

    // ========== validateLogin ==========
    void testLoginValid()
    {
        QVERIFY(validateLogin("abc"));
        QVERIFY(validateLogin("test123"));
        QVERIFY(validateLogin("a"));
        QVERIFY(validateLogin("a"));
        QVERIFY(validateLogin("a"));
        QVERIFY(validateLogin("a"));
    }

    void testLoginTooShort()
    {
        QVERIFY(!validateLogin(""));
        QVERIFY(!validateLogin("a"));
        QVERIFY(!validateLogin("ab"));
    }

    void testLoginTooLong()
    {
        QVERIFY(!validateLogin(QString(17, 'a')));
    }

    void testLoginMaxLength()
    {
        QVERIFY(validateLogin(QString(16, 'a')));
    }

    // ========== validateEmail ==========
    void testEmailValid()
    {
        QVERIFY(validateEmail("test@mail.com"));
        QVERIFY(validateEmail("a@b.c"));
        QVERIFY(validateEmail("user@domain.org"));
    }

    void testEmailNoAt()
    {
        QVERIFY(!validateEmail("no-at.com"));
    }

    void testEmailNoDot()
    {
        QVERIFY(!validateEmail("no@dotcom"));
    }

    void testEmailEmpty()
    {
        QVERIFY(!validateEmail(""));
    }

    void testEmailTooLong()
    {
        QVERIFY(!validateEmail(QString(91, 'a') + "@test.com"));
    }

    void testEmailMaxLength()
    {
        QVERIFY(validateEmail(QString(90, 'a') + "@test.com"));
    }

    // ========== validatePassword ==========
    void testPasswordValid()
    {
        QVERIFY(validatePassword("Pass1234"));
        QVERIFY(validatePassword("aA1bB2cC"));
        QVERIFY(validatePassword("12345678"));
    }

    void testPasswordTooShort()
    {
        QVERIFY(!validatePassword(""));
        QVERIFY(!validatePassword("short1"));
        QVERIFY(!validatePassword("1234567"));
    }

    void testPasswordTooLong()
    {
        QVERIFY(!validatePassword(QString(65, 'a')));
    }

    void testPasswordMaxLength()
    {
        QVERIFY(validatePassword(QString(64, 'a')));
    }

    void testPasswordNoSpecialChars()
    {
        QVERIFY(!validatePassword("Pass@1234"));
        QVERIFY(!validatePassword("Pass word1"));
        QVERIFY(!validatePassword("Pass1234!"));
    }

    void testPasswordOnlyDigits()
    {
        QVERIFY(validatePassword("12345678"));
    }

    void testPasswordOnlyLetters()
    {
        QVERIFY(validatePassword("abcdefgh"));
        QVERIFY(validatePassword("ABCDEFGH"));
    }

    // ========== Password Hashing ==========
    void testHashConsistent()
    {
        QString h1 = hashPassword("test1234", "mysalt");
        QString h2 = hashPassword("test1234", "mysalt");
        QCOMPARE(h1, h2);
    }

    void testHashDifferentSalt()
    {
        QString h1 = hashPassword("test1234", "salt1");
        QString h2 = hashPassword("test1234", "salt2");
        QVERIFY(h1 != h2);
    }

    void testHashDifferentPassword()
    {
        QString h1 = hashPassword("password1", "salt");
        QString h2 = hashPassword("password2", "salt");
        QVERIFY(h1 != h2);
    }

    void testHashFormat()
    {
        QString h = hashPassword("test1234", "mysalt");
        QVERIFY(h.startsWith("mysalt:"));
        QStringList parts = h.split(":");
        QCOMPARE(parts.size(), 2);
        QCOMPARE(parts[1].length(), 64);
    }

    void testHashSha256()
    {
        QString h = hashPassword("test", "salt");
        QString hex = h.split(":")[1];
        QRegularExpression hexRe("^[0-9a-f]{64}$");
        QVERIFY(hexRe.match(hex).hasMatch());
    }
};

QTEST_MAIN(TimpUnitTests)
#include "tst_unit_tests.moc"
