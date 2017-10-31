#ifndef VIEWCLASSES_H
#define VIEWCLASSES_H

#include <QMainWindow>

namespace Ui {
class ViewClasses;
}

class ViewClasses : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewClasses(QWidget *parent = 0);
    ~ViewClasses();

private:
    Ui::ViewClasses *ui;
};

#endif // VIEWCLASSES_H
