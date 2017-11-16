#include "Mainwindow.h"
#include "Database/dbDatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show(); //show window

    //Somehow when the application closes make sure we add the following line.
    // database::dbEndDatabaseConnection();
    runDatabase();
    return a.exec();
}
