#ifndef SIGNINFORM_H
#define SIGNINFORM_H

#include <QMainWindow>

namespace Ui {
class SignInForm;
}

class SignInForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignInForm(QWidget *parent = 0);
    ~SignInForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SignInForm *ui;
};

#endif // SIGNINFORM_H
