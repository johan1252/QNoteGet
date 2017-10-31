#include "addclasses.h"
#include "ui_addclasses.h"
#include "buildapath.h"

addClasses::addClasses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addClasses)
{
    ui->setupUi(this);
    ui->comboBox_classes->addItem("CISC");
    ui->comboBox_classes->addItem("ELEC");

    ui->comboBox_classNum->addItem("320");
    ui->comboBox_classNum->addItem("270");


}

addClasses::~addClasses()
{
    delete ui;
}

void addClasses::on_pushButton_add_clicked()
{
    QString course = ui->comboBox_classes->currentText() + " " + ui->comboBox_classNum->currentText();
    QListWidgetItem * item = new QListWidgetItem(course);

    ui->listOfClasses->addItem(item);

}

void addClasses::on_pushButton_done_clicked()
{
    hide();
    page = new BuildAPath(this);
    page->show();
}

void addClasses::on_pushButton_viewClasses_clicked()
{
    hide();
    classesPage = new ViewClasses(this);
    classesPage->show();
}
