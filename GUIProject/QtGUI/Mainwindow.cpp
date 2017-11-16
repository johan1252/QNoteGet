#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "Credentials.h"

static int currentIndex = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(HOMEPAGE);

    setupDirectoryExplorer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    bool valid = false;
    currentIndex = ui->stackedWidget->currentIndex();
    if((ui->lineEdit_loginUsername->text().isEmpty()) ||(ui->lineEdit_loginPassword->text().isEmpty()))
    {
        QMessageBox::critical(this, "Empty Fields",
                      "Please enter your username and password.");
    } else {
        valid = validateUser(ui->lineEdit_loginUsername->text().toStdString(),ui->lineEdit_loginPassword->text().toStdString());
        if (valid){
            if( currentIndex < ui->stackedWidget->count())
            {
                ui->stackedWidget->setCurrentIndex(YOURCLASSESPAGE);
            }
        } else {
            QMessageBox::critical(this, "Incorrect Login",
                          "No account was found with these credentials. Try Again.");
        }
    }


}

void MainWindow::on_pushButton_doneSubscribe_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(YOURCLASSESPAGE);
  }
}

void MainWindow::on_pushButton_doneSignUp_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
    if (ui->lineEdit_password->text().isEmpty() || ui->lineEdit_fileDirectory->text().isEmpty() ||
                   ui->lineEdit_confirmPassword->text().isEmpty() || ui->lineEdit_username->text().isEmpty()) {
            QMessageBox::critical(this, "Empty Fields",
                          "Please ensure all fields are filled in.");
    }
    else if (ui->lineEdit_password->text() != ui->lineEdit_confirmPassword->text()){
        QMessageBox::critical(this, "Passwords Not Matched",
                     "'Password' and 'Confirm Password' do not match. "
                     "Please ensure the correct password is entered to continue.");
    }

    else if (ui->checkBox_cisc320->isChecked() == false && ui->checkBox_elec451->isChecked() == false
           && ui->checkBox_cisc124->isChecked() == false){
        QMessageBox::critical(this, "Must Select Class",
                      "Please select at least one class to subscribe to.");
    }
    else {

        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Account Details",
                       "Are you sure you would like to proceed with:\nUsername: " + ui->lineEdit_username->text()
                      ,QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes){
            ui->label_myAccountUsername->setText("Hello, " + ui->lineEdit_username->text());

            /*
             * Hash password, get file path from GUI, and convert GUI update interval to number of hours.
             */
            int passwordHashed = hashPassword(ui->lineEdit_password->text().toStdString());
            string filepath = ui->lineEdit_fileDirectory->text().toStdString();

            int scaledInterval = 0;
            int interval = ui->updateIntervalComboBox->currentIndex();
            if (interval == 0)
                scaledInterval = 24;
            else if (interval == 1)
                scaledInterval = 24*7;
            else if (interval == 2)
                scaledInterval = 24*7*2;

            /* Course Object Creation specific for user selection.
             * This is then used in createUser() method to link courses to user object.
             */
            // TODO: This call may need to be moved once categoryPreferences is involved
            vector<Course> userCourses = createUserCourseObjects();

            // make user object function which checks if the username is unique or not
            // if unique, create user object, if not unique, tell user that already exists
            if(!(createUser(ui->lineEdit_username->text().toStdString(), passwordHashed,filepath,scaledInterval,userCourses))){
                QMessageBox::critical(this, "Exists",
                              "An account with this username already exists.");
            } else {
                if(currentIndex < ui->stackedWidget->count())
                {
                    ui->stackedWidget->setCurrentIndex(EDITSUBSCRIPTIONSPAGE);
                }
            }
        }
    }
}

/*
 * Function to hash a user's password before being passed to User object.
 */
int MainWindow::hashPassword(string password) {
    std::size_t str_password_hash = std::hash<std::string>{}(password);
    return str_password_hash;
}

/*
 * Function to create the User object and any associated DB calls. (including adding which courses the user is subscribed to)
 */
bool MainWindow::createUser(string username, int password, string path, int interval, vector<Course> userCourses){
    int result = Database::dbGetPasswordForUsername(username);
    if(result == -1){
        User userAccount = User(username,password,path,interval,userCourses);
        displayApplicableCourseTabs(userAccount);
        Database::dbCreateUserRow(userAccount.getUsername(),userAccount.getPassword(),userAccount.getFileDirectory(),userAccount.getUpdateInterval());

        // Create entry in usercourses DB table for each course the user has subscribed to.
        for(auto userCourse: userCourses) {
            Database::dbCreateUserCoursesRow(username, userCourse);
        }

        return true;
    }
    else {
        return false;
    }
}

/*
 * Function validates a user's login information to see if they have an account in the dB
 * Returns a boolean based on validation.
 */

