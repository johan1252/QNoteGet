#include "addclasses.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    addClasses w;
    w.show();

    return a.exec();
}
