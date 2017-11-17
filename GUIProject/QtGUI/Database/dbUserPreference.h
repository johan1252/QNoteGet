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
//bool getUserPreference(int& userId, int& courseId, vector of preferenceIds); // given userId and courseId return all preferenceID's
//bool getUserPreference(int& userId, int& courseId, int& preferenceId, vector of extensionIds); // given userId and courseId and preferenceId return all extentionIds
bool dbDeleteUserPreference(int id);

#endif /* USERPREFERENCE_H_ */
