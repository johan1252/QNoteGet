#include "buildapath.h"
#include "ui_buildapath.h"

BuildAPath::BuildAPath(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuildAPath)
{
    ui->setupUi(this);
}

BuildAPath::~BuildAPath()
{
    delete ui;
}
