#pragma once
#include "CourseCategory.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Course;

using namespace std;

class Course {
public:
        Course(string courseName, string rootUrl,vector<CourseCategory> categories);

        string getCourseName();
        vector<CourseCategory> getCategories();
        string getRootUrl();
        void setRootUrl(string path);
        void setCategories(vector<CourseCategory> category);
        void addCategory(CourseCategory category);
        void removeCategory(CourseCategory category);

private:
        string courseName;
        string rootUrl;
        vector<CourseCategory> categories;
};
