/*
 * createTable.h
 *
 *  Created on: Oct 29, 2017
 *      Author: ganesha
 */


#ifndef DATABASE_H_
#define DATABASE_H_

#include <pqxx/pqxx>
#include <string>

#include "dbCourse.h"
#include "dbExtension.h"
#include "dbUser.h"
#include "dbUserCourse.h"
#include "dbPreference.h"
#include "dbUserPreference.h"

int dbRunDatabase() ;
void dbCreatePreDefinedCourses();
void dbCreateTableQueries();

#endif /* DATABASE_H_ */
