#include "Backend.h"

//TODO updateCategoryExtension method
//CourseCategory Backend::updateCategoryExtension(CourseCategory categoryObject);

//TODO download files for course method, should call getFilesAtUrl() method and DownloadFilesInUrl() method.
//void Backend::downloadFilesForCourse(Course courseObject);

/*
 * Daemon (not actually daemon task since that requires lot of OS work
 * but behaves like one using a for-loop), this function should only be called once the user
 * is complete with the GUI setup and wants to have the application just work in the background.
 * Inputs: updateInterval in hours (amount of time between updates)
 * Will call the appropriate file update functions when the time interval + start time matches.
 */
void Backend::daemonUpdateTask(int updateInterval) {
    time_t newTime;
    time_t startTime = time(0);
    size_t minutes = updateInterval*60;

    while(true) {
        newTime = startTime + (60 * minutes);
        struct tm tNewTime;
        memset(&tNewTime, '\0', sizeof(struct tm));
        localtime_r(&newTime, &tNewTime);

        if (time(0) == newTime) {
            cout << "Time Matched! Run daemon download update tasks!" << endl ;
            //TODO: Call appropriate download tasks

            //Reset the start time to current time so that next interval occurs in current time + updateinterval(hrs)
            startTime = time(0);
        }
   }
}

//TODO getFilesAtUrl, can use CourseScraper methods as example but use better structure.
//vector<string> Backend::getFilesAtUrl(CourseCategory categoryObject);

//TODO downloadFilesInUrl, can use CourseScraper methods as example but use better structure.
//void Backend::downloadFilesInUrl(CourseCategory categoryObject);

// Note: fileUrl should contain file name with extension.
void Backend::downloadFile(string fileUrl, User userObject, Course courseObject, CourseCategory courseCategoryObject) {
    const string dirPathRoot = userObject.getFileDirectory();
    string dirPath = dirPathRoot + "/" + courseObject.getRootUrl() + "/" + courseCategoryObject.getCategoryName();

    //Test path
    //string dirPath = "/Users/johancornelissen/Desktop/CISC320/Lectures";

    string url = fileUrl;

    //Test Url
    //url = "http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/CISC320_2017_19Oct.pdf";

    //Find file name example, "CISC320_Lecture3.pdf"
    string pdfFile = url.substr(url.find_last_of("\\/"),url.back());
    dirPath = dirPath + pdfFile;

    FILE *fp;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    //Open file for writing in user's computer
    fp = std::fopen(dirPath.c_str(),"wb");
    //cout << "Opening file: " << dirPath << endl;

    //Download file contents
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Backend::write_data);

    //Uncomment for Debugging
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /* always cleanup */
    fclose(fp);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void Backend::createCourseDirectory(User userObject, Course courseObject) {
    const string dirPathRoot = userObject.getFileDirectory();
    const string dirPath = dirPathRoot + "/" + courseObject.getRootUrl();

    //Test path
    //const string dirPath = "/Users/johancornelissen/Desktop/CISC320";

    boost::filesystem::path dir(dirPath);

    //If directory does not already exist, create it.
    if(!boost::filesystem::exists(dir)) {
        if(!boost::filesystem::create_directory(dir)) {
            cerr << "ERROR: Directory " << dir << " could not be created!" << "\n";
        }
    }
}

void Backend::createCourseSubDirectory(User userObject, Course courseObject, CourseCategory courseCategoryObject) {
    const string dirPathRoot = userObject.getFileDirectory();
    const string dirPath = dirPathRoot + "/" + courseObject.getRootUrl() + "/" + courseCategoryObject.getCategoryName();

    //Test path
    //const string dirPath = "/Users/johancornelissen/Desktop/CISC320/Lectures";

    boost::filesystem::path dir(dirPath);

    //If directory does not already exist, create it.
    if(!boost::filesystem::exists(dir)) {
        if(!boost::filesystem::create_directory(dir)) {
            cerr << "ERROR: Directory " << dir << " could not be created!" << "\n";
        }
    }
}

size_t Backend::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = std::fwrite(ptr, size, nmemb, stream);
    return written;
}
