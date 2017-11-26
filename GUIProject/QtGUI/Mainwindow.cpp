#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <typeinfo>
#include "Database/dbUserPreference.h"
#include "Database/dbExtension.h"
#include "Database/dbPreference.h"

static int currentIndex = 0;
vector<Course> dummy;
string path = "dummy";
string uname = "dummy";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),currentUserG(0,uname,1,path,2,dummy)
{
    createTaskBarIcon();

    //Set the application icon
#ifdef Q_OS_MACX
    QApplication::setWindowIcon(QIcon(":/newPrefix/appIcon.png"));
#else
    QApplication::setWindowIcon(QIcon(":/newPrefix/appIcon_linux.png"));
#endif

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(HOMEPAGE);
}

void MainWindow::createTaskBarIcon() {
    /* Create system tray icon to allow application to run in the background.
     * Using the Quit QNoteGet option the in taskbar menu is the only way to fully quit the application!
     */

    trayMenu = new QMenu(this);
    QAction* viewWindow = new QAction(trUtf8("View QNoteGet Window"), this);
    QAction* quitWindow = new QAction(trUtf8("Quit QNoteGet"), this);

    trayIcon = new QSystemTrayIcon(this);
    //trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setToolTip("QNoteGet Application");

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitWindow, SIGNAL(triggered()),this,SLOT(quitApplication()));

    trayIcon->setIcon(QIcon(":/newPrefix/trayIcon.png"));
    trayMenu->addAction(viewWindow);
    trayMenu->addAction(quitWindow);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void MainWindow::quitApplication() {
    /* Fully quit the application if the users quits through the taskbar icon */
    qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    /* If the "X" close button is pressed on the application, we want it to go into background mode.
     * We only want the application to fully QUIT if the "Quit QNoteGet" is triggered from the task bar.
     * This function overrides the close event method to make the application not actually close.
     */
    event->ignore();
    this->hide();
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

    trayIcon->showMessage("QNoteGet",
                          trUtf8("QNoteGet is still running from your tray toolbar to allow you to get notes on a regular basis!"),
                          icon,
                          2000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    bool valid = false;
    int dbPassword,dbInterval;
    string dbPath;
    currentIndex = ui->stackedWidget->currentIndex();
    if((ui->lineEdit_loginUsername->text().isEmpty()) ||(ui->lineEdit_loginPassword->text().isEmpty()))
    {
        QMessageBox::critical(this, "Empty Fields",
                      "Please enter your username and password.");
    } else {
        valid = validateUser(ui->lineEdit_loginUsername->text().toStdString(),ui->lineEdit_loginPassword->text().toStdString());

        if (valid){

            //Determine user password, path and update interval with passing by reference
            dbGetUserWithUsername(ui->lineEdit_loginUsername->text().toStdString(),dbPassword,dbPath,dbInterval);
            //Populate the global user object
            populateGlobalUserOnLogin(ui->lineEdit_loginUsername->text().toStdString(),dbPassword,dbPath,dbInterval);
            if( currentIndex < ui->stackedWidget->count())
            {
                // Can only setup directory explorer once we have global user object.
                setupDirectoryExplorer();
                ui->stackedWidget->setCurrentIndex(YOURCLASSESPAGE);
            }
        } else {
            QMessageBox::critical(this, "Incorrect Login",
                          "No account was found with these credentials. Try Again.");
        }
    }
}

// The following function fetches all of the information about an existing users subscription
// This will allow the global User object to be populated with the correct vector<Courses>
void MainWindow::populateGlobalUserOnLogin(string username,int pass, string path, int interval){
    int userId;
    vector<int> courses,categories,extensions;
    vector<int>::iterator catUnique;
    vector<string> extString;
    string extName,catName,coursePathName,catPathName,courseName;
    vector<CourseCategory> courseCat;
    vector<Course> coursesVec;

    dbGetUserByName(username,userId); // Get the user id from db
    dbGetUserCourses(userId,courses); //Determine all the courses user "id" subscribes to
    //Iterate through each course the user subscribed to
    for (auto courseID: courses) {
        //Create a Course object here
        dbGetCourse(courseID, courseName, coursePathName);
        dbGetUserPreferences(userId, courseID, categories);
        //Determine all unique categories the user subscribes to and resize "categories" vector
        catUnique = std::unique(categories.begin(),categories.end());
        categories.resize(std::distance(categories.begin(),catUnique));
        //Iterate through each of the unique categories the user subscribed to for one course (courseID)
        for (auto categoryID: categories) {
            dbGetPreference(categoryID,catName,catPathName);
            dbGetUserExtensions(userId, courseID, categoryID, extensions);
            //Iterate through all the extensions the user subscribed to for one category (categoryID)
            for (auto extensionID: extensions) {
                dbGetExtensionName(extensionID, extName);
                extString.push_back(extName); //Add the extension string
            }
            //Create CourseCategory object
            CourseCategory cc = CourseCategory(catName, catPathName, extString);
            // Add courseCategory object to vector<CourseCategory>
            courseCat.push_back(cc);
            //Clear the vector of extension strings and vector<int> of extensions which are passed by reference each
            //iteration
            extString.clear();
            extensions.clear();
        }
        //Create Course object once CourseCategory objects for that course have been populated
        Course course = Course(courseName,coursePathName,courseCat);
        coursesVec.push_back(course);
        // Clear categories vector which is passed by reference each iteration
        categories.clear();
    }
    //Set global user
    currentUserG = User(userId,username,pass,path,interval,coursesVec);
}

void MainWindow::on_pushButton_doneSubscribe_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      setupDirectoryExplorer();
      qDebug() << "On doneSubscribe clicked!";

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
    //Use boost::hash over std::hash, as boost::hash is the same on MAC vs LINUX gcc.
    boost::hash<std::string> string_hash;
    std::size_t str_password_hash = string_hash(password);
    return str_password_hash;
}

