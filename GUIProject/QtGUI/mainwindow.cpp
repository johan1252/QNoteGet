#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    static bool clicked = false;
    if(!clicked){
     ui->label->setText("I've been clicked!");
     clicked = true;
    }
    else{
     ui->label->setText("Click the button!");
     clicked = false;
    }
}
