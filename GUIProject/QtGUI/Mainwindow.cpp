#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <typeinfo>

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
    QApplication::setWindowIcon(QIcon(":/newPrefix/appIcon.png"));

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(HOMEPAGE);
    setupDirectoryExplorer();
    editsMade = false; //for use with editSubscriptions button
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
    currentIndex = ui->stackedWidget->currentIndex();
    if((ui->lineEdit_loginUsername->text().isEmpty()) ||(ui->lineEdit_loginPassword->text().isEmpty()))
    {
        QMessageBox::critical(this, "Empty Fields",
                      "Please enter your username and password.");
    } else {
        valid = validateUser(ui->lineEdit_loginUsername->text().toStdString(),ui->lineEdit_loginPassword->text().toStdString());
        if (valid){

            //populateGlobalUserOnLogin(ui->lineEdit_loginUsername->text().toStdString());

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

// The following function fetches all of the information about an existing users subscription
// This will allow the global User object to be populated with the correct vector<Courses>
void MainWindow::populateGlobalUserOnLogin(string username){
    //dbCreateUserPreference(104, 1, 3, 8);
    int id;
    vector<int> courses,categories,extensions;
    vector<int>::iterator catUnique;
    vector<string> extString;
    string extName,catName,coursePathName,catPathName,courseName;
    dbGetUserByName(username,id);
    cout << "user ID is:  " << id << endl;
    dbGetUserCourses(id,courses);
    for (auto courseID: courses) {
        //Create a Course object here
        dbGetCourse(courseID, courseName, coursePathName);
        cout << courseName << " - "<< "ID: " << courseID << endl;
        dbGetUserPreferences(id, courseID, categories);
        catUnique = std::unique(categories.begin(),categories.end());
        categories.resize(std::distance(categories.begin(),catUnique));
        for (auto categoryID: categories) {
            dbGetPreference(categoryID,catName,catPathName);
            cout << "    " << catName << " - "<< "ID: " << categoryID << endl;
            cout << "       Path is: " << catPathName << endl;
            dbGetUserExtensions(id, courseID, categoryID, extensions);
            for (auto extensionID: extensions) {
                dbGetExtensionName(extensionID, extName);
                extString.push_back(extName);
                cout << "           " << extName << " - "<< "ID: " << extensionID << endl;
            }
            //Create CourseCategoryObject here before clearing extString
            extString.clear();
            extensions.clear();
        // Add courseCategoryObject to vector<CourseCategory>
        }
     // Add vector<CourseCategory> to Course object
     // Add course object to vector<Courses>
    categories.clear();
    }
}

void MainWindow::on_pushButton_doneSubscribe_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
  if( currentIndex < ui->stackedWidget->count())
  {
      setupDirectoryExplorer();
      qDebug() << "On doneSubscribe clicked!";

      tellMeCurrentUserGsCISC320Categories();
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
    std::size_t str_password_hash = std::hash<std::string>{}(password);
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
            }
        }
    }
    if (ui->checkBox_cisc124->isChecked()) {
        for (auto courseObj: preDefinedCourses){
            if (courseObj.getCourseName() == "CISC124"){
                courseVector.push_back(Course(courseObj)); //Copy pre-defined course for User specific course.
            }
        }
    }
    if (ui->checkBox_elec451->isChecked()) {
        for (auto courseObj: preDefinedCourses){
            if (courseObj.getCourseName() == "ELEC451") {
                courseVector.push_back(Course(courseObj)); //Copy pre-defined course for User specific course.
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
    tellMeCurrentUserGsCISC320Categories();
    clearCourseTabs();
    repopulateUserSubs();
    editsMade = true;
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
                extensionsBox->addWidget(extension);
            }
            catBox->setLayout(extensionsBox);
            catBox->setCheckable(true); //Category must be checked before extensions can be accessed
            catBox->setChecked(false);
            categoriesBox->addWidget(catBox);
        }
        groupBox->setLayout(categoriesBox);
    }
}


