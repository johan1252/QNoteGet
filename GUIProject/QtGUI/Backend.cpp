#include "Backend.h"

string data;

//Download files for course method, calls getFilesAtUrl() method and DownloadFile() methods.
void Backend::downloadFilesForCourses(User userObject) {
    vector<Course> userCourses = userObject.getSubscribedCourses();
    for (auto course:userCourses){
        vector<CourseCategory> courseCategories = course.getCategories();

        //Create directory for course
        createCourseDirectory(userObject, course);
        qDebug() << "IN downloadFilesForCourses, gets here";
        for (auto category:courseCategories) {
            vector<string> urls = getFilesAtUrl(category);

            //Create sub-directory for course
            createCourseSubDirectory(userObject,course,category);

            for(auto url:urls){
                //cout << url << endl;
                downloadFile(url,userObject,course,category);
            }
        }
    }
}

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

        //Try using current username and password saved.
        //If it fails keep asking user for new username and password.
        if (!username.empty() && !password.empty()){
            data = "";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
            curl_easy_perform(curl);
        }

        while(data.find("401 Authorization Required") != string::npos){
            data = "";

            //(ui->loginLineEdit_credentials->text().isEmpty()) ||(ui->passwordLineEdit_passwordCredentials->text().isEmpty())
            Credentials loginPopup;
            loginPopup.setModal(true);
            loginPopup.exec();

            username = loginPopup.getUsername();
            password = loginPopup.getPassword();

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
            curl_easy_perform(curl);
        }

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
            //cout << line << endl;
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
                if (newline.find(e) != string::npos && newline.find(".html") == string::npos){
                    string file = urlPath + "/" + newline.substr(9,end-begin-10); //start at 9 to get rid of <a href=" ,length is the end - the beginning - 9 - 1 to elimnate the end quote
                    allFiles.push_back(file);
                    //cout << "File: " << file << endl;
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
                    //cout << "Recursive call" << newUrl << endl;
                    urlsVisited.push_back(newUrl);\
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
                if (newr.find(e) != string::npos  && newr.find(".html") == string::npos){
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
                    //cout << "Recursive call" << newUrl  << endl;
                    urlsVisited.push_back(newUrl);\
                    CourseCategory c = CourseCategory("intmUrl", newUrl, fileExtensions);
                    moreFiles = getFilesAtUrl(c);
                    //cout << "End recursive call" << endl;
                    //allFiles.insert(allFiles.end(),moreFiles.begin(), moreFiles.end());
                }
            }
        }
    }
    return allFiles;
}