bool MainWindow::validateUser(string username, string password){
    int passwordHashed = hashPassword(password);
    int result = Database::dbGetPasswordForUsername(username);
    return(passwordHashed == result);
}

/*
 * Function to create user specific Course object.
 * Returns the course object.
 */
Course MainWindow::createCourse(string courseName, string rootUrl, vector<CourseCategory> categories){
    Course userCourse = Course(courseName,rootUrl,categories);
    return userCourse;
}

/*
 * Function to create user specific Course objects depending on which courses they chose in the GUI.
 * Returns vector of course objects.
 */
vector<Course> MainWindow::createUserCourseObjects(){
    vector<Course> courseVector;
    string coursePath;

    // Since the course categories subscription phase is later on in the GUI, for now set as an empty categories vector.
    vector<CourseCategory> emptyCategoriesVector;

    // Note, The GUI ensures atleast one of these items is checked.
    if (ui->checkBox_cisc320->isChecked()) {
        coursePath = Database::dbGetCoursePath("CISC320");
        if (coursePath != "") {
            courseVector.push_back(createCourse("CISC320", coursePath, emptyCategoriesVector));
        } else {
           cout << "ERROR occured, course path could not be found for CISC320" << endl;
        }
    }
    if (ui->checkBox_cisc124->isChecked()) {
        coursePath = Database::dbGetCoursePath("CISC124");
        if (coursePath != "") {
            courseVector.push_back(createCourse("CISC124", coursePath, emptyCategoriesVector));
        } else {
           cout << "ERROR occured, course path could not be found for CISC124" << endl;
        }
    }
    if (ui->checkBox_elec451->isChecked()) {
        coursePath = Database::dbGetCoursePath("ELEC451");
        if (coursePath != "") {
            courseVector.push_back(createCourse("ELEC451", coursePath, emptyCategoriesVector));
        } else {
           cout << "ERROR occured, course path could not be found for ELEC451" << endl;
        }
    }
    return courseVector;
}

void MainWindow::on_pushButton_createAccount_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      ui->stackedWidget->setCurrentIndex(SIGNUPPAGE);
  }
}
//TODO:: When user goes back, displayApplicableCourseTabs should be called. But it requires User object.
// May need to change this.
void MainWindow::on_pushButton_editSubs_clicked()
{
    if (currentIndex < ui->stackedWidget->count()){
        ui->stackedWidget->setCurrentIndex(EDITSUBSCRIPTIONSPAGE);
    }
}

void MainWindow::on_pushButton_Back_clicked()
{
    if (currentIndex < ui->stackedWidget->count()){
        ui->stackedWidget->setCurrentIndex(HOMEPAGE);
    }
}

void MainWindow::on_treeView_courseDirectories_clicked(const QModelIndex &index)
{
    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView_courseFiles->setRootIndex(fileModel->setRootPath(path));
}

void MainWindow::on_listView_courseFiles_doubleClicked(const QModelIndex &index)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileModel->fileInfo(index).absoluteFilePath()));
}

void MainWindow::displayApplicableCourseTabs(User userObj){
    vector<Course> subscription = userObj.getSubscribedCourses();
    // all disabled by default
    ui->tabWidget->setTabEnabled(1,true); //cisc320
    ui->tabWidget->setTabEnabled(2,true); //elec451
    ui->tabWidget->setTabEnabled(3, true); //cisc124

    for (unsigned long i = 0; i < subscription.size(); i++){
        if(subscription[i].getCourseName() == "CISC320"){
            qDebug() << "CISC320 REACHED";
            ui->tabWidget->setTabEnabled(1,true);
            displayCategoriesForCourse(subscription[i], 1);
        }
        else if(subscription[i].getCourseName() == "ELEC451") {
            qDebug() << "ELEC451 REACHED";
            ui->tabWidget->setTabEnabled(2,true);
            displayCategoriesForCourse(subscription[i], 2);
        }
        else if(subscription[i].getCourseName() == "CISC124"){
            qDebug() << "CISC124 REACHED";
            ui->tabWidget->setTabEnabled(3,true);
            displayCategoriesForCourse(subscription[i], 3);
        }
    }

}

