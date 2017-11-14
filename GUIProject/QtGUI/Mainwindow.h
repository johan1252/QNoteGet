#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>

#include "Database.h"
#include "User.h"
#include "Course.h"

using namespace std;
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

    void on_pushButton_editSubs_clicked();

    void on_pushButton_Back_clicked();

    void on_treeView_courseDirectories_clicked(const QModelIndex &index);

    void on_listView_courseFiles_doubleClicked(const QModelIndex &index);

    void displayApplicableCourseTabs(User userObj);

    void on_saveButton_Cisc320_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel * dirModel;
    QFileSystemModel * fileModel;

    void setupDirectoryExplorer();
    bool validateUser(string username, string password); //unhash and check PW
    int hashPassword(string password);
    bool createUser(string username, int password,string path, int interval, vector<Course> userCourses);
    Course createCourse(string courseName, string rootUrl, vector<CourseCategory> categorie);
    vector<Course> createUserCourseObjects();
    void courseCategorySaveButtonClicked(int courseTabId);
};



