#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinform.h"
#include "signupform.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>

static int currentIndex = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // page1

    /*
    cisc320(":/dummyDirs/ExampleCourses/CISC 320");
    elec370(":/dummyDirs/ExampleCourses/ELEC 370");

    ui->listWidget->addItem(cisc320.dirName());
    ui->listWidget->addItem(elec370.dirName());


    ui->listWidget->addItem("CISC 220");
    ui->listWidget->addItem("CISC 320");
    ui->listWidget->addItem("ELECT 370");

    ui->listWidget_2->addItem("Lectures");
    ui->listWidget_2->addItem("Assignments");

    ui->listWidget_3->addItem("Week 01");
    ui->listWidget_3->addItem("Week 02");
    ui->listWidget_3->addItem("Week 03");
    ui->listWidget_3->addItem("Week 04");
    ui->listWidget_3->addItem("Week 05");
    ui->listWidget_3->addItem("Week 06");
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(YOURCLASSESPAGE); // page1
  }
}

void MainWindow::on_pushButton_doneSubscribe_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(YOURCLASSESPAGE); // Your Classes page
  }
}

void MainWindow::on_pushButton_doneSignUp_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();

    if (ui->lineEdit_password->text() != ui->lineEdit_confirmPassword->text()){
        QMessageBox::critical(this, "Passwords Not Matched",
                     "'Password' and 'Confirm Password' do not match. "
                     "Please ensure the correct password is entered to continue.");
    }

    else if (ui->checkBox_cisc320->isChecked() == false && ui->checkBox_elec371->isChecked() == false
           && ui->checkBox_cisc221->isChecked() == false){
        QMessageBox::critical(this, "Must Select Class",
                      "Please select at least one class to subscribe to.");
    }
    else {

        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Account Details",
                       "Are you sure you would like to proceed with:\nUsername:  " + ui->lineEdit_username->text()
                       + "\nPassword: " + ui->lineEdit_password->text() + "    ...?\nClick 'Yes' to continue.",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            ui->label_myAccountUsername->setText("Hello, " + ui->lineEdit_username->text());
            if(currentIndex < ui->stackedWidget->count())
            {
                ui->stackedWidget->setCurrentIndex(EDITSUBSCRIPTIONSPAGE); // page1
            }
        }
    }


}

void MainWindow::on_pushButton_createAccount_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(SIGNUPPAGE); // Sign Up
  }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{


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


void MainWindow::on_pushButton_editSubs_clicked()
{
    if (currentIndex < ui->stackedWidget->count()){
        ui->stackedWidget->setCurrentIndex(EDITSUBSCRIPTIONSPAGE);
    }
}

void MainWindow::on_pushButton_Back_clicked()
{
    if (currentIndex < ui->stackedWidget->count()){
        ui->stackedWidget->setCurrentIndex(HOMEPAGE);
    }
}
