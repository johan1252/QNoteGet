#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinform.h"
#include "signupform.h"
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
