#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

#include "CourseCategory.h"

CourseCategory::CourseCategory(string categoryName, string urlPath, vector<string> fileExtensions) : categoryName(categoryName),urlPath(urlPath),fileExtensions(fileExtensions)  {}

vector<string> CourseCategory::getExtensionPreferences() {
    return fileExtensions;
}

string CourseCategory::getCategoryName() {
    return categoryName;
}

string CourseCategory::getUrlPath() {
    return urlPath;
}

void CourseCategory::setExtensionPreferences(vector<string> extensions) {
    fileExtensions = extensions;
}
