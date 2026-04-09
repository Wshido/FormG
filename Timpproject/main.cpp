#include "maintimp.h"
#include "logintimp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginTimp w;
    w.show();
    return a.exec();
}