vector<string> Backend::getExtensionsAtUrl(string categoryUrl){
    data = "";
    string urlPath = categoryUrl;

    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curlAtUrl(curl, urlPath);

    if (urlPath.find("451") != string::npos) {
        //Cheat to make 451 google drive files show as pdf extension
        if (find(fileExt.begin(), fileExt.end(), ".pdf") == fileExt.end()) {
            fileExt.push_back(".pdf");
        }
        vector<string> fileExtensions = fileExt;
        return fileExtensions;
    }

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
    stringstream ss2;

    while (getline (ss, line)){
        //Handle the case where more than one href exists on a line.
        if (line.find("<a href=\"") != string::npos){

            //Find the closing tag for href, and then split into substring.
            int closingTagIndex = line.find("</a>");
            if (closingTagIndex != -1) {
                string restOfLine = line.substr(closingTagIndex+4, line.size());

                //While another href exists in the rest of the line (after cutting off the first href), keep splitting
                //Append the cut off parts to the string stream ss2 to be parsed later.
                while(restOfLine.find("<a href=\"") != string::npos){
                    closingTagIndex = restOfLine.find("</a>");
                    if(closingTagIndex != -1){
                        restOfLine = restOfLine.substr(closingTagIndex+4, restOfLine.size());
                        ss2 << restOfLine.substr(0, closingTagIndex+4) << endl;
                    } else {
                        ss2 << restOfLine << endl;
                        restOfLine = "";
                    }
                }
                //Make the line equal to just the second with the FIRST href. Other hrefs are now part of ss2.
                line = line.substr(0,closingTagIndex);
            }

            //Get the file name + extensions
            boost::regex urlPattern("href=\"(.*\\..{1,4})\"");
            boost::match_results<std::string::const_iterator> testMatches;
            std::string::const_iterator startPos = line.begin();
            if ( regex_search( startPos, line.cend(), testMatches, urlPattern ) ) {
                //cout << testMatches[1] << endl;
                string ext = testMatches[1];

                //Don't accept http/https and htm/html files/pages
                if (ext.find("http") == string::npos && ext.find(".htm") == string::npos){
                    int period = ext.find_last_of('.');
                    ext = ext.substr(period,ext.size());
                    if (find(fileExt.begin(), fileExt.end(), ext) == fileExt.end() && (ext != ".html\"" || ext != ".htm\\")) {
                        fileExt.push_back(ext);
                        //cout << "Extension Added: " << ext << endl;
                    }
                }
            }
        }

        //If an html page, recurse into the pages.
        if (line.find(".html\"") != string::npos){
            unsigned first = line.find('"');
            unsigned last = line.find(".html\"");
            string newUrl = urlPath + "/" + line.substr(first+1, last-first+4);
            if(urlValid(newUrl)){
                //cout << "Recursive call" << newUrl << endl;
                urlsVisited.push_back(newUrl);\
                recursiveExt = getExtensionsAtUrl(newUrl);
                //cout << "End recursive call" << endl;

                //TODO: Ask krysta why this was necessary!
                //fileExt.insert(fileExt.end(),recursiveExt.begin(), recursiveExt.end());
            }
        }
    }

    //Follow the same procedure for the left over href's that were found earlier (more than one on a line)
    while (getline (ss2, line)){
        if (line.find("<a href=\"") != string::npos){
            //Get the file name + extensions
            boost::regex urlPattern("href=\"(.*\\..{1,4})\"");
            boost::match_results<std::string::const_iterator> testMatches;
            std::string::const_iterator startPos = line.begin();
            if ( regex_search( startPos, line.cend(), testMatches, urlPattern ) ) {
                //cout << testMatches[1] << endl;
                string ext = testMatches[1];

                //Don't accept http/https and htm/html files/pages
                if (ext.find("http") == string::npos && ext.find(".htm") == string::npos){
                    int period = ext.find_last_of('.');
                    ext = ext.substr(period,ext.size());
                    if (find(fileExt.begin(), fileExt.end(), ext) == fileExt.end() && (ext != ".html\"" || ext != ".htm\\")) {
                        fileExt.push_back(ext);
                        //cout << "Extension Added: " << ext << endl;
                    }
                }
            }
        }
        //If an html page, recurse into the pages.
        if (line.find(".html\"") != string::npos){
            unsigned first = line.find('"');
            unsigned last = line.find(".html\"");
            string newUrl = urlPath + "/" + line.substr(first+1, last-first+4);
            if(urlValid(newUrl)){
                //cout << "Recursive call" << newUrl << endl;
                urlsVisited.push_back(newUrl);
                recursiveExt = getExtensionsAtUrl(newUrl);
                //cout << "End recursive call" << endl;

                //TODO: Ask krysta why this was necessary!
                //fileExt.insert(fileExt.end(),recursiveExt.begin(), recursiveExt.end());
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
           if(fullUrl.find("/#") == string::npos && fullUrl.find("doc/index.html") == string::npos){
               return true;
           }
       }
    }
    return false;
}

// Note: fileUrl should contain file name with extension.
void Backend::downloadFile(string fileUrl, User userObject, Course courseObject, CourseCategory courseCategoryObject) {
    FILE *fp;
    string pdfFile,id;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    const string dirPathRoot = userObject.getFileDirectory();
    string dirPath = dirPathRoot + "/" + courseObject.getCourseName() + "/" + courseCategoryObject.getCategoryName();

    //Test path
    //dirPath = "/Users/johancornelissen/Desktop/CISC320/Lectures";

    string url = fileUrl;

    //Test Url
    //url = "http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/CISC320_2017_19Oct.pdf";

    if (url.find("drive.google.com") != string::npos){
        //Want in following form
        //curl -L -o ./test.pdf -k "https://drive.google.com/uc?export=download&id=0B949Dch_2XgWUEhtN2FIbFE3TVk"

        //For google drive links, we need to extract ID and use the google download url.
        //Download url "https://drive.google.com/uc?export=download&id="
        boost::regex urlPattern("/d/(.*)/view?");
        boost::match_results<std::string::const_iterator> testMatches;
        std::string::const_iterator startPos = url.begin();
        if ( regex_search( startPos, url.cend(), testMatches, urlPattern ) ) {
            id = testMatches[1];
            url = "https://drive.google.com/uc?export=download&id=" + id;

            //To download google drive links, redirects need to be followed.
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        } else {
            cerr << "ERROR, google drive link failed, could not find URL id." << endl;
            return;
        }

        pdfFile = "/" + id + ".pdf";
    } else {
        //Get the name at end of url. example: "http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/CISC320_2017_19Oct.pdf"
        //For example pdfFile = /CISC320_2017_19Oct.pdf
        pdfFile = url.substr(url.find_last_of("\\/"),url.back());
    }

    dirPath = dirPath + pdfFile;

    if ((fp = std::fopen(dirPath.c_str(),"r"))){
        //If file already exists, then we don't need to re-download.
        fclose(fp);
        return;
    }

    fclose(fp);
    fp = std::fopen(dirPath.c_str(),"wb");

    //Download file contents
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);

    //Uncomment for Debugging
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);

    /* always cleanup */
    fclose(fp);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void Backend::createCourseDirectory(User userObject, Course courseObject) {
    const string dirPathRoot = userObject.getFileDirectory();
    const string dirPath = dirPathRoot + "/" + courseObject.getCourseName();

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
    const string dirPath = dirPathRoot + "/" + courseObject.getCourseName() + "/" + courseCategoryObject.getCategoryName();

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

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = std::fwrite(ptr, size, nmemb, stream);
    return written;
}
