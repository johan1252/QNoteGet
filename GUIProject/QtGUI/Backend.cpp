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
