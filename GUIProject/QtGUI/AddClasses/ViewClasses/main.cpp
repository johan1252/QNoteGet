#include "viewclasses.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewClasses w;
    w.show();

    return a.exec();
}
