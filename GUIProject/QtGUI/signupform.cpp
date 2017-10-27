#include "signupform.h"
#include "ui_signupform.h"

SignUpForm::SignUpForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignUpForm)
{
    ui->setupUi(this);
}

SignUpForm::~SignUpForm()
{
    delete ui;
}
