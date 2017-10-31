#ifndef BUILDAPATH_H
#define BUILDAPATH_H

#include <QMainWindow>

namespace Ui {
class BuildAPath;
}

class BuildAPath : public QMainWindow
{
    Q_OBJECT

public:
    explicit BuildAPath(QWidget *parent = 0);
    ~BuildAPath();

private:
    Ui::BuildAPath *ui;
};

#endif // BUILDAPATH_H
