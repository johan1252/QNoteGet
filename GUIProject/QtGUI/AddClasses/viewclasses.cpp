#include "viewclasses.h"
#include "ui_viewclasses.h"
#include <QDir>
#include <QDebug>
#include "addclasses.h"

QString baseFilePath = "/Users/Marshall/Downloads/3rd 1st Sem";

ViewClasses::ViewClasses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewClasses)
{
    ui->setupUi(this);

    QDir dir(baseFilePath);
    foreach (QFileInfo var, dir.entryInfoList()) {
        ui->listWidget->addItem(var.baseName());
    }

}

ViewClasses::~ViewClasses()
{
    delete ui;
}

void ViewClasses::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
    ui->listWidget_2->clear();

    QString thisFolder = baseFilePath + "/" + item->text();
    QDir dir2(thisFolder);

    foreach (QFileInfo var, dir2.entryInfoList()) {
        ui->listWidget_2->addItem(var.baseName());
    }

}

void ViewClasses::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_3->clear();

    QString parentDir = ui->listWidget->currentItem()->text();
    qDebug() << parentDir;
    QString thisFolder = baseFilePath + "/" + parentDir + "/" + item->text();
    qDebug() << thisFolder;
    QDir dir3(thisFolder);

    foreach (QFileInfo var, dir3.entryInfoList()) {
        ui->listWidget_3->addItem(var.baseName());
    }
}

void ViewClasses::on_pushButton_addClasses_clicked()
{
    hide();
    addClasses * page = new addClasses(this);
    page->show();
}
