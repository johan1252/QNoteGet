#ifndef ADDCLASSES_H
#define ADDCLASSES_H

#include <QMainWindow>
#include "buildapath.h"
#include "viewclasses.h"

namespace Ui {
class addClasses;
}

class addClasses : public QMainWindow
{
    Q_OBJECT

public:
    explicit addClasses(QWidget *parent = 0);
    ~addClasses();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_done_clicked();

    void on_pushButton_viewClasses_clicked();

private:
    Ui::addClasses *ui;
    BuildAPath *page;
    ViewClasses * classesPage;
};

#endif // ADDCLASSES_H
