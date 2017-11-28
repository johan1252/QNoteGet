#include "Mainwindow.h"
#include "Database/dbDatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // w.setStyleSheet("QMainWindow {background-color:rgb(114,159,207);}");
    w.show(); //show window

    //Create global pre-defined course objects from database
    w.populatePreDefineCourseObjects();

    //Somehow when the application closes make sure we add the following line.
    // database::dbEndDatabaseConnection();
    dbRunDatabase();
    a.exec();

    return 0;
}
