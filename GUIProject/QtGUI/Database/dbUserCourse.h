/*
 * userUserCourse.h
 *
 *  Created on: Nov 14, 2017
 *      Author: ganesha
 */

#ifndef USERCOURSE_H_
#define USERCOURSE_H_

#include <pqxx/pqxx>
#include <string>
#include <vector>
#include "dbExecute.h"

int dbCreateUserCourse(int userId,int courseId);
bool dbGetUserCourses(int userId, std::vector<int>& courses);
bool dbDeleteUserCourse(int userId, int courseId);
bool dbDeleteUserCourses(int userId);

#endif /* USERCOURSE_H_ */
