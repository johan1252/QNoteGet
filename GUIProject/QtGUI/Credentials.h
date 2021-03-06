#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>

using namespace std;

namespace Ui {
class Credentials;
}

class Credentials : public QDialog
{
    Q_OBJECT

public:
    explicit Credentials(QWidget *parent = 0);
    ~Credentials();
    void validateCredentials(string url);
    string getUsername();
    string getPassword();

private slots:
    void on_validateCredentials_button_clicked();

private:
    Ui::Credentials *ui;
    string username;
    string password;
};

#endif // CREDENTIALS_H
