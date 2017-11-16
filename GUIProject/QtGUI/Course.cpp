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

// Marshall - I added this so I could remove a category in Mainwindow::courseCategorySaveButtonClicked using
// the string name of the category,vs. instantiating a CourseCategory instance just to remove it
void Course::removeCategory(string category){
    for (int i = 0; i < categories.size(); i++){
        if (categories[i].getCategoryName() == category){
            categories.erase(categories.begin() + i);
            break;
        }
    }
}
