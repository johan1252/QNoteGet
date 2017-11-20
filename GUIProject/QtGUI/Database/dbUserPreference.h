/*
 * userPreferences.h
 *
 *  Created on: Nov 15, 2017
 *      Author: ganesha
 */

#ifndef USERPREFERENCE_H_
#define USERPREFERENCE_H_



#include <pqxx/pqxx>
#include <string>
#include "dbExecute.h"
//
//		std::string userPreferences = "CREATE TABLE USERPREFERENCES("  \
//					   "ID           SERIAL PRIMARY KEY          NOT NULL," \
//					   "USERID       INT REFERENCES USERS(ID)        NOT NULL," \
//					   "COURSEID     INT REFERENCES COURSES(ID)      NOT NULL," \
//					   "PREFERENCEID INT REFERENCES PREFERENCES(ID)  NOT NULL," \
//					   "EXTENSIONID  INT REFERENCES EXTENSIONS(ID)   NOT NULL);";

int dbCreateUserPreference(int userId, int courseId, int preferenceId, int extensionId);
bool dbGetUserPreferences(int userId, int& courseId, std::vector<int>& preferences);
bool dbGetUserExtensions(int userId, int& courseId, int& preferenceId, std::vector<int>& extensions);
bool dbDeleteUserPreference(int id);

#endif /* USERPREFERENCE_H_ */
