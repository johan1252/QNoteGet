#include "viewclasses.h"
#include "ui_viewclasses.h"

ViewClasses::ViewClasses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewClasses)
{
    ui->setupUi(this);
}

ViewClasses::~ViewClasses()
{
    delete ui;
}
