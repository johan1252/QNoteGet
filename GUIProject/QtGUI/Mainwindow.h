#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFileSystemModel>
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <vector>
#include <string>
#include <algorithm>
#include <QGroupBox>

#include "Database/dbDatabase.h"
#include "Backend.h"
#include "User.h"
#include "Course.h"
#include "Credentials.h"
#include "boost/functional/hash.hpp"

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

    void populatePreDefineCourseObjects();
    void populateGlobalUserOnLogin(string username,int pass, string path, int interval);

protected:
    /* override application close */
    void closeEvent(QCloseEvent * event);

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_doneSubscribe_clicked();

    void on_pushButton_doneSignUp_clicked();

    void on_pushButton_createAccount_clicked();

    void on_pushButton_editSubs_clicked();

    void on_pushButton_Back_clicked();

    void on_treeView_courseDirectories_clicked(const QModelIndex &index);

    void on_listView_courseFiles_doubleClicked(const QModelIndex &index);

    void displayApplicableCourseTabs();

    void displayCategoriesForCourse(Course courseObj, int index);

    void repopulateUserSubs();

    void clearCourseTabs();

    void on_saveButton_Cisc320_clicked();

    void on_saveButton_Elec451_clicked();

    void on_saveButton_Cisc124_clicked();

    void on_pushButton_clicked();

    void getCredentials();

    void on_button_getCredentials_clicked();

    void quitApplication();

    void on_actionExit_triggered();

    //Save button on account edit page
    void on_pushButton_saveAccount_clicked();

private:
    Ui::MainWindow *ui;

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;

    QFileSystemModel * dirModel;
    QFileSystemModel * fileModel;
    vector<Course> preDefinedCourses;
    User currentUserG;
    vector<bool> courseEditsMade; //for use with editSubscriptions button
    vector<Course*> * beforeSubs = nullptr;

    void setupDirectoryExplorer();
    void createTaskBarIcon();
    bool validateUser(string username, string password); //unhash and check PW
    int hashPassword(string password);
    bool createUser(string username, int password,string path, int interval, vector<Course> userCourses);
    Course createCourse(string courseName, string rootUrl, vector<CourseCategory> categorie);
    vector<Course> createUserCourseObjects();
    //void courseCategorySaveButtonClicked(int courseTabId);
    void courseCategorySaveButtonClicked(int courseTabId);
    vector<CourseCategory> editSubscription(vector<Course *> userCourses, int UserCourseIndex, QString thisCourse, QList<QGroupBox*> categories);
    void compareEditedSubscriptions(const int courseID, vector<CourseCategory> beforeSubs, vector<CourseCategory> afterSubs);

};
