#include "Credentials.h"
#include "ui_Credentials.h"

Credentials::Credentials(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credentials)
{
    ui->setupUi(this);
}

Credentials::~Credentials()
{
    delete ui;
}

string Credentials::getUsername(){
    return ui->loginLineEdit_credentials->text().toStdString();;
}

string Credentials::getPassword(){
    return ui->passwordLineEdit_passwordCredentials->text().toStdString();
}

void Credentials::on_validateCredentials_button_clicked()
{
    if((ui->loginLineEdit_credentials->text().isEmpty()) ||(ui->passwordLineEdit_passwordCredentials->text().isEmpty())) {
        QMessageBox::critical(this, "Empty Fields",
                      "Please enter a username and password.");
    } else {
        close();
    }
}
