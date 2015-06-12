#include "baldawindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaldaWindow w;
    w.show();

    return a.exec();
}
