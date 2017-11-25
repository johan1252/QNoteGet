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
#include <vector>
//
//		std::string userPreferences = "CREATE TABLE USERPREFERENCES("  \
//					   "ID           SERIAL PRIMARY KEY          NOT NULL," \
//					   "USERID       INT REFERENCES USERS(ID)        NOT NULL," \
//					   "COURSEID     INT REFERENCES COURSES(ID)      NOT NULL," \
//					   "PREFERENCEID INT REFERENCES PREFERENCES(ID)  NOT NULL," \
//					   "EXTENSIONID  INT REFERENCES EXTENSIONS(ID)   NOT NULL);";

int dbCreateUserPreference(int userId, int courseId, int preferenceId, int extensionId);
std::vector<int> dbCreateMultipleUserPreferences(int userId, int courseId, int preferenceId, std::vector<int> extensionsIds);
bool dbGetUserPreferences(int userId, const int& courseId, std::vector<int>& preferences);
bool dbGetUserExtensions(int userId, const int& courseId, int& preferenceId, std::vector<int>& extensions);
bool dbDeleteUserPreference(int id);
bool dbDeleteUserCategoryPreference(const int userId, const int courseId, const std::vector<int> idsToDelete);
bool dbDeleteUserExtensionPreference(const int userId, const int courseId, const int preferenceId, const std::vector<int> idsToDelete);

#endif /* USERPREFERENCE_H_ */
