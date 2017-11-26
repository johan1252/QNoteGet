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



size_t writeCallback(char* buf,size_t size, size_t nmemb){
    for (size_t c =0; c<size*nmemb; c++){
        data.push_back(buf[c]);
        //cout<< buf[c];
    }
    return size*nmemb;
}

bool Backend::webpageError(CURL* curl, string line, string url){
    if (line.find("401 Authorization Required") != string::npos){
        data = "";
        string username = "elec451";
        string password = "cmos2017";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_perform(curl);

        return true;
    }
    if (line.find("301 Moved Permanently") != string::npos ){
        data="";
        auto at = find(urlsVisited.begin(), urlsVisited.end(), url);
        if (at != urlsVisited.end()){
            urlsVisited.erase(at);
        }
        curlAtUrl(curl, url);
        return true;
    }
    return false;

}

void Backend::curlAtUrl(CURL* curl, string url){

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_perform(curl);
}

//TODO getFilesAtUrl, can use CourseScraper methods as example but use better structure.

vector<string> Backend::getFilesAtUrl(CourseCategory categoryObject){

    data = "";
    string urlPath = categoryObject.getUrlPath(); //a set url from the database

    vector<string> fileExtensions = categoryObject.getExtensionPreferences();

    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curlAtUrl(curl, urlPath);

    stringstream ss_init(data);
    string line;
    while(getline(ss_init, line)){
        if (webpageError(curl,line,urlPath)) //error handler
        {
            break;
        }
    }

    stringstream ss(data);
    vector<string> allFiles, moreFiles;


    if (find(urlsVisited.begin(), urlsVisited.end(), urlPath) == urlsVisited.end()){ //puts the root url
        urlsVisited.push_back(urlPath);
    }

    urlPath.erase(urlPath.find_last_of("/"));
    vector<string> alltherest;
    while (getline(ss, line))  // for the initial scrape from the website
    {
        string lowerLine = line;
        std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);
        int begin = lowerLine.find("<a href=\"");
        if (begin != -1){
            cout << line << endl;
            int end = begin+9;
            while (line[end] != '"'){
                end++;
            }
            end++; //advance one past the end quote

            string newline = line.substr(begin, end-begin);
            string therest = line.substr(end, line.length()-end);
            alltherest.push_back(therest);
            //cout << "Line: " << newline << endl;
            for (auto e : fileExtensions){
                //cout << e << endl;
                if (newline.find(e) != string::npos){
                    string file = urlPath + "/" + newline.substr(9,end-begin-10); //start at 9 to get rid of <a href=" ,length is the end - the beginning - 9 - 1 to elimnate the end quote
                    allFiles.push_back(file);
                    cout << "File: " << file << endl;
                    break;
                 }
            }

            if (line.find("drive.google.com") != string::npos){
                string file = line.substr(begin+9,end-begin-10);
                allFiles.push_back(file);
            }
            if (line.find(".html\"") != string::npos){
                unsigned first = line.find('"');
                unsigned last = line.find(".html\"");
                string newUrl = urlPath + "/" + line.substr(first+1, last-first+4);
                if(urlValid(newUrl)){
                    cout << "Recursive call" << newUrl << endl;
                    urlsVisited.push_back(newUrl);
                    CourseCategory c = CourseCategory("intmUrl", newUrl, fileExtensions);
                    moreFiles = getFilesAtUrl(c);
                    //cout << "End recursive call" << endl;
                    //allFiles.insert(allFiles.end(),moreFiles.begin(), moreFiles.end());
                }
            }

        }
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    for (auto r : alltherest) //this goes through all the remainder substrings the files were taken from
    {
        string lowerLine = r;
        std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);
        int begin = lowerLine.find("<a href=\"");
        if (begin != -1){
            int end = begin+9;
            while (r[end] != '"'){
                end++;
            }
            end++; //advance to include the end quote

            string newr = r.substr(begin, end-begin);
            string therest = r.substr(end, r.length()-end);
            alltherest.push_back(therest);
            //cout << "r: " << newr << endl;
            for (auto e : fileExtensions){
                if (newr.find(e) != string::npos){
                    string file = urlPath + "/" + newr.substr(9,end-begin-10);
                    allFiles.push_back(file);
                    //cout << "File: " << file << endl;
                    break;

                }
            }

            if (line.find("drive.google.com") != string::npos){
                string file = r.substr(begin+9,end-begin-10);
                allFiles.push_back(file);
            }
            if (r.find(".html\"") != string::npos){
                unsigned first = r.find('"');
                unsigned last = r.find(".html\"");
                string newUrl = urlPath + "/" + r.substr(first+1, last-first+4);
                if(urlValid(newUrl)){
                    cout << "Recursive call" << newUrl  << endl;
                    urlsVisited.push_back(newUrl);\
                    CourseCategory c = CourseCategory("intmUrl", newUrl, fileExtensions);
                    moreFiles = getFilesAtUrl(c);
                    //cout << "End recursive call" << endl;
                    allFiles.insert(allFiles.end(),moreFiles.begin(), moreFiles.end());
                }
            }
        }
    }
    return allFiles;
}

