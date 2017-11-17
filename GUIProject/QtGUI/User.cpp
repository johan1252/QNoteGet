#include "User.h"

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

vector<Course> User::getSubscribedCourses(){
    return subscribedCourses;
}

void User::setCourses(vector<Course> userCourses){
    subscribedCourses = userCourses;
}
