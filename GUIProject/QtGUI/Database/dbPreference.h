/*
 * preferences.h
 *
 *  Created on: Nov 15, 2017
 *      Author: ganesha
 */

#ifndef PREFERENCE_H_
#define PREFERENCE_H_

#include <pqxx/pqxx>
#include <string>
#include "dbExecute.h"

//  "ID       SERIAL PRIMARY KEY  NOT NULL," \
//						  "COURSEID INT REFERENCES COURSES(ID)  NOT NULL," \
//						  "NAME     TEXT             NOT NULL," \
//						  "PATH     TEXT             NOT NULL);";

int dbCreatePreference(int courseId, const std::string& name,const std::string& path);
bool dbGetPreferenceIds(int courseId,std::vector<int> preferences); //given a courseId you get a vector of preferenceIds
bool dbGetPreference(int id,std::string& name,std::string& path); //given a preferenceId you can get the name/path
bool dbDeletePreference(int id);

#endif /* PREFERENCE_H_ */
