/*
 * curlLibExample.hpp
 *
 *  Created on: Oct 29, 2017
 *      Author: johancornelissen
 */

#ifndef CURLLIBEXAMPLE_HPP_
#define CURLLIBEXAMPLE_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <curl/curl.h> //your directory may be different
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

using namespace std;

class CourseScraper;

class CourseScraper
{
public:
	void listAllFilesFoundInURL(string userInput);
	void listPdfFilesInPage (string inputUrl);

	std::map<string, string> courses_map = {
	    { "CISC320", "http://research.cs.queensu.ca/home/cisc320/" },
	    { "ELEC451", "http://post.queensu.ca/~nm7/ELEC451/" }
	};

	vector<string> urlVisitedVector;

private:

	string username;
	string password;

	char url [100];

	//Not currently used
	void get320LectureNotes();

	void tryWebsiteWithAuthentication();

	//Not currently used;
	char* getPage();

	bool checkIfWebPageError(CURL* curl, string line);

	bool checkUrlValidity(string fullUrl);

};

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
string data; //will hold the url's contents

#endif /* CURLLIBEXAMPLE_HPP_ */
