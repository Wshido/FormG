#include <QApplication>
#include "aboutwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AboutWindow w;
    w.show();

    return a.exec();
}