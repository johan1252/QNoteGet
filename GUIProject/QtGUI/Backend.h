#pragma once
#include "CourseCategory.h"
#include "Course.h"
#include "User.h"
#include <string.h>
#include <boost/filesystem.hpp>
#include <vector>

class Backend;

using namespace std;

class Backend {
public:
    static CourseCategory updateCategoryExtension(CourseCategory categoryObject);
    static void downloadFilesForCourse(Course courseObject);
    static void daemonUpdateTask(int updateInterval);

private:
    vector<string> getFilesAtUrl(CourseCategory categoryObject);
    static void downloadFilesInUrl(CourseCategory categoryObject);
    static void createCourseDirectory(User userObject, Course courseObject);
    static void createCourseSubDirectory(User userObject, Course courseObject, CourseCategory courseCategoryObject);

};

