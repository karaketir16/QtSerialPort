#include "logtest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logTest w;
    w.show();

    return a.exec();
}
