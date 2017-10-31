#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinform.h"
#include "signupform.h"
#include <QDir>
#include <QDebug>

static int currentIndex = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // page1
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //this->hide();
    //SignInForm *w = new SignInForm(this);
   // w->show(); //show window
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(3); // page1
  }
}

void MainWindow::on_pushButton_2_clicked()
{
   // this->hide();
    //SignUpForm *w = new SignUpForm(this);
    //w->show(); //show window
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(3); // page1
  }
}

void MainWindow::on_pushButton_4_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(2); // page1
  }
}

void MainWindow::on_pushButton_3_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(1); // page1
  }
}

void MainWindow::on_pushButton_4_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(2); // page1
  }
}

void MainWindow::on_pushButton_3_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(1); // page1
  }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

    //This doesnt work when "baseFilePath" not hard-coded to the particular machine
    // but old code still included to give idea of what old implementation looked like

   /*
    qDebug() << item->text();
    ui->listWidget_2->clear();


    QString thisFolder = baseFilePath + "/" + item->text();
    QDir dir2(thisFolder);

    foreach (QFileInfo var, dir2.entryInfoList()) {
        ui->listWidget_2->addItem(var.baseName());
    }

    */
}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    /*
    ui->listWidget_3->clear();

    QString parentDir = ui->listWidget->currentItem()->text();
    qDebug() << parentDir;
    QString thisFolder = baseFilePath + "/" + parentDir + "/" + item->text();
    qDebug() << thisFolder;
    QDir dir3(thisFolder);

    foreach (QFileInfo var, dir3.entryInfoList()) {
        ui->listWidget_3->addItem(var.baseName());
    }
    */
}

