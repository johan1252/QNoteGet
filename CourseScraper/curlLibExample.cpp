/*
 * curlLibExample.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Team Simcoe
 */

#include "curlLibExample.hpp"

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

// NOT USED CURRENTLY
void CourseScraper::get320LectureNotes() {
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
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
				res = curl_easy_perform(curl);
				/* always cleanup */

				fclose(fp);

	    		}
	    }
	    curl_easy_cleanup(curl);

	    return;
}

void CourseScraper::tryWebsiteWithAuthentication() {

	//char url[100];
	//strcpy(url,urlInput);

	CURL* curl; //our curl object

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	bool authenticated = false;
	bool attemptFailed = false;
	bool attemptFailedMoved = false;
	while (!authenticated && !attemptFailedMoved) {
		data = "";

		if ( (username == "" || password == "") || attemptFailed ) {
				cout << "PASSWORD REQUIRED FROM USER FOR " << url << endl;
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

		attemptFailed = false;
		attemptFailedMoved = false;
		while (getline(ss, line)) {
				//cout << "AUTHDEBUG " << line << endl;
				if (line.find("401 Authorization Required") != -1) {
					attemptFailed = true;
					ss.clear();
					ss.str("");
					break;
				}
				if (line.find("301 Moved Permanently") != -1) {
					//Delete url from list if its moved now
					auto itr = find(urlVisitedVector.begin(), urlVisitedVector.end(), url);
					if (itr != urlVisitedVector.end()) urlVisitedVector.erase(itr);

					strcat(url,"/");

					attemptFailedMoved = true;
					ss.clear();
					ss.str("");

					break;
				}

		}
		if (!attemptFailed && !attemptFailedMoved) {
			authenticated = true;
		}

	}

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return;

}

// NOT USED CURRENTLY
char* CourseScraper::getPage() {
	CURL* curl;

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

	curl_easy_perform(curl);

	stringstream ss_initial(data);
	string line;

	while (getline(ss_initial, line)) {
		if (line.find("401 Authorization Required") != -1) {
			//cout << "ATTENTION: " << line << endl;

			tryWebsiteWithAuthentication();

			break;
		}
		if (line.find("301 Moved Permanently") != -1) {
			cout << "ATTENTION: " << line << endl;



			//Make this a function (to get a page)
			//getPage(url);

			break;
		}
	}
	return url;
}

bool CourseScraper::checkIfWebPageError(CURL* curl, string line) {
	if (line.find("401 Authorization Required") != -1) {
		tryWebsiteWithAuthentication();
		return true;
	}
	if (line.find("301 Moved Permanently") != -1) {
		data = "";
		//Delete url from list if its moved now
		auto itr = find(urlVisitedVector.begin(), urlVisitedVector.end(), url);
		if (itr != urlVisitedVector.end()) urlVisitedVector.erase(itr);

		//Add extra slash if site moved.
		strcat(url,"/");

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_perform(curl);

		return true;
	}
	return false;
}

void CourseScraper::listPdfFilesInPage (string inputUrl) {
		data = "";

		strcpy(url,inputUrl.c_str());

		CURL* curl; //our curl object

	    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	    curl = curl_easy_init();

	    curl_easy_setopt(curl, CURLOPT_URL, url);
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

	    curl_easy_perform(curl);

	    stringstream ss_initial(data);
	    string line;

	    while (getline(ss_initial, line)) {
	    		if (checkIfWebPageError(curl, line)) {
	    			break;
	    		}
		}

		// Reset string stream for second loop.
		stringstream ss(data);

	    vector<string> pdfFilesVector;
	    const char* lastPdfName;

	    while (getline(ss, line)) {
	    		//cout << line << endl;
	    		if (line.find(".pdf") != -1){
	    			//cout << line << endl;
	    			unsigned first = line.find('"');
	    			unsigned last = line.find(".pdf\"");
	    			string pdfFile = line.substr(first+1,last-first+3);
	    			pdfFilesVector.push_back(pdfFile);
	    			lastPdfName = pdfFile.c_str();
	    		} else if (line.find("https://drive.google.com/file/") != -1) {
	    			//cout << "DEBUG " << line << endl;
	    			unsigned first = line.find("https://drive.google.com/file/");
				unsigned last = line.find("\">");
				string pdfFile = line.substr(first,last-first);
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

bool CourseScraper::checkUrlValidity(string fullUrl) {
	if (find(begin(urlVisitedVector), end(urlVisitedVector), fullUrl) == end(urlVisitedVector)) {
		// Also check that equivalent url (with and extra slash) has not already been seen.
		string equivfullUrl = fullUrl + "/";
		if (find(begin(urlVisitedVector), end(urlVisitedVector), equivfullUrl) == end(urlVisitedVector)) {
			if (fullUrl.find("/#") == -1) {
					return true;
			}
		}
	}
	return false;
}

void CourseScraper::recursivelyListUrls(string userInput) {
		// IMPORTANT, DATA MUST BE CLEARED FIRST
		data = "";

		//char url [100];
	    strcpy(url,userInput.c_str());

	    //cout << "USER INPUT: " << userInput << endl;
	    //cout << "URL: " << url << endl;

	    // Remove everything after last slash to get root webpage.
	    userInput.erase(userInput.rfind('/'));

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
	    } */


	    while (getline(ss_initial, line)) {
	    		if (checkIfWebPageError(curl, line)) {
	    			break;
	    		}
	    }

	    // Reset string stream for second loop.
		stringstream ss(data);



		// Add base URL to list if not already in it.
		if (find(begin(urlVisitedVector), end(urlVisitedVector), url) == end(urlVisitedVector)) {
			//cout << "URL when adding to list " << url << endl;
			urlVisitedVector.push_back(url);
		}

	    while (getline(ss, line)) {
	    		// DEBUG: To print out html page
	    		//cout << line << endl;

	    		string lineLowerCase = line;
	    		transform(lineLowerCase.begin(), lineLowerCase.end(), lineLowerCase.begin(), ::tolower);
	    		// If in format http://research.cs.queensu.ca/home/cisc320/assignments.html
	    		if (lineLowerCase.find("href=") != -1 && lineLowerCase.find(".html\"") != -1) {
	    			if (!((lineLowerCase.find("http://") != -1 || lineLowerCase.find("https://") != -1) && !(lineLowerCase.find(hostName) != -1))) {
	    					// If it is a website address that is not to the internal host.
	    					// Example if ref is to anything research.cs.queensu then that is fine but not to googleTutorials.com/ etc.

						//cout << "DEBUG: Found Line " << line << endl;

						unsigned first = lineLowerCase.find('"');
						unsigned last = lineLowerCase.find(".html\"");
						string htmlPage = line.substr(first+1,last-first+4);
						string fullUrl = userInput + "/" + htmlPage;

						// check to ensure url has not already been seen and then add to htmlPagesVector and urlVisitedVector.
						if (checkUrlValidity(fullUrl)) {
							htmlPagesVector.push_back(fullUrl);
							urlVisitedVector.push_back(fullUrl);
							//cout << "3URL when adding to list " << fullUrl << endl;
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

							// check to ensure url has not already been seen and then add to htmlPagesVector and urlVisitedVector.
							if (checkUrlValidity(fullUrl)) {
								htmlPagesVector.push_back(fullUrl);
								urlVisitedVector.push_back(fullUrl);
								//cout << "3URL when adding to list " << fullUrl << endl;
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

								// check to ensure url has not already been seen and then add to htmlPagesVector and urlVisitedVector.
								if (checkUrlValidity(fullUrl)) {
									htmlPagesVector.push_back(fullUrl);
									urlVisitedVector.push_back(fullUrl);
									//cout << "3URL when adding to list " << fullUrl << endl;
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
	    		recursivelyListUrls(i);
	    }

	    //cout << "Pdf Files Found:" << endl;
	    //for (auto i: htmlPagesVector)
	    	//	listPdfFilesInPage(i);
}

int main()
{
	//get320LectureNotes();
	CourseScraper scraper;

	string userInput;
    cout << "Please enter course (CISC320,ELEC451): ";
    cin >> userInput;
    //userInput = "http://research.cs.queensu.ca/home/cisc320/";
    //userInput = "http://post.queensu.ca/~nm7/ELEC451/";

    transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
    string courseUrl = scraper.courses_map[userInput];

    scraper.recursivelyListUrls(courseUrl);
    cout << endl << "Websites Found:" << endl;
    for (auto i: scraper.urlVisitedVector)
    {
    		cout << i << endl;
    }

    cout << endl << "Files Found in each Website:" << endl << endl;

    for (auto i: scraper.urlVisitedVector)
    {
        		cout << "Files found in: " << i << endl;

        		scraper.listPdfFilesInPage(i);
    }

	return 0;
}



