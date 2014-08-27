#include "senddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SendDialog d;
    if (d.isStarted())
        d.show();

    return a.exec();
}
