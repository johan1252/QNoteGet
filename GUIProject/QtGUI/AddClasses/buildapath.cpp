#include "buildapath.h"
#include "ui_buildapath.h"
#include <QPixmap>
#include "addclasses.h"

BuildAPath::BuildAPath(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuildAPath)
{
    ui->setupUi(this);
    QPixmap addIcon(":/icons/icons/Button-Add.png");
    int w = ui->label_addClasses->width();
    int h = ui->label_addClasses->height();
    ui->label_addClasses->setPixmap(addIcon.scaled(w, h, Qt::KeepAspectRatio));

}

BuildAPath::~BuildAPath()
{
    delete ui;
}

void BuildAPath::on_group_addClasses_clicked()
{
    hide();
    addClasses * page = new addClasses(this);
    page->show();
}
