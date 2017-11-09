#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

#include "user.h"

User::User(string uName,int pw,string directory,int interval):username(uName),passwordHash(pw),fileDirectory(directory),updateInterval(interval) {

}

string User::getUsername(){
    return username;
}

int User::getPassword(){
    return passwordHash;
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
