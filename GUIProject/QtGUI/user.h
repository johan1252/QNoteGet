#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "Course.h"

class User;

using namespace std;

class User {
public:
        User(string uName,int pw,string directory,int interval,vector<Course> userCourses);
        string getUsername();
        int getPassword();
        string getFileDirectory();
        int getUpdateInterval();
        vector<Course> getSubscribedCourses();
        void setPassword(int pw);
        void setUpdateInterval(int interval);
        void setCourses(vector<Course> userCourses);

private:
        string username;
        int passwordHash;
        string fileDirectory;
        int updateInterval;
        vector<Course> subscribedCourses;
};
