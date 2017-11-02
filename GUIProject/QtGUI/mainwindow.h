#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum pages {
        HOMEPAGE = 0,
        SIGNUPPAGE = 1,
        EDITSUBSCRIPTIONSPAGE = 2,
        YOURCLASSESPAGE = 3
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_doneSubscribe_clicked();

    void on_pushButton_doneSignUp_clicked();

    void on_pushButton_createAccount_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_pushButton_editSubs_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::MainWindow *ui;
    QDir cisc320;
    QDir elec370;

};

#endif // MAINWINDOW_H
