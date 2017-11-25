#pragma once
#include "CourseCategory.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class Course;

using namespace std;

class Course {
public:
        //Constructor
        Course(string courseName, string rootUrl,vector<CourseCategory> categories);

        //Copy constructor
        Course(const Course& preDefinedCourse);

        string getCourseName() const;
        vector<CourseCategory> getCategories() const;
        string getRootUrl() const;
        void setRootUrl(string path);
        void setCategories(vector<CourseCategory> category);
        void addCategory(CourseCategory category);
        void removeCategory(string category);
        // comment so bitbucket reflects changes, delete afterwards

private:
        string courseName;
        string rootUrl;
        vector<CourseCategory> categories;
};