// displayCategoriesForCourse is called from displayApplicableCourseTabs each time it is determined
// that a particular course tab is enabled.The course associated with that tab (as determined by the course
// at subscription[i] in that function) is passed in, as well as the TabWidget index for that course.
// On that tab a QGroupBox is created (or in this case found, as they existed previously), that GroupBox
// given a vertical layout, which is populated by GroupBoxes of Course Categories, each with a horizontal
// layout populated by extension checkboxes.
void MainWindow::displayCategoriesForCourse(Course courseObj, int index){

    vector<CourseCategory> cats = courseObj.getCategories();

    ui->tabWidget->setCurrentIndex(index);
    QGroupBox * groupBox = ui->tabWidget->currentWidget()->findChild<QGroupBox*>(QString(), Qt::FindDirectChildrenOnly);
    QVBoxLayout * categoriesBox = new QVBoxLayout;
    for (unsigned long i = 0; i < cats.size(); i++){
        QGroupBox * catBox = new QGroupBox(QString::fromStdString(cats[i].getCategoryName()));
        QHBoxLayout * extensionsBox = new QHBoxLayout;
        vector<string> extensions = cats[i].getExtensionPreferences();

        for (unsigned long j = 0; j < extensions.size(); j++){
            QCheckBox * extension = new QCheckBox(QString::fromStdString(extensions[j]), this);
            extensionsBox->addWidget(extension);
        }
        catBox->setLayout(extensionsBox);
        catBox->setCheckable(true); //Category must be checked before extensions can be accessed
        catBox->setChecked(false);
        categoriesBox->addWidget(catBox);
    }
    groupBox->setLayout(categoriesBox);
}


void MainWindow::setupDirectoryExplorer(){

    //Due to an apparent bug in Qt 4.7.2, the version I'm using, the QFileSystemModel
    //doesn't work with resource files. I'm not sure if its fixed in version 5.
    //So resourcePath is the path to use if resources work, otherwise, make a path to
    //your desktop. This isn't expected to be a problem with the final version of QNoteGet
    //as the directories won't be Qt resources
    // see here : https://bugreports.qt.io/browse/QTBUG-25007
    //          : https://bugreports.qt.io/browse/QTBUG-7010

    //TO USE DIRECTORY EXPLORER:
    // Either: replace all uses of desktopPath with resourcePath
    //      or
    //          If resource path still not working, edit desktopPath to your desktop,
    //          place resource file in appropriately named folder on desktop (or wherever you'd like I guess)

    QString resourcePath = ":/dummyDirs/ExampleCourses";
    QString desktopPath = "/Users/Marshall/Desktop/ExampleCourses";

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); //hide "." and ".." folders, only display directories
    /*
     * QFileSystemModel will not fetch any files or directories until
     *  setRootPath() is called. This will prevent any unnecessary querying
     * on the file system until that point such as listing the drives on Windows.
     */
    dirModel->setReadOnly(true);
    ui->treeView_courseDirectories->setModel(dirModel);
    ui->treeView_courseDirectories->setRootIndex(dirModel->setRootPath(desktopPath));

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files); //only show files
    fileModel->setRootPath(dirModel->rootPath());
    ui->listView_courseFiles->setModel(fileModel);

    QModelIndex coursesIndex = ui->treeView_courseDirectories->rootIndex();
    ui->treeView_courseDirectories->expand(coursesIndex);
    ui->treeView_courseDirectories->setCurrentIndex(coursesIndex);
    ui->treeView_courseDirectories->resizeColumnToContents(0);
}

void MainWindow::on_saveButton_Cisc320_clicked()
{
    courseCategorySaveButtonClicked(dummyUser, 0);
}

// TODO: This function along with MainWindow::on_saveButton_Cisc320_clicked() serves as an EXAMPLE.
// Function/GUI should be changed to dynamically list the available categories etc. Using courseScraper information.
/*
 * void MainWindow::courseCategorySaveButtonClicked(int courseTabId) {
    //Where courseTabId = 0 (CISC320), 1(ELEC451), 2(CISC124)
    QList<QCheckBox *> allCategoriesSelected;

    //Note use of Qt::FindDirectChildrenOnly to ensure only direct children are listed.
    //Example if lectures, assignments etc. is chosen.
    if (courseTabId == 0) {
        allCategoriesSelected = ui->groupBox_CISC320->findChildren<QCheckBox *>(QString(),Qt::FindDirectChildrenOnly);
    } else if (courseTabId == 1) {
        allCategoriesSelected = ui->groupBox_ELEC451->findChildren<QCheckBox *>(QString(),Qt::FindDirectChildrenOnly);
    } else if (courseTabId == 2) {
        allCategoriesSelected = ui->groupBox_CISC124->findChildren<QCheckBox *>(QString(),Qt::FindDirectChildrenOnly);
    } else {
        cout << "ERROR, Invalid courseTabId." << endl;
        return;
    }

    vector<CourseCategory> courseCategoryObjects;

    //qDebug() << allCategoriesSelected.size();
    for(int i = 0; i < allCategoriesSelected.size(); ++i)
    {
        if(allCategoriesSelected.at(i)->isChecked()) {
            //Debug print for what categories were selected.
            qDebug() << "Using course category: " << allCategoriesSelected.at(i)->text();

            string categoryName = allCategoriesSelected.at(i)->text().toStdString();

            string groupBoxNameForCategory = allCategoriesSelected.at(i)->objectName().toStdString();
            //cout << groupBoxNameForCategory << endl;

            QList<QCheckBox *> allExtensionsSelected;
            // TODO: This is ugly code, we need a better way to do this...ASAP
            if (groupBoxNameForCategory == "LECT") {
                allExtensionsSelected = ui->groupBox_LECT->findChildren<QCheckBox *>(QString());
            } else if (groupBoxNameForCategory == "TUT") {
                allExtensionsSelected = ui->groupBox_TUT->findChildren<QCheckBox *>(QString());
            } else if (groupBoxNameForCategory == "ASSGN") {
                allExtensionsSelected = ui->groupBox_ASSGN->findChildren<QCheckBox *>(QString());
            }

            vector<string> choosenExtensions;
            //qDebug() << allExtensionsSelected.size();
            for(int i = 0; i < allExtensionsSelected.size(); ++i)
            {
                if(allExtensionsSelected.at(i)->isChecked()) {
                    qDebug() << "With file extension options: " << allExtensionsSelected.at(i)->text();
                    choosenExtensions.push_back(allExtensionsSelected.at(i)->text().toStdString());
                }
            }

            //Create course category object
            //TODO: Fill in appropriate file path, this should come from course scraper.
            courseCategoryObjects.push_back(CourseCategory(categoryName,"Blah blah some URL",choosenExtensions));
        }
    }

    //TODO: Link the course category objects to the course.


    return;
}
*/

