#pragma once
#include "CourseCategory.h"
#include "Course.h"
#include "User.h"
#include <string.h>
#include <vector>
#include <curl/curl.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <QDebug>
#include "Credentials.h"

class Backend;

using namespace std;

class Backend {
public:
    static CourseCategory updateCategoryExtension(CourseCategory categoryObject);
    void downloadFilesForCourses(User userObject);
    static void daemonUpdateTask(int updateInterval);

    vector<string> getExtensionsAtUrl(string categoryUrl);
    vector<string> urlsVisited;
    vector<string> getFilesAtUrl(CourseCategory categoryObject);
    vector<string> fileExt;
private:
    bool urlValid(string newUrl);
    void downloadFilesInUrl(CourseCategory categoryObject);
    void createCourseDirectory(User userObject, Course courseObject);
    void createCourseSubDirectory(User userObject, Course courseObject, CourseCategory courseCategoryObject);
    void downloadFile(string fileUrl, User userObject, Course courseObject, CourseCategory courseCategoryObject);
    bool webpageError(CURL* curl, string line, string url);
    void curlAtUrl(CURL* curl, string url);

    string username;
    string password;
};

size_t writeCallback(char* buf,size_t size, size_t nmemb);
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
extern string data;


