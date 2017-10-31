#include "addclasses.h"
#include "ui_addclasses.h"

addClasses::addClasses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addClasses)
{
    ui->setupUi(this);
}

addClasses::~addClasses()
{
    delete ui;
}