vector<string> Backend::getExtensionsAtUrl(CourseCategory categoryObject){

    data = "";
    string urlPath = categoryObject.getUrlPath();

    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curlAtUrl(curl, urlPath);

    stringstream ss_init(data);
    string line;
    while(getline(ss_init, line)){
        if (webpageError(curl,line,urlPath)) //error handler
        {
            break;
        }
    }

    urlPath.erase(urlPath.find_last_of("/"));
    vector<string> recursiveExt;
    stringstream ss(data);

    while (getline (ss, line)){
        if (line.find("<a href=\"") != string::npos){
            int end1 = line.find_last_of('.');
            int end2 = end1;
            while (line[end2] != '"'){
                end2++;
            }
            end2++; //to advance past the endquote (we want to include it)
            if ((end2 - end1) <= 6) {
                string ext = line.substr(end1, end2-end1);
                if (find(fileExt.begin(), fileExt.end(), ext) == fileExt.end() && (ext != ".html\"" || ext != ".htm\\")) {
                    fileExt.push_back(ext);
                    //cout << ext << endl;
                }
            }
        }
        if (line.find(".html\"") != string::npos){
            unsigned first = line.find('"');
            unsigned last = line.find(".html\"");
            string newUrl = urlPath + "/" + line.substr(first+1, last-first+4);
            if(urlValid(newUrl)){
                //cout << "Recursive call" << endl;
                urlsVisited.push_back(newUrl);\
                CourseCategory c = CourseCategory("intmUrl", newUrl, fileExt);
                recursiveExt = getExtensionsAtUrl(c);
                //cout << "End recursive call" << endl;
                fileExt.insert(fileExt.end(),recursiveExt.begin(), recursiveExt.end());
            }
        }
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    vector<string> fileExtensions = fileExt;
    return fileExtensions;
}

bool Backend::urlValid(string newUrl){
    if (find(urlsVisited.begin(), urlsVisited.end(), newUrl) == urlsVisited.end()){
       string fullUrl = newUrl + '/';
       if (find(urlsVisited.begin(), urlsVisited.end(), fullUrl) == urlsVisited.end()){
           if(fullUrl.find("/#") == string::npos){
               return true;
           }
       }
    }
    return false;
}

//TODO downloadFilesInUrl, can use CourseScraper methods as example but use better structure.
/*void Backend::downloadFilesInUrl(CourseCategory categoryObject){
     vector<string> fileUrls = getFilesAtUrl(categoryObject);
    for (auto f : fileUrls){
       // downloadFile(f, currentUserG,?, categoryObject); //some course object,??
    }
}*/

// Note: fileUrl should contain file name with extension.
void Backend::downloadFile(string fileUrl, User userObject, Course courseObject, CourseCategory courseCategoryObject) {
    const string dirPathRoot = userObject.getFileDirectory();
    string dirPath = dirPathRoot + "/" + courseObject.getRootUrl() + "/" + courseCategoryObject.getCategoryName();
    //string dirPath = dirPathRoot + "/" + courseObject.getCourseName() + "/" + courseCategoryObject.getCategoryName();
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
