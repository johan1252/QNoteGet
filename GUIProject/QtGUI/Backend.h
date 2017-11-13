#pragma once
#include "CourseCategory.h"
#include "Course.h"
#include <string>
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
    void downloadFilesInUrl(CourseCategory categoryObject);

};

