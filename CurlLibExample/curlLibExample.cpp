/*
 * curlLibExample.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Team Simcoe
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <curl/curl.h> //your directory may be different
#include <boost/filesystem.hpp>

using namespace std;

string data; //will hold the url's contents

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main()
{
    string userInput;
	char url [100];
    cout << "Please enter URL for course notes: ";
    cin >> userInput;
    strcpy(url,userInput.c_str());

    // Remove everything after last slash.
    userInput.erase(userInput.rfind('/'));
    const char* initialWebpage = userInput.c_str();

	CURL* curl; //our curl object

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    //curl_easy_setopt(curl, CURLOPT_URL, "http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/LectureNotes.html");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

    curl_easy_perform(curl);

    stringstream ss(data);

    string line;
    vector<string> pdfFilesVector;
    const char* lastPdfName;

    while (getline(ss, line)) {
    		if (line.find("pdf") != -1){
    			//cout << line << endl;
    			unsigned first = line.find('"');
    			unsigned last = line.find(".pdf\"");
    			string pdfFile = line.substr(first+1,last-first+3);
    			pdfFilesVector.push_back(pdfFile);
    			lastPdfName = pdfFile.c_str();
    		}
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

	const char dir_path[] = "lectures";
	boost::filesystem::path dir(dir_path);
	if(boost::filesystem::create_directory(dir)) {
		std::cout << "Success" << "\n";
	}


    //http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/CISC320_2017_19Oct.pdf
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {

    		for(auto i : pdfFilesVector) {
    			cout << i << " File Saved." << endl;
    			const char* pdfPath = i.c_str();
			char url[100];   // array to hold the result.
			strcpy(url,initialWebpage); // copy string one into the result.
			strcat(url,pdfPath); // append string two to the result.

		    char path[100];   // array to hold the result.
		    char* directory = "lectures/";
		    strcpy(path,directory); // copy string one into the result.
		    strcat(path,pdfPath); // append string two to the result.

			fp = fopen(path,"wb");
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			/* always cleanup */

			fclose(fp);

    		}
    }
    curl_easy_cleanup(curl);
    //cout << endl << data << endl;
    //cin.get();

    return 0;
}



