#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinform.h"
#include "signupform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    SignInForm *w = new SignInForm(this);
    w->show(); //show window
}

void MainWindow::on_pushButton_2_clicked()
{
    SignUpForm *w = new SignUpForm(this);
    w->show(); //show window
}
