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

int createPreference(int courseId, const std::string& name,const std::string& path);
//bool getPreferences(int courseId, #vector of preferenceIds); //given a courseId you get a vector of preferenceIds
//bool getPreferences(int id, &name, &path); //given a preferenceId you can get the name/path
bool deletePreference(int id);

#endif /* PREFERENCE_H_ */