/*
 * Function to create the User object and any associated DB calls. (including adding which courses the user is subscribed to)
 */
bool MainWindow::createUser(string username, int password, string path, int interval, vector<Course> userCourses){
    int dbPassword, dbUpdate;
    string dbPath;
    bool result = dbGetUserWithUsername(username,dbPassword, dbPath, dbUpdate);

    if(result == false){

        int userId = dbCreateUser(username,password,path,interval);

        User userAccount = User(userId,username,password,path,interval,userCourses);
        //TODO:: check that userCourses object has filled in information from predefined
        currentUserG = userAccount;
        displayApplicableCourseTabs();

        // Create entry in usercourses DB table for each course the user has subscribed to.
        for(auto userCourse: userCourses) {
            int courseId;
            dbGetCourseId(courseId, userCourse.getCourseName());
            dbCreateUserCourse(userId,courseId);

            //By default, all categories and extensions are selected, so below places in db
            vector<CourseCategory> courseCats = userCourse.getCategories();
            for (unsigned long i = 0; i < courseCats.size(); i++){
                int prefID;
                dbGetPreferenceIdByName(courseId, courseCats[i].getCategoryName(), prefID);
                vector<string> catExt = courseCats[i].getExtensionPreferences();
                vector<int> extIDs;
                for (unsigned long j = 0; j < catExt.size(); j++){
                    int extID;
                    dbGetExtensionID(extID, catExt[j]);
                    extIDs.push_back(extID);
                }
                dbCreateMultipleUserPreferences(userId, courseId, prefID, extIDs);
            }

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
    int dbPassword;
    string dbUserPath;
    int dbUpdateInterval;

    int result = dbGetUserWithUsername(username, dbPassword, dbUserPath, dbUpdateInterval);
    if (result == false)
        std::cerr << "Failed to find username in user database table!" << std::endl;

    return(passwordHashed == dbPassword);
}

/*
 * Function to create user specific Course objects depending on which courses they chose in the GUI.
 * Returns vector of course objects.
 */
vector<Course> MainWindow::createUserCourseObjects(){
    vector<Course> courseVector;

    // Note, The GUI ensures atleast one of these items is checked.
    if (ui->checkBox_cisc320->isChecked()) {
        for (auto courseObj: preDefinedCourses){
            if (courseObj.getCourseName() == "CISC320") {
                courseVector.push_back(Course(courseObj));//Copy pre-defined course for User specific course.
                courseEditsMade.push_back(false);
            }
        }
    }
    if (ui->checkBox_cisc124->isChecked()) {
        for (auto courseObj: preDefinedCourses){
            if (courseObj.getCourseName() == "CISC124"){
                courseVector.push_back(Course(courseObj)); //Copy pre-defined course for User specific course.
                courseEditsMade.push_back(false);
            }
        }
    }
    if (ui->checkBox_elec451->isChecked()) {
        for (auto courseObj: preDefinedCourses){
            if (courseObj.getCourseName() == "ELEC451") {
                courseVector.push_back(Course(courseObj)); //Copy pre-defined course for User specific course.
                courseEditsMade.push_back(false);
            }
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


void MainWindow::on_pushButton_editSubs_clicked()
{
    displayApplicableCourseTabs();
    qDebug() << "On editSubs clicked!";
    clearCourseTabs();
    repopulateUserSubs();
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


void MainWindow::displayApplicableCourseTabs(){
    vector<Course> subscription = currentUserG.getSubscribedCourses();

    // all disabled by default
    ui->tabWidget->setTabEnabled(1,false); //cisc320
    ui->tabWidget->setTabEnabled(2,false); //elec451
    ui->tabWidget->setTabEnabled(3, false); //cisc124

    for (unsigned long i = 0; i < subscription.size(); i++){
        if(subscription[i].getCourseName() == "CISC320"){
            qDebug() << "CISC320 REACHED";
            ui->tabWidget->setTabEnabled(1,true);
            displayCategoriesForCourse(preDefinedCourses[0], 1);
        }
        else if(subscription[i].getCourseName() == "ELEC451") {
            qDebug() << "ELEC451 REACHED";
            ui->tabWidget->setTabEnabled(2,true);
            displayCategoriesForCourse(preDefinedCourses[1], 2);
        }

        else if(subscription[i].getCourseName() == "CISC124"){
            qDebug() << "CISC124 REACHED";
            ui->tabWidget->setTabEnabled(3,true);
            displayCategoriesForCourse(preDefinedCourses[2], 3);
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
    // Make sure groupBox doesnt already have children (for when this may be called from login or edit subs)
    QList<QGroupBox *> possibleChildren = groupBox->findChildren<QGroupBox *>();

    if (possibleChildren.size() == 0 && groupBox->layout() != 0){
        QLayout * layout = groupBox->layout();
        delete layout;
    }

    // If this function gets called after initial Sign Up set up, dont need to reset these, just clear their
    // checkboxes. Calling from a second login or on edit subs causes error trying to overwrite old layouts
    if (possibleChildren.size() == 0){
        QVBoxLayout * categoriesBox = new QVBoxLayout;

        QLabel * categoriesBoxLabel = new QLabel("Course Categories", this);
        categoriesBoxLabel->setStyleSheet("QLabel {background-position: top; font-weight: bold}");
        categoriesBox->addWidget(categoriesBoxLabel);

        for (unsigned long i = 0; i < cats.size(); i++){
            QString catName = QString::fromStdString(cats[i].getCategoryName());
            QGroupBox * catBox = new QGroupBox(catName, this);
            QHBoxLayout * extensionsBox = new QHBoxLayout;
            vector<string> extensions = cats[i].getExtensionPreferences();

            for (unsigned long j = 0; j < extensions.size(); j++){
                QCheckBox * extension = new QCheckBox(QString::fromStdString(extensions[j]), this);
                extension->setChecked(true);
                extensionsBox->addWidget(extension);
            }
            catBox->setLayout(extensionsBox);
            catBox->setCheckable(true); //Category must be checked before extensions can be accessed
            catBox->setChecked(true);
            categoriesBox->addWidget(catBox);
        }
        groupBox->setLayout(categoriesBox);
    }
}


//NOTE: Qt actually saves the state of the checkboxes when you leave the page (its all in the same window)
//This functionality is for the hypothetical case in which a new user visits the page after another has logged out, and
//the previous choices need to be cleared. clearCourseTabs() is called before this function.
void MainWindow::repopulateUserSubs(){

    vector<Course> subscriptions = currentUserG.getSubscribedCourses();

    //For each of the user's subscribed courses
    for (unsigned long i = 0; i < subscriptions.size(); i++){
        //get their CourseCategories
        vector<CourseCategory> cats = subscriptions[i].getCategories();

        for (int j = 0; j < ui->tabWidget->count(); j++){
            ui->tabWidget->setCurrentIndex(j);

            //Find the corresponding course tab by matching tab_CourseName to CourseName with substring Course name
            if (ui->tabWidget->currentWidget()->isEnabled()
                    && ui->tabWidget->currentWidget()->objectName().contains(QString::fromStdString(subscriptions[i].getCourseName()), Qt::CaseInsensitive)){

                QGroupBox * topGroupBox = ui->tabWidget->currentWidget()->findChild<QGroupBox*>();
                //get all the category group boxes
                QList<QGroupBox *> catGroupBoxes = topGroupBox->findChildren<QGroupBox *>(QString(), Qt::FindDirectChildrenOnly);

                // Go through the users CourseCategories, match them to the category group boxes
                for (unsigned long k = 0; k < cats.size(); k++){
                    for (int l = 0; l < catGroupBoxes.size(); l++){
                        if (QString::fromStdString(cats[k].getCategoryName()) == catGroupBoxes[l]->title()){
                            //if its in the users CourseCategories in the first place, it should be checked
                            catGroupBoxes[l]->setChecked(true);


                            //and that means we have to check its appropriate children extensions
                            QList<QCheckBox *> extensionBoxes = catGroupBoxes[l]->findChildren<QCheckBox *>(QString(), Qt::FindDirectChildrenOnly);
                            vector<string> userExtensions = cats[k].getExtensionPreferences();

                            for (unsigned long m = 0; m < userExtensions.size(); m++){
                                for (int n = 0; n < extensionBoxes.size(); n++){
                                    if (QString::fromStdString(userExtensions[m]) == extensionBoxes[n]->text()){
                                        extensionBoxes[n]->setChecked(true);
                                        break;
                                    }
                                }
                            }
                            break; //don't need to check the rest of the category boxes
                        }

                    }
                }
                break; //dont need to look at the rest of the tabs
        }
        }
    }
}

//NOTE: Qt actually saves the state of the checkboxes when you leave the page (its all in the same window)
//This functionality is for the hypothetical case in which a new user visits the page after another has logged out, and
//the previous choices need to be cleared. repopulateUserSubs() is called after
void MainWindow::clearCourseTabs(){

    //start at 1 because 0 is Account details tab
    for (int i = 1; i < ui->tabWidget->count(); i++){
        ui->tabWidget->setCurrentIndex(i);
        QGroupBox * courseGroup = ui->tabWidget->currentWidget()->findChild<QGroupBox *>(QString(), Qt::FindDirectChildrenOnly);
        QList<QGroupBox *> categories = courseGroup->findChildren<QGroupBox *>(QString(), Qt::FindDirectChildrenOnly);
        for (auto cat : categories){
            //Have to uncheck all children, unchecking group box doesnt uncheck extension checkboxes
            QList<QCheckBox *> extensions = cat->findChildren<QCheckBox *>();
            for (auto checkbox : extensions){
                if (checkbox->isChecked()){
                    checkbox->setChecked(false);
                }
            }
            //now you can uncheck the groupbox itself
            if (cat->isChecked()){
                cat->setChecked(false);
            }
        }
    }

}


void MainWindow::setupDirectoryExplorer(){

    QString selectedPath = QString::fromStdString(currentUserG.getFileDirectory());
    qDebug() << "in setupDirectoryExplorer, selectedPath is: " << selectedPath;

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); //hide "." and ".." folders, only display directories
    /*
     * QFileSystemModel will not fetch any files or directories until
     *  setRootPath() is called. This will prevent any unnecessary querying
     * on the file system until that point such as listing the drives on Windows.
     */
    dirModel->setReadOnly(true);
    ui->treeView_courseDirectories->setModel(dirModel);
    ui->treeView_courseDirectories->setRootIndex(dirModel->setRootPath(selectedPath));

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files); //only show files
    fileModel->setRootPath(dirModel->rootPath());
    ui->listView_courseFiles->setModel(fileModel);

    QModelIndex coursesIndex = ui->treeView_courseDirectories->rootIndex();
    ui->treeView_courseDirectories->expand(coursesIndex);
    ui->treeView_courseDirectories->setCurrentIndex(coursesIndex);
    ui->treeView_courseDirectories->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->treeView_courseDirectories->resizeColumnToContents(0);
}

void MainWindow::on_saveButton_Cisc320_clicked()
{
    courseCategorySaveButtonClicked(1);
}

void MainWindow::on_saveButton_Elec451_clicked()
{
    courseCategorySaveButtonClicked(2);
}


void MainWindow::on_saveButton_Cisc124_clicked()
{
    courseCategorySaveButtonClicked(3);
}


void MainWindow::courseCategorySaveButtonClicked(int courseTabId) {

    //for use with DB calls
    int userID = currentUserG.getUserId();
    int courseID;
    vector<int> preferenceIDs;

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
    vector<Course*> userCourses = currentUserG.getSubscribedCoursesByPtr();

    int userCourseIndex = -1; //error if used, but shuts up uninitialized warning
    for (unsigned long i = 0; i < userCourses.size(); i++){
        if (userCourses[i]->getCourseName() == thisCourse.toStdString()){
            userCourseIndex = i;
            break;
        }
    }

    //set the CourseID
    try{
        if (dbGetCourseId(courseID, thisCourse.toStdString())){}
        else{
            QString dbError = "ERROR: Could not retrieve course ID from database.";
            throw dbError;
        }
    }
    catch(QString& dbError){
        QMessageBox::critical(this, "Get Course ID Error", dbError);
    }

    try{
        //set the PreferenceIDs
        if(dbGetUserPreferences(userID, courseID, preferenceIDs)){
            qDebug() << "Got preferences! They are:";
            for (unsigned long i = 0; i < preferenceIDs.size(); i++){
                qDebug() << preferenceIDs[i];
            }
        }
        else{
            if (!courseEditsMade[userCourseIndex]){ //behaviour only unexpected if its users first time through, otherwise they may have deleted these preferences
            QString getPreferenceError = "No preferences obtained for user: " + QString::fromStdString(currentUserG.getUsername());
            throw getPreferenceError;
            }
        }
    }
    catch(QString& error){
        QMessageBox::critical(this, "Preferences Not Obtained", error);
    }
    catch(...){
        qDebug() << "No preferences obtained for user";
    }


    ui->tabWidget->setCurrentIndex(courseTabId);
    //get the QGroupBox for the current tab
    QGroupBox * groupBox = ui->tabWidget->currentWidget()->findChild<QGroupBox*>(QString(), Qt::FindDirectChildrenOnly);
    //get the QGroupBoxes (the Course Categories) in the parent group box
    QList<QGroupBox *> categories = groupBox->findChildren<QGroupBox *>(QString(), Qt::FindDirectChildrenOnly);

    if (!courseEditsMade[userCourseIndex]){ //if its the users first time making a selection of categories
        QList<QGroupBox *> chosenCategories;
        vector<int> idsToDelete; //to cut down on db calls

        // if the groupBox isn't checked, then the user doesnt want that category
        // else, add to chosenCategories
        for (int i = 0; i < categories.size(); i++){
            if (!(categories.at(i)->isChecked())){
                //each category group box was initialized with the name from CourseCategory::getCategoryName
                qDebug() << "preferenceID.size is: " << preferenceIDs.size();
                userCourses[userCourseIndex]->removeCategory(categories.at(i)->title().toStdString()); //Note: GroupBoxes use title, not objectName

                idsToDelete.push_back(preferenceIDs[i]);
                qDebug() << "It gets here";
            }
            else{
                chosenCategories.push_back(categories.at(i));
            }
        }

        if (idsToDelete.size() > 0){
            try{
                qDebug() << "First deletion. idsToDelete size is: " << idsToDelete.size() << " and they are: ";
                for (int i = 0; i < idsToDelete.size(); i++){
                    qDebug() << idsToDelete[i];
                }

                if(dbDeleteUserCategoryPreference(userID, courseID, idsToDelete)){ //deletes from database. Note: categories and preferenceIDs represent the same array of categories
                    qDebug() << "Successfully removed from database!";
                }
                else{
                    QString dbError = "ERROR: Deletion of preference IDs from database unsuccessful";
                    throw dbError;
                }
            }
            catch(QString& error){
                QMessageBox::critical(this, "Database Deletion Error", error);
            }
            catch(...){
                qDebug() << "ERROR: Deletion of preference IDs from database unsuccessful";
            }
        }
        //get the (possibly trimmed down) CourseCategories vector for the course
        vector<CourseCategory *> thisCourseCategories = userCourses[userCourseIndex]->getCategoriesByPtr();

        // and now set the extension preferences for the categories they do want
        // assumption based on how everythings put together: thisCourseCategories and chosenCategories have same indices
        for (int i = 0; i < chosenCategories.size(); i++){
            vector<string> categoryExtensions;
            //FindChildrenRecursively (I think) since QHBoxLayout, not the checkboxes, is the direct child of each category GroupBox
            QList<QCheckBox *> extensionCheckboxes = chosenCategories.at(i)->findChildren<QCheckBox *>(QString(), Qt::FindChildrenRecursively);
            vector<int> extIDsToDelete;
            for (int i = 0; i < extensionCheckboxes.size(); i++){
                if(extensionCheckboxes[i]->isChecked()){
                    //checkboxes text were initilialized in displayCategoriesForCourse with CourseCategory::getExtensionPreferences names
                    categoryExtensions.push_back(extensionCheckboxes[i]->text().toStdString());
                }
                else{
                    int extID;
                    try{
                        if(dbGetExtensionID(extID, extensionCheckboxes[i]->text().toStdString())){
                            qDebug() << "SUccess! got extID, it is " << extID;
                        }
                        else{
                            QString dbError = "ERROR: Could not obtain an extension ID upon initial save";
                            throw dbError;
                        }

                    }
                    catch(QString& error){
                        QMessageBox::critical(this, "DBGetExtensionID Error", error);
                    }

                    extIDsToDelete.push_back(extID);
                }

            }
            if (extIDsToDelete.size() > 0){
            try{
                    int prefID;
                    try{
                        if(dbGetPreferenceIdByName(courseID, chosenCategories[i]->title().toStdString(), prefID)){
                            qDebug() << "GOT PREF ID!";
                        }
                        else{
                            QString dbError = "ERROR: Could not obtain preference ID by name upon saving";
                            throw dbError;
                        }
                    }
                    catch(QString& error){
                        QMessageBox::critical(this, "GET PREFERENCE BY ID NAME ERROR", error);
                    }

                    if(dbDeleteUserExtensionPreference(userID, courseID, prefID, extIDsToDelete)){
                        qDebug() << "USER EXTENESIO PREFERENCES DELETED";
                    }
                    else{
                        QString dbError = "ERROR: Could not delete extension preferences";
                        throw dbError;
                    }

            }
                catch(QString& error){
                    QMessageBox::critical(this, "Delete User Extension Preference Error", error);
                }
            }
            thisCourseCategories[i]->setExtensionPreferences(categoryExtensions);
        }
        courseEditsMade[userCourseIndex] = true; // after user clicks save for first time, edits made is true
    }
    else{ //this is not the users first time picking categories
        vector<CourseCategory> beforeSubs = userCourses[userCourseIndex]->getCategories(); // use the pointer to the users Course Category before state
        // and pass the pointer to the global users courses, identifiers of the course, and the category group box list for setting edited subscriptions
        vector<CourseCategory> afterSubs = editSubscription(userCourses, userCourseIndex, thisCourse, categories);
        compareEditedSubscriptions(courseID, beforeSubs, afterSubs);

    }

    vector<CourseCategory> afterCats = userCourses[userCourseIndex]->getCategories();
    qDebug() << "currentUserG's categories after selection are: ";
    for (unsigned long i = 0; i < afterCats.size(); i++){
        qDebug() << QString::fromStdString(afterCats[i].getCategoryName());
    }

}


// editSubscription takes the pointer to the heap allocated user's Courses' pointers, created in
// courseCategorySaveButtonClicked, as well as info for the particular course, and the list of categories.
// it sets the User's CourseCategory preferences for that Course, and passes back the changed vector
// for later use with compareEditedSubscriptions
// NOTE: editedSubscriptions edits the global user object, not the database. compareEditedSubscriptions
// edits the database, due to certain db-specific function calls being required
vector<CourseCategory> MainWindow::editSubscription(vector<Course*> userCourses, int userCourseIndex, QString thisCourse, QList<QGroupBox*> categories){

    vector<CourseCategory> newSubscriptions;


    //find the predefined course of the same name as the one were editing subscriptions for
    int preDefCourseIndex = -1; //to shut up warning
    for (unsigned long i = 0; i < preDefinedCourses.size(); i++){
        if (thisCourse == QString::fromStdString(preDefinedCourses[i].getCourseName())){
            preDefCourseIndex = i;
            break;
        }
    }
    //and then get those CourseCategories
    vector<CourseCategory> preDefCats = preDefinedCourses[preDefCourseIndex].getCategories();

    for (int i = 0; i < categories.size(); i++){
        if (categories[i]->isChecked()){

            //Get the extension preferences first
            QList<QCheckBox*> chosenExtensions = categories[i]->findChildren<QCheckBox*>();
            vector<string> newExtensionPrefs;
            for (int j = 0; j < chosenExtensions.size(); j++){
                if (chosenExtensions[j]->isChecked()){
                    newExtensionPrefs.push_back(chosenExtensions[j]->text().toStdString());
                }
            }
            preDefCats[i].setExtensionPreferences(newExtensionPrefs);

            // Now add to newSubscriptions
            //Original categories QList based on preDefinedCourses, so have same indices
            newSubscriptions.push_back(preDefCats[i]);
        }
    }

    userCourses[userCourseIndex]->setCategories(newSubscriptions);
    return newSubscriptions;

}

// Function only called if not the users first time choosing subscriptions, from courseCategorySavedButtonClicked
// This check is made at on_pushButton_editSubs_clicked() with changing courseEditsMade to true
// beforeSubs is set in courseCategorySaveButtonClicked before call to editSubscription made
// afterSubs is a copy of the results of that call.
// compareEditedSubscriptions compares the differences and makes the appropriate db calls
void MainWindow::compareEditedSubscriptions(const int courseID, vector<CourseCategory> beforeSubs, vector<CourseCategory> afterSubs){

    int userID = currentUserG.getUserId();
    vector<int> prefIDs;
    if (beforeSubs.size() > 0){
        try{
            if (dbGetUserPreferences(userID, courseID, prefIDs)){ //this maps to beforeSubs since no db calls have changed subscription list
                //qDebug() << "dbGetUserPreferences called succesfully. PrefIDs are: ";
                for (size_t i = 0; i < prefIDs.size(); i++){
                    //qDebug() << prefIDs[i];
                }
            }
            else{
                QString dbError = "ERROR: Unable to retrieve user preference IDs";
                throw dbError;
            }
        }
        catch(QString& error){
            QMessageBox::critical(this, "Get User Preference Error", error);
        }
        catch(...){
            //qDebug() << "ERROR: Unable to retrieve user preference IDs";
        }
    }
    vector<int> idsToDelete; //category preferences
    vector<int> userBeforeExtensionPrefIDs;
    vector<int> extensionIDsToDelete;
    vector<string> fakeExts = {};
    CourseCategory fakeCat("FAKE CATEGORY", "FAKEPATH", fakeExts); //for placeholding in before/after subs so vectors can be compared easily

            // 4 Scenarios
            // 1 - user was subscribed, but checkbox unchecked -> will be present in beforeSubs, but not afterSubs. Call dbDelete
            // 2 - user was subscribed, checkbox still checked -> present in both Subs, but extensions may have changed
            // 3 - user was not subscribed, checkbox checked -> not present in beforeSubs, present in afterSubs. Call dbCreate
            // 4 - user was not subscribed, checkbox still unchecked -> no need to do anything, not that you could know what youre missing

    if (beforeSubs.size() > 0){ //if there are no before-subs, no need to check any of this
        //check for old subscriptions not renewed
        for (unsigned long i = 0; i < beforeSubs.size(); i++){
            bool beforeNotAfter = true;
            //qDebug() << "beforeSubs[i]: " << QString::fromStdString(beforeSubs[i].getCategoryName());
            for (unsigned long j = 0; j < afterSubs.size(); j++){
                //qDebug() << "afterSubs[j]: " << QString::fromStdString(afterSubs[j].getCategoryName());

                if (beforeSubs[i].getCategoryName() == afterSubs[j].getCategoryName()){
                    beforeNotAfter = false;
                    //qDebug() << "beforeNotAfter changed, it is now " << beforeNotAfter;
                    break;
                }
            }
            if (beforeNotAfter){ //Scenario 1
                //qDebug() << "IT IS BEFORE NOT AFTER with prefID: " << prefIDs[i];
                idsToDelete.push_back(prefIDs[i]);
                vector<CourseCategory>::iterator it;
                it = afterSubs.begin();
                advance(it, i); //get iterator to position that is absent in afterSubs
                afterSubs.insert(it, fakeCat);
                //qDebug() << "Insertion successful! afterSubs is now: ";
                for (size_t z = 0; z < afterSubs.size(); z++){
                    //qDebug() << QString::fromStdString(afterSubs[z].getCategoryName());
                }
            }
            else{ //Scenario 2
                //But still need to check if extensions were changed
                //qDebug() << "EXECUTION GETS HEREEEE TO SCENEARIO 2";
                //qDebug() << "beforeSubs.size() is " << beforeSubs.size() << " and afterSubs.size() is " << afterSubs.size();
                //qDebug() << "but i is: " << i;
                //if a category's been added, shifts afterSubs so that beforeSubs[i] != afterSubs[i], so have to find matching category
                int matchingAfterCat = -1;
                for (unsigned long z = 0; z < afterSubs.size(); z++){
                    if (afterSubs[z].getCategoryName() == beforeSubs[i].getCategoryName()){
                        matchingAfterCat = z;
                        break;
                    }
                }
                vector<string> beforeExtensions = beforeSubs[i].getExtensionPreferences();
                vector<string> afterExtensions = afterSubs[matchingAfterCat].getExtensionPreferences();
                //qDebug() << "beforeExtensions size is: " << beforeExtensions.size() << "for cat: " << QString::fromStdString(beforeSubs[i].getCategoryName()) << " and those extensions are: ";
                //for (unsigned long z = 0; z < beforeExtensions.size(); z++) { //qDebug() << QString::fromStdString(beforeExtensions[z]);}
                //qDebug() << "afterExtensions size is: " << afterExtensions.size() << " for cat: " <<QString::fromStdString(afterSubs[matchingAfterCat].getCategoryName()) << " and those extensions are: ";
                //for (unsigned long z = 0; z < afterExtensions.size(); z++){//qDebug() << QString::fromStdString(afterExtensions[z]);}
                //qDebug() << "size of prefIds: " << prefIDs.size();
                //qDebug() << "userID is: " << userID << "courseID is: " << courseID << " prefIDs are: " << prefIDs[i] << " and userBeforeExtensionPredIDs size is: " << userBeforeExtensionPrefIDs.size();
                try{
                    if (dbGetUserExtensions(userID, courseID, prefIDs[i], userBeforeExtensionPrefIDs)){
                        //qDebug() << "userBeforeExtensionPrefIDs size is: " << userBeforeExtensionPrefIDs.size();
                        //qDebug() << "dbGetUserExtensions called successfully. userBeforeExtensionPrefIDs are: ";
                        for (size_t z = 0; z < userBeforeExtensionPrefIDs.size(); z++){
                            //qDebug() << userBeforeExtensionPrefIDs[z];
                        }
                    }
                    else{
                        QString dbError = "ERROR: Unable to retrieve user extension IDs";
                        //qDebug() << "ERROR: Unable to retrieve user extension IDs for courseID: " << courseID << " and prefID: " << prefIDs[i];
                        throw dbError;
                    }
                }
                catch(QString& error){
                    QMessageBox::critical(this, "Get User Extensions Error", error);
                }
                catch(...){
                    //qDebug() << "ERROR: Unable to retrieve user extension IDs";
                }
                //do the same thing another level down
                //qDebug() << "AND ALSO GETS HERE";
                for (unsigned long k = 0; k < beforeExtensions.size(); k++){
                    beforeNotAfter = true;
                    for (unsigned long l = 0; l < afterExtensions.size(); l++){
                        if (beforeExtensions[k] == afterExtensions[l]){
                            beforeNotAfter = false;
                        }
                    }
                    if (beforeNotAfter){ //only removes extensions
                        //qDebug() << "userBeforeExtensionPrefIDs size is: " << userBeforeExtensionPrefIDs.size();
                        extensionIDsToDelete.push_back(userBeforeExtensionPrefIDs[k]);
                    }
                }

                userBeforeExtensionPrefIDs.clear(); // clear so can be used fresh on next category iteration

                //but also must check if extensions added to a still-checked category
                //do the reverse, if AfterNotBefore, add category
                for (unsigned long k = 0; k < afterExtensions.size(); k++){
                    bool afterNotBefore = true;
                    for (unsigned long l = 0; l < beforeExtensions.size(); l++){
                        if (afterExtensions[k] == beforeExtensions[l]){
                            afterNotBefore = false;
                        }
                    }
                    if (afterNotBefore){ //need to add extension to db
                        int extID;
                        try{
                            if (dbGetExtensionID(extID, afterExtensions[i])){}
                            else{
                                QString dbError = "ERROR: Unable to retrieve extension IDs";
                                throw dbError;
                            }
                        }
                        catch(QString& error){
                            QMessageBox::critical(this, "Get Extension ID Error", error);
                        }
                        catch(...){
                            //qDebug() << "ERROR: Unable to retrieve extension IDs";
                        }
                        try{
                            if (dbCreateUserPreference(userID, courseID, prefIDs[i], extID)){}
                            else{
                                QString dbError = "ERROR: Unable to create user preferences";
                                throw dbError;
                            }
                        }
                        catch(QString& error){
                            QMessageBox::critical(this, "Create User Preferences Error", error);
                        }
                        catch(...){
                            //qDebug() << "ERROR: Unable to create user preferences";
                        }

                    }
                }
            }
            if (extensionIDsToDelete.size() > 0){
                //qDebug() << "GETS TO EXTENSIONIDSTODELETE";
                //qDebug() << "for prefID " << prefIDs[i] << " extensionIdsToDelete size is: " << extensionIDsToDelete.size() << " and they are: ";
                for (size_t z = 0; z < extensionIDsToDelete.size(); z++){
                    //qDebug() << extensionIDsToDelete[z];
                }
                try{
                    if (dbDeleteUserExtensionPreference(userID, courseID, prefIDs[i], extensionIDsToDelete)){}
                    else{
                        QString dbError = "ERROR: Unable to delete user extension preferences";
                        throw dbError;
                    }
                }
                catch(QString& error){
                    QMessageBox::critical(this, "Delete User Extension Preferences Error", error);
                }
                catch(...){
                    //qDebug() << "ERROR: Unable to delete user extension preferences";
                }

                extensionIDsToDelete.clear();
            }
        }

        if (idsToDelete.size() > 0){
            try{
                //qDebug() << "About to make a delete preference call";
                //qDebug() << "idsToDelete.size is" << idsToDelete.size() << " and they are: ";
                if (idsToDelete.size() > 0){
                    for (size_t z = 0; z < idsToDelete.size(); z++){
                        //qDebug() << idsToDelete[z];
                    }
                }
                if (dbDeleteUserCategoryPreference(userID, courseID, idsToDelete)){}
                else{
                    QString dbError = "ERROR: Unable to delete user category preferences";
                    throw dbError;
                }
            }
            catch(QString& error){
                QMessageBox::critical(this, "Delete User Category Preferences Error", error);
            }
            catch(...){
                //qDebug() << "ERROR: Unable to delete user category preferences";
            }

            idsToDelete.clear();
        }
    }

    //check for new subscriptions
    for (unsigned long i = 0; i < afterSubs.size(); i++){
        bool afterNotBefore = true;
        for (unsigned long j = 0; j < beforeSubs.size(); j++){
            if (afterSubs[i].getCategoryName() == beforeSubs[j].getCategoryName()){
                afterNotBefore = false;
            }
        }
        if (afterNotBefore && afterSubs[i].getCategoryName() != "FAKE CATEGORY"){ //Scenario 3
            // Need to add top level category
            // Note: making a single call to DB and getting a vector<int> of course pref IDs unfortunately doesnt
            // work here, because afterSubs is not necessarily the size of all possible category subs, and so
            // a vector<int> coursePrefIDs[i] /= afterSubs[i] in all cases
            //qDebug() << "AFTER NOT BEFORE is true for: " << QString::fromStdString(afterSubs[i].getCategoryName());
            int prefID;
            try{
                if (dbGetPreferenceIdByName(courseID, afterSubs[i].getCategoryName(), prefID)){}
                else{
                    QString dbError = "ERROR: Unable to get preference IDs by name";
                    throw dbError;
                }
            }
            catch(QString& error){
                QMessageBox::critical(this, "Get Preference ID by Name Error", error);
            }
            catch(...){
                //qDebug() << "ERROR: Unable to get preference IDs by name";
            }

            //also need to add extensions
            vector<string> prefExtensions = afterSubs[i].getExtensionPreferences();
            vector<int> prefExtensionIDs;
            int prefExtensionID;
            for (unsigned long k = 0; k < prefExtensions.size(); k++){
                try{
                    if (dbGetExtensionID(prefExtensionID, prefExtensions[k])){}
                    else{
                        QString dbError = "ERROR: Unable to get extension IDs";
                        throw dbError;
                    }
                }
                catch(QString& error){
                    QMessageBox::critical(this, "Get Extension ID Error", error);
                }
                catch(...){
                    //qDebug() << "ERROR: Unable to get extension IDs";
                }

                prefExtensionIDs.push_back(prefExtensionID);
            }
            try{
                vector<int> userPreferenceIDs = dbCreateMultipleUserPreferences(userID, courseID, prefID, prefExtensionIDs);
                if (userPreferenceIDs[0] != -1){}
                else{
                    QString dbError = "ERROR: Unable to create user preferences";
                    throw dbError;
                }
            }
            catch(QString& error){
                QMessageBox::critical(this, "Create User Preferences Error", error);
            }
            catch(...){
                //qDebug() << "ERROR: Unable to create user preferences";
            }

        } //and then Scenario 4 is do nothing
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

//TODO: Create a backend class that takes some of this out of main window.
//As well, add some error checking for return codes of the DB calls.
void MainWindow::populatePreDefineCourseObjects() {
    vector<int> courseIds;

    //Get all DB course IDs.
    dbGetAllCourses(courseIds);

    string courseName;
    string coursePath;
    string preferenceName;
    string preferencePath;
    Backend b;

    //Populate course and CourseCategory objects for all courses in DB.
    for (auto courseId : courseIds){
        dbGetCourse(courseId, courseName, coursePath);

        //Get all preference ID's associated with course.
        vector<int> preferenceIds;
        dbGetPreferenceIds(courseId,preferenceIds);
        //Create course category objects for course.
        vector<CourseCategory> courseCategories;
        for (auto preferenceId: preferenceIds) {
            dbGetPreference(preferenceId,preferenceName,preferencePath);

            //Use course scraper to get file extensions available on the page
            vector<string> fileExtensions = {};

            //Must clear urlsVisited and fileExt vectores before calling getExtensionsAtUrl.
            b.urlsVisited.clear();
            b.fileExt.clear();
            fileExtensions = b.getExtensionsAtUrl(preferencePath);

            CourseCategory cc = CourseCategory(preferenceName, preferencePath, fileExtensions);
            courseCategories.push_back(cc);

        }
        preDefinedCourses.push_back(Course(courseName, coursePath, courseCategories));
    }
}

void MainWindow::on_actionExit_triggered()
{
    /* Use the function to fully quit the application, not just hide the application. */
    quitApplication();
}