void MainWindow::courseCategorySaveButtonClicked(User userObj, int courseTabId) {

    // Determine which course this tab applies to
    QString thisCourse;
    switch(courseTabId){
    case 1:
        thisCourse = "CISC320";
        break;
    case 2:
        thisCourse = "ELEC451";
        break;
    case 3:
        thisCourse = "CISC124";
        break;
    }

    // Because the User's courses will have different indices int their subscribedCourses based on what they select
    vector<Course> userCourses = userObj.getSubscribedCourses();
    int userCourseIndex;
    for (unsigned long i = 0; i < userCourses.size(); i++){
        if (userCourses[i].getCourseName() == thisCourse.toStdString()){
            userCourseIndex = i;
            break;
        }
    }

    ui->tabWidget->setCurrentIndex(courseTabId);
    //get the QGroupBox for the current tab
    QGroupBox * groupBox = ui->tabWidget->currentWidget()->findChild<QGroupBox*>(QString(), Qt::FindDirectChildrenOnly);
    //get the QGroupBoxes (the Course Categories) in the parent group box
    QList<QGroupBox *> categories = groupBox->findChildren<QGroupBox *>(QString(), Qt::FindDirectChildrenOnly);

    QList<QGroupBox *> chosenCategories;
    // if the groupBox isn't checked, then the user doesnt want that category
    // else, add to chosenCategories
    for (int i = 0; i < categories.size(); i++){
        if (!(categories.at(i)->isChecked())){
            //each category group box was initialized with the name from CourseCategory::getCategoryName
            userCourses[userCourseIndex].removeCategory(categories.at(i)->objectName().toStdString());
        }
        else{
            chosenCategories.push_back(categories.at(i));
        }
    }


    //get the (possibly trimmed down) CourseCategories vector for the course
    vector<CourseCategory> thisCourseCategories = userCourses[userCourseIndex].getCategories();

    // and now set the extension preferences for the categories they do want
    // assumption based on how everythings put together: thisCourseCategories and chosenCategories have same indices
    for (int i = 0; i < chosenCategories.size(); i++){
        vector<string> categoryExtensions;
        //FindChildrenRecursively (I think) since QHBoxLayout, not the checkboxes, is the direct child of each category GroupBox
        QList<QCheckBox *> extensionCheckboxes = chosenCategories.at(i)->findChildren<QCheckBox *>(QString(), Qt::FindChildrenRecursively);
        for (int i = 0; i < extensionCheckboxes.size(); i++){
            if(extensionCheckboxes[i]->isChecked()){
                //checkboxes objectNames were initilialized in displayCategoriesForCourse with CourseCategory::getExtensionPreferences names
                categoryExtensions.push_back(extensionCheckboxes[i]->objectName().toStdString());
            }
        }
        thisCourseCategories[i].setExtensionPreferences(categoryExtensions);
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString noteDir = QFileDialog::getExistingDirectory(this, "Choose a Destination...", QDir::homePath());
    ui->lineEdit_fileDirectory->setText(noteDir);
}

void MainWindow::getCredentials()
{
    Credentials dialog;
    dialog.validateCredentials("post.queensu.ca/~nm7/ELEC451/");
}

void MainWindow::on_button_getCredentials_clicked()
{
    getCredentials();
}
