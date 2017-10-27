#include "signinform.h"
#include "ui_signinform.h"
#include <QMessageBox>
SignInForm::SignInForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignInForm)
{
    ui->setupUi(this);
}

SignInForm::~SignInForm()
{
    delete ui;
}

void SignInForm::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QMessageBox::information(this,"User Info","U: " + username + "\n" + "P: " + password);
}
