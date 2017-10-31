#ifndef ADDCLASSES_H
#define ADDCLASSES_H

#include <QMainWindow>

namespace Ui {
class addClasses;
}

class addClasses : public QMainWindow
{
    Q_OBJECT

public:
    explicit addClasses(QWidget *parent = 0);
    ~addClasses();

private:
    Ui::addClasses *ui;
};

#endif // ADDCLASSES_H
