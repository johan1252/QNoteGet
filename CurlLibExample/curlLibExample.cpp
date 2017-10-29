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
#include <boost/regex.hpp>

using namespace std;

string data; //will hold the url's contents

vector<string> urlVisitedVector;

string username;

string password;

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
        //cout << buf[c];
    }
    return size*nmemb; //tell curl how many bytes we handled
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void get320LectureNotes() {
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
			    const char* directory = "lectures/";
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

	    return;
}

void listPdfFilesInPage (string urlIn) {
		data = "";
		char url [100];
		strcpy(url, urlIn.c_str());
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
	    		if (line.find(".pdf") != -1){
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

	    for (auto i: pdfFilesVector)
	      std::cout << i << endl;

	    return;
}

void tryWebsiteWithAuthentication(char* urlInput) {

	char url[100];
	strcpy(url,urlInput);
	strcat(url,"/");

	CURL* curl; //our curl object

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	bool authenticated = false;
	bool attemptFailed = false;
	while (!authenticated) {
		data = "";

		if ( (username == "" || password == "") || attemptFailed ) {
				cout << "PASSWORD REQUIRED FROM USER for " << url << endl;
				cout << "Provide Username: ";
				cin >> username;

				cout << "Provide Password: ";
				cin >> password;

				attemptFailed = false;
		} //If we still have a password and username remembered, try using it.

		//cout <<"URL IN AUTHENTICATION FUNCTION " << url << endl;

		curl_easy_setopt(curl, CURLOPT_URL, url);

		// Using authentication
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
		curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
		curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

		curl_easy_perform(curl);

		stringstream ss(data);
		string line;

		while (getline(ss, line)) {
				//cout << line << endl;
				if (line.find("401 Authorization Required") != -1) {
					attemptFailed = true;
					ss.clear();
					ss.str("");
					break;
				}
		}
		if (!attemptFailed) {
			authenticated = true;
		}

	}

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return;

}

void listAllFilesFoundInURL(string userInput) {
		// IMPORTANT, DATA MUST BE CLEARED FIRST
		data = "";

		char url [100];
	    strcpy(url,userInput.c_str());

	    //cout << "USER INPUT: " << userInput << endl;
	    //cout << "URL: " << url << endl;

	    // Remove everything after last slash.
	    userInput.erase(userInput.rfind('/'));
	    const char* initialWebpage = userInput.c_str();

	    // Store root page url, example from http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/LectureNotes.html store
	    // just http://research.cs.queensu.ca
	    string hostName;
	    	boost::regex urlPattern("^(?:http[s]?:\\/\\/)(.*)\\.(?:ca|com|net|org|edu|me)\\/");
	    	boost::match_results<std::string::const_iterator> testMatches;
	    	std::string::const_iterator startPos = userInput.begin();
	    	if ( regex_search( startPos, userInput.cend(), testMatches, urlPattern ) ) {
	    		hostName = testMatches[1];
	    	}


		CURL* curl; //our curl object

	    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	    curl = curl_easy_init();

	    //curl_easy_setopt(curl, CURLOPT_URL, "http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/LectureNotes.html");
	    curl_easy_setopt(curl, CURLOPT_URL, url);
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

	    curl_easy_perform(curl);

	    stringstream ss_initial(data);

	    string line = "";
	    vector<string> htmlPagesVector;

	    //320 ROOT Page: http://research.cs.queensu.ca/home/cisc320/

	    /*
	    cout << "URLs VISITED SO FAR " << endl;
	    for (auto i: urlVisitedVector)
	    {
	    		cout << i << endl;
	    }
	    */

	    while (getline(ss_initial, line)) {
	    		if (line.find("401 Authorization Required") != -1) {
	    			//cout << "ATTENTION: " << line << endl;

	    			tryWebsiteWithAuthentication(url);

	    			break;
	    		}
	    }

	    // Reset string stream for second loop.
		stringstream ss(data);

		// Add base URL to list if not already in it.
		if (find(begin(urlVisitedVector), end(urlVisitedVector), url) == end(urlVisitedVector)) {
			urlVisitedVector.push_back(url);
		}

	    while (getline(ss, line)) {
	    		// DEBUG: To print out html page
	    		//cout << line << endl;

	    		string lineLowerCase = line;
	    		transform(lineLowerCase.begin(), lineLowerCase.end(), lineLowerCase.begin(), ::tolower);
	    		// If in format http://research.cs.queensu.ca/home/cisc320/assignments.html
	    		if (lineLowerCase.find("href=") != -1 && lineLowerCase.find(".html\"") != -1){
	    			if (!((lineLowerCase.find("http://") != -1 || lineLowerCase.find("https://") != -1) && !(lineLowerCase.find(hostName) != -1))) {
	    					// If it is a website address that is not to the internal host.
	    					// Example if ref is to anything research.cs.queensu then that is fine but not to googleTutorials.com/ etc.

						//cout << "DEBUG: Found Line " << line << endl;

						unsigned first = lineLowerCase.find('"');
						unsigned last = lineLowerCase.find(".html\"");
						string htmlPage = line.substr(first+1,last-first+4);
						string fullUrl = userInput + "/" + htmlPage;

						// check to ensure url has not already been seen.
						if (find(begin(urlVisitedVector), end(urlVisitedVector), fullUrl) == end(urlVisitedVector)) {
							// Also check that equivalent url (with and extra slash) has not already been seen.
							string equivfullUrl = fullUrl + "/";
							if (find(begin(urlVisitedVector), end(urlVisitedVector), equivfullUrl) == end(urlVisitedVector)) {
								htmlPagesVector.push_back(fullUrl);
								urlVisitedVector.push_back(fullUrl);
								//cout << fullUrl << endl;
							}
						}
	    			}
	    		} else if (lineLowerCase.find("href=") != -1) {
	    			if (!((lineLowerCase.find("http://") != -1 || lineLowerCase.find("https://") != -1) && !(lineLowerCase.find(hostName) != -1))) {
						//If in format http://post.queensu.ca/~nm7/elec451/protected

	    					// absolute path
	    					if (line.find("http") != -1) {
	    						//cout << "Absolute Path" << endl;
	    						//cout << line << endl;

							unsigned first = lineLowerCase.find("href=\"");
							unsigned last = lineLowerCase.find("\">");
							string fullUrl = line.substr(first+6,last-first-6);

							// check to ensure url has not already been seen.
							if (find(begin(urlVisitedVector), end(urlVisitedVector), fullUrl) == end(urlVisitedVector)) {
								// Also check that equivalent url (with and extra slash) has not already been seen.
								string equivfullUrl = fullUrl + "/";
								if (find(begin(urlVisitedVector), end(urlVisitedVector), equivfullUrl) == end(urlVisitedVector)) {
									htmlPagesVector.push_back(fullUrl);
									urlVisitedVector.push_back(fullUrl);
									//cout << fullUrl << endl;
								}
							}
	    					} else {
	    						// Relative Path
	    						//cout << "Relative Path" << endl;
	    						//cout << line << endl;

							unsigned first = lineLowerCase.find("href=\"");
							unsigned last = lineLowerCase.find("\">");
							if (first != -1 && last != -1) {
								string htmlPage = line.substr(first+6,last-first-6);

								if (line.find(".") != -1 && !(line.find("html") != -1)){
									continue;
								}

								string fullUrl = userInput + "/" + htmlPage;

								// check to ensure url has not already been seen.
								if (find(begin(urlVisitedVector), end(urlVisitedVector), fullUrl) == end(urlVisitedVector)) {
									// Also check that equivalent url (with and extra slash) has not already been seen.
									string equivfullUrl = fullUrl + "/";
									if (find(begin(urlVisitedVector), end(urlVisitedVector), equivfullUrl) == end(urlVisitedVector)) {
										htmlPagesVector.push_back(fullUrl);
										urlVisitedVector.push_back(fullUrl);
										//cout << fullUrl << endl;
									}
								}
							}
	    					}
	    			}
	    		}
	    }

	    curl_easy_cleanup(curl);
	    curl_global_cleanup();

	    /*
	    cout << "DEBUG: FOUND THE FOLLOWING URLS IN PAGE " << url << endl;
	    for (auto i: htmlPagesVector)
		{
				cout << i << endl;
		}
		*/

	    for (auto i: htmlPagesVector)
	    {
	    		//cout << "Calling API again using " << i << endl;
	    		listAllFilesFoundInURL(i);
	    }

	    //cout << "Pdf Files Found:" << endl;
	    //for (auto i: htmlPagesVector)
	    	//	listPdfFilesInPage(i);
}

int main()
{
	//get320LectureNotes();

	string userInput;
    cout << "Please enter root course URL: ";
    //cin >> userInput;
    userInput = "http://research.cs.queensu.ca/home/cisc320/";
    //userInput = "http://post.queensu.ca/~nm7/ELEC451/";

	listAllFilesFoundInURL(userInput);
    cout << endl << "Websites Found:" << endl;
    for (auto i: urlVisitedVector)
    {
    		cout << i << endl;
    }

    cout << endl << "Files Found in each Website:" << endl << endl;

    for (auto i: urlVisitedVector)
    {
        		cout << "Files found in: " << i << endl;
        		listPdfFilesInPage(i);
    }

	//string url = "http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/LectureNotes.html";
	//listPdfFilesInPage(url);

	return 0;
}