//NOTE: Qt actually saves the state of the checkboxes when you leave the page (its all in the same window)
//This functionality is for the hypothetical case in which a new user visits the page after another has logged out, and
//the previous choices need to be cleared. clearCourseTabs() is called before this function.
// As a side benefit, repopulateUserSubs provides a convenient snapshot of the "before" state of a users selections.
// Because repopulateUserSubs is called as a precursor to changing subscriptions, it is appropriate to carry out both functionalities,
// assigning a heap allocated copy of the users "before" state to beforeSubs, a private MainWindow attribute, so that this state
// persists beyond the life of this function.
void MainWindow::repopulateUserSubs(){

    qDebug() << "At top of repopulateUserSubs!";
    tellMeCurrentUserGsCISC320Categories();

    vector<Course> subscriptions = currentUserG.getSubscribedCourses();
    // make a copy on heap for "before" snapshot
    vector<Course> *heapSubscriptions = new vector<Course>(subscriptions);
    beforeSubs = heapSubscriptions;

    vector<CourseCategory> currentUserGsCISC320Subs = subscriptions[0].getCategories();
    qDebug() << "sizeOf currentUserGsCISC320Subs is: " << currentUserGsCISC320Subs.size();
    qDebug() << "In repopulateUserSubs: \nCISC 320 Categories are: ";
    for (int i = 0; i < currentUserGsCISC320Subs.size(); i++){
        qDebug() << QString::fromStdString(currentUserGsCISC320Subs[i].getCategoryName());
    }


    //For each of the user's subscribed courses
    for (unsigned long i = 0; i < subscriptions.size(); i++){
        //get their CourseCategories
        vector<CourseCategory> cats = subscriptions[i].getCategories();


        /*
        qDebug() << "currentUserG's CourseCategories for: " << QString::fromStdString(subscriptions[i].getCourseName());
        for (unsigned long i = 0; i < cats.size(); i++){
            qDebug() << QString::fromStdString(cats[i].getCategoryName());
        }
        */

        for (unsigned long j = 0; j < ui->tabWidget->count(); j++){
            ui->tabWidget->setCurrentIndex(j);

            //Find the corresponding course tab by matching tab_CourseName to CourseName with substring Course name
            if (ui->tabWidget->currentWidget()->isEnabled()
                    && ui->tabWidget->currentWidget()->objectName().contains(QString::fromStdString(subscriptions[i].getCourseName()), Qt::CaseInsensitive)){

                //qDebug() << "Course Tab is: " << QString::fromStdString(subscriptions[i].getCourseName());

                QGroupBox * topGroupBox = ui->tabWidget->currentWidget()->findChild<QGroupBox*>();
                //get all the category group boxes
                QList<QGroupBox *> catGroupBoxes = topGroupBox->findChildren<QGroupBox *>(QString(), Qt::FindDirectChildrenOnly);


                //qDebug() << "catGroupBoxes size is: " << catGroupBoxes.size();
                //qDebug() << "and that GroupBox is: " << catGroupBoxes[0]->objectName() << " with title: " << catGroupBoxes[0]->title();
                //qDebug() << "catGroupBoxes are: ";
                //for (int i = 0; i < catGroupBoxes.size(); i++){
                //    qDebug() << catGroupBoxes[i]->title();
                //}



                // Go through the users CourseCategories, match them to the category group boxes
                for (unsigned long k = 0; k < cats.size(); k++){
                    //qDebug() << "k:  cat[k] is: " << QString::fromStdString(cats[k].getCategoryName());
                    for (unsigned long l = 0; l < catGroupBoxes.size(); l++){
                        //qDebug() << "catGroupBox size is: " << catGroupBoxes.size();
                        //qDebug() << "      l:  catGroupBox[l] is: " << catGroupBoxes[l]->title();
                        //qDebug() << "          and here, cat[k] is: " << QString::fromStdString(cats[k].getCategoryName());
                        if (QString::fromStdString(cats[k].getCategoryName()) == catGroupBoxes[l]->title()){
                            //if its in the users CourseCategories in the first place, it should be checked
                            catGroupBoxes[l]->setChecked(true);


                            //and that means we have to check its appropriate children extensions
                            //holy crap this is a lot of for-loops, I'm regretting this dynamacism tbh
                            QList<QCheckBox *> extensionBoxes = catGroupBoxes[l]->findChildren<QCheckBox *>(QString(), Qt::FindDirectChildrenOnly);
                            vector<string> userExtensions = cats[k].getExtensionPreferences();

                            for (unsigned long m = 0; m < userExtensions.size(); m++){
                                for (unsigned long n = 0; n < extensionBoxes.size(); n++){
                                    if (QString::fromStdString(userExtensions[m]) == extensionBoxes[n]->objectName()){
                                        extensionBoxes[n]->setChecked(true);
                                        break; //break statements make everything better
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
    vector<Course*> *userCourses = currentUserG.getSubscribedCoursesByPtr();
    vector<Course*>::iterator it;
    qDebug() << "~~~~~INSIDE COURSECATEGORYSAVEBUTTON, for user: " << QString::fromStdString(currentUserG.getUsername()) << ", address of userCourses is: " << &userCourses;
    qDebug() << "~~~~~~ and those subscribed courses are: ";
    for (it = userCourses->begin(); it != userCourses->end(); it++){
        qDebug() << "~~~~~ " << QString::fromStdString((*it)->getCourseName()) << " with memory address: " << *it;
    }


    int userCourseIndex;
    int i = 0;
    for (it = userCourses->begin(); it != userCourses->end(); it++, i++){
        if ((*it)->getCourseName() == thisCourse.toStdString()){
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
            it = userCourses->begin() + userCourseIndex;
            (*it)->removeCategory(categories.at(i)->title().toStdString()); //Note: GroupBoxes use title, not objectName
        }
        else{
            chosenCategories.push_back(categories.at(i));
        }
    }


    //get the (possibly trimmed down) CourseCategories vector for the course
    it = userCourses->begin() + userCourseIndex;
    vector<CourseCategory> thisCourseCategories = (*it)->getCategories();

    // and now set the extension preferences for the categories they do want
    // assumption based on how everythings put together: thisCourseCategories and chosenCategories have same indices
    for (int i = 0; i < chosenCategories.size(); i++){
        vector<string> categoryExtensions;
        //FindChildrenRecursively (I think) since QHBoxLayout, not the checkboxes, is the direct child of each category GroupBox
        QList<QCheckBox *> extensionCheckboxes = chosenCategories.at(i)->findChildren<QCheckBox *>(QString(), Qt::FindChildrenRecursively);
        for (int i = 0; i < extensionCheckboxes.size(); i++){
            if(extensionCheckboxes[i]->isChecked()){
                //checkboxes objectNames were initilialized in displayCategoriesForCourse with CourseCategory::getExtensionPreferences names
                categoryExtensions.push_back(extensionCheckboxes[i]->text().toStdString());
            }
        }
        thisCourseCategories[i].setExtensionPreferences(categoryExtensions);
    }

    it = userCourses->begin() + userCourseIndex;
    vector<CourseCategory> afterCats = (*it)->getCategories();
    qDebug() << "currentUserG's categories after selection are: ";
    for (unsigned long i = 0; i < afterCats.size(); i++){
        qDebug() << QString::fromStdString(afterCats[i].getCategoryName());
    }

    //delete userCourses heap allocation NOTE: Since did not allocate the Courses, just pointers to courses
    // no need to loop through and delete
    delete userCourses;
    userCourses = nullptr;
}

//compareEditedSubscriptions only called if MainWindow attribute beforeSubs != nullptr (there would be nothing to compare).
// beforeSubs is set in repopulateUserSubs().
// This check is made at on_pushButton_editSubs_clicked() with changing editsMade to true
void MainWindow::compareEditedSubscriptions(){



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

            //TODO: use DB for fileExtensions instead of empty vector
            vector<string> fileExtensions = {};
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

void MainWindow::tellMeCurrentUserGsCISC320Categories(){

qDebug() << "INSIDE TELLMECURRENTUSERGSCATEGORIES: \nCategories are: ";
vector<Course> theCors = currentUserG.getSubscribedCourses();
vector<CourseCategory> theCats = theCors[0].getCategories();
qDebug() << "theCats.size is: " << theCats.size();

for (int i = 0; i < theCats.size(); i++){
    qDebug() << QString::fromStdString(theCats[i].getCategoryName());
}

qDebug() << "tellMeCurrentUserGsCISC320Categories finished";
}


