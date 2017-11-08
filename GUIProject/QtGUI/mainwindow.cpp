#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinform.h"
#include "signupform.h"
#include "database.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>


static int currentIndex = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(HOMEPAGE);

    setupDirectoryExplorer();

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
      ui->stackedWidget->setCurrentIndex(YOURCLASSESPAGE);
  }
}

void MainWindow::on_pushButton_doneSubscribe_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(YOURCLASSESPAGE);
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

            //TODO: fill in real values for path, updateInterval. And don't make direct database call.
            //Just proof of concept.
            std::size_t str_password_hash = std::hash<std::string>{}(ui->lineEdit_password->text().toStdString());

            database::dbCreateUserRow(ui->lineEdit_username->text().toStdString(), str_password_hash , "Blah path", 2021);

            if(currentIndex < ui->stackedWidget->count())
            {
                ui->stackedWidget->setCurrentIndex(EDITSUBSCRIPTIONSPAGE);
            }
        }
    }


}

void MainWindow::on_pushButton_createAccount_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(SIGNUPPAGE);
  }
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

void MainWindow::on_treeView_courseDirectories_clicked(const QModelIndex &index)
{
    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView_courseFiles->setRootIndex(fileModel->setRootPath(path));
}

void MainWindow::on_listView_courseFiles_doubleClicked(const QModelIndex &index)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileModel->fileInfo(index).absoluteFilePath()));
}

void MainWindow::setupDirectoryExplorer(){

    //Due to an apparent bug in Qt 4.7.2, the version I'm using, the QFileSystemModel
    //doesn't work with resource files. I'm not sure if its fixed in version 5.
    //So resourcePath is the path to use if resources work, otherwise, make a path to
    //your desktop. This isn't expected to be a problem with the final version of QNoteGet
    //as the directories won't be Qt resources
    // see here : https://bugreports.qt.io/browse/QTBUG-25007
    //          : https://bugreports.qt.io/browse/QTBUG-7010

    //TO USE DIRECTORY EXPLORER:
    // Either: replace all uses of desktopPath with resourcePath
    //      or
    //          If resource path still not working, edit desktopPath to your desktop,
    //          place resource file in appropriately named folder on desktop (or wherever you'd like I guess)

    QString resourcePath = ":/dummyDirs/ExampleCourses";
    QString desktopPath = "/Users/Marshall/Desktop/ExampleCourses";

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); //hide "." and ".." folders, only display directories
    /*
     * QFileSystemModel will not fetch any files or directories until
     *  setRootPath() is called. This will prevent any unnecessary querying
     * on the file system until that point such as listing the drives on Windows.
     */
    dirModel->setReadOnly(true);
    ui->treeView_courseDirectories->setModel(dirModel);
    ui->treeView_courseDirectories->setRootIndex(dirModel->setRootPath(desktopPath));

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files); //only show files
    fileModel->setRootPath(dirModel->rootPath());
    ui->listView_courseFiles->setModel(fileModel);

    QModelIndex coursesIndex = ui->treeView_courseDirectories->rootIndex();
    ui->treeView_courseDirectories->expand(coursesIndex);
    ui->treeView_courseDirectories->setCurrentIndex(coursesIndex);
    ui->treeView_courseDirectories->resizeColumnToContents(0);
}
