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

void Credentials::validateCredentials(string url) {
    QString qstr = QString::fromStdString(url);
    //TODO:: get course url showing on the label
    Credentials creddialog;
    creddialog.setModal(true);
    creddialog.exec();
}



void Credentials::on_validateCredentials_button_clicked()
{
    bool valid = false;
    if((ui->loginLineEdit_credentials->text().isEmpty()) ||(ui->passwordLineEdit_passwordCredentials->text().isEmpty())) {
        QMessageBox::critical(this, "Empty Fields",
                      "Please enter a username and password.");
    } else {

        //TODO::call backend function which will validate the username password for the url, the return
        // of the function should be a boolen put in valid
        if(valid) {
            //close the window
            close();
        } else {
            QMessageBox::critical(this, "Incorrect",
                          "Please enter a valid username and password.");
        }
    }
}
