#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

#include "Course.h"

Course::Course(string courseName, string rootUrl) : courseName(courseName),rootUrl(rootUrl) {}

string Course::getCourseName() {
    return courseName;
}

//vector<CourseCategory> Course::getCategories();

string Course::getRootUrl() {
    return rootUrl;
}

void Course::setRootUrl(string path){
    rootUrl = path;
    return;
}
