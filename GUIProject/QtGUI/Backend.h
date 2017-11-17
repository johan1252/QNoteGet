#pragma once
#include "CourseCategory.h"
#include "Course.h"
#include <string.h>
#include <vector>
#include <curl/curl.h>
#include <boost/filesystem.hpp>
#include <boost/regex.h>

class Backend;

using namespace std;

class Backend {
public:
    static CourseCategory updateCategoryExtension(CourseCategory categoryObject);
    static void downloadFilesForCourse(Course courseObject);
    static void daemonUpdateTask(int updateInterval);
    vector<string> getFilesAtUrl(CourseCategory categoryObject);
    vector<string> urlsVisited;
private:
    bool urlValid(string newUrl);
    void downloadFilesInUrl(CourseCategory categoryObject);
};

size_t writeCallback(char* buf,size_t size, size_t nmemb, void* up);
bool webpageError(CURL* curl, string line);
void curlAtUrl(CURL* curl, string url);
extern string data;


