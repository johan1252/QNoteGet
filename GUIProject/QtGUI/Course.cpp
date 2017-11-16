#include "Course.h"

Course::Course(string courseName, string rootUrl,vector<CourseCategory> categories) : courseName(courseName),rootUrl(rootUrl),categories(categories) {}

string Course::getCourseName() {
    return courseName;
}

vector<CourseCategory> Course::getCategories() {
    return categories;
}

string Course::getRootUrl() {
    return rootUrl;
}

void Course::setRootUrl(string path){
    rootUrl = path;
    return;
}

void Course::setCategories(vector<CourseCategory> newCategories) {
    categories=newCategories;
}
void Course::addCategory(CourseCategory category) {
    categories.push_back(category);
}
void Course::removeCategory(CourseCategory category) {
    //TODO: Verify that this remove from vector by value actually works
    //categories.erase(std::remove(categories.begin(), categories.end(), category), categories.end());
}
