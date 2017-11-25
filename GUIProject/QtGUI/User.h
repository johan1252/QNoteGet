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
        User(int userId, string uName, int pw, string directory, int interval, vector<Course> userCourses);
        string getUsername();
        int getPassword();
        int getUserId();
        string getFileDirectory();
        int getUpdateInterval();
        vector<Course>& getSubscribedCourses();
        vector<Course *> getSubscribedCoursesByPtr();
        void setPassword(int pw);
        void setUpdateInterval(int interval);
        void setCourses(vector<Course> userCourses);
        // comment so bitbucket reflects changes, delete afterwards

private:
        int userId;
        string username;
        int passwordHash;
        string fileDirectory;
        int updateInterval;
        vector<Course> subscribedCourses;
        vector<Course*> ptrToSubscribedCourses;

};
