#include "Backend.h"

string data;
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



size_t writeCallback(char* buf,size_t size, size_t nmemb, void* up){
    for (int c =0; c<size*nmemb; c++){
        data.push_back(buf[c]);
        //cout<< buf[c];
    }
    return size*nmemb;
}

bool webpageError(CURL *curl, string line){
    if (line.find("401 Authorization Required") != -1){
        //TODO Try Website with Authorization
        return true;
    }
    else if (line.find("301 Moved Permanently") != -1 ){
        data="";

        return true;
    }
    else {
        return false;
    }
}

void curlAtUrl(CURL* curl, string url){

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

    curl_easy_perform(curl);
}

//TODO getFilesAtUrl, can use CourseScraper methods as example but use better structure.

vector<string> Backend::getFilesAtUrl(CourseCategory categoryObject){

    data = ""; //do I need a copy constructor? overload the assignment operator?
    string urlPath = categoryObject.getUrlPath(); //a set url from the database
    char url [100];
    strcpy(url, urlPath.c_str());
    //vector<string> fileExtensions = categoryObject.getExtensionPreferences();
    vector<string> fileExtensions;
    fileExtensions.push_back(".pdf");
    fileExtensions.push_back(".cpp");
    fileExtensions.push_back(".zip");
    fileExtensions.push_back(".txt");
    fileExtensions.push_back(".pptx");
    fileExtensions.push_back(".h");

    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_perform(curl);

    stringstream ss_init(data);
    string line;
    while(getline(ss_init, line)){
        if (webpageError(curl,line)){
            break;
        }
    }

    stringstream ss(data);
    vector<string> allFiles, moreFiles;


    if (find(urlsVisited.begin(), urlsVisited.end(), url) == urlsVisited.end()){ //puts the root url
        urlsVisited.push_back(url);
    }

    while (getline(ss, line)){
        if (line.find(".html\"") != -1){
            unsigned first = line.find('"');
            unsigned last = line.find(".html\"");
            string newUrl(url);
            newUrl.erase(newUrl.find_last_of("/"));
            newUrl += "/" + line.substr(first+1, last-first+4);
            if(urlValid(newUrl)){
                urlsVisited.push_back(newUrl);
                cout << url << endl;
                cout << newUrl << endl;
                //TODO call getFilesAtUrl with new URL
                CourseCategory c = CourseCategory("intmUrl", newUrl, fileExtensions);
                moreFiles = getFilesAtUrl(c);
                allFiles.insert(allFiles.end(),moreFiles.begin(), moreFiles.end());
            }
        }
        for (int i = 0; i < (int)fileExtensions.size(); i++){
            if (line.find(fileExtensions[i]+'"') != -1){
                unsigned first = line.find('"');
                unsigned last = line.find(fileExtensions[i]+'"');
                string file = line.substr(first+1, last-first+(fileExtensions[i].length())-1);
                allFiles.push_back(file);
                cout << file << endl;
            }
        }

    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    for (auto i : allFiles){
        cout << i << endl;
    }

    return allFiles;
}

bool Backend::urlValid(string newUrl){
    if (find(urlsVisited.begin(), urlsVisited.end(), newUrl) == urlsVisited.end()){
       string fullUrl = newUrl + '/';
       if (find(urlsVisited.begin(), urlsVisited.end(), fullUrl) == urlsVisited.end()){
           if(fullUrl.find("/#") == -1){
               return true;
           }
       }
    }
    return false;
}

//TODO downloadFilesInUrl, can use CourseScraper methods as example but use better structure.
//void Backend::downloadFilesInUrl(CourseCategory categoryObject);
