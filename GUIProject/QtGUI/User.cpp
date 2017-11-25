#include "User.h"
#include <QDebug>

User::User(int userId, string uName,int pw,string directory,int interval, vector<Course> userCourses):userId(userId),username(uName),passwordHash(pw),fileDirectory(directory),updateInterval(interval),subscribedCourses(userCourses) {

}

string User::getUsername(){
    return username;
}

int User::getPassword(){
    return passwordHash;
}

int User::getUserId(){
    return userId;
}

string User::getFileDirectory(){
    return fileDirectory;
}
int User::getUpdateInterval() {
    return updateInterval;
}

void User::setPassword(int pw){
    passwordHash = pw;
}

void User::setUpdateInterval(int interval){
    updateInterval = interval;
}

vector<Course>& User::getSubscribedCourses(){
    //qDebug() << "******INSIDE USER OBJECT getSubscribedCourses for " << QString::fromStdString(username) << ", address of subscribed courses: " << &subscribedCourses;
    //qDebug() << "****** and those courses are: ";
    /*for (int i = 0; i < subscribedCourses.size(); i++){
        qDebug() << "*********** " << QString::fromStdString(subscribedCourses[i].getCourseName()) << " and whose address is: " << &subscribedCourses[i];
    }
    */
    return subscribedCourses;
}

vector<Course*> User::getSubscribedCoursesByPtr(){
    ptrToSubscribedCourses.reserve(subscribedCourses.size());
    for (int i = 0; i < subscribedCourses.size(); i++){
        Course *coursePtr = &subscribedCourses[i];
        ptrToSubscribedCourses.push_back(coursePtr);
    }
    return ptrToSubscribedCourses;
}


void User::setCourses(vector<Course> userCourses){
    subscribedCourses = userCourses;
}
// comment so bitbucket reflects changes, delete afterwards
