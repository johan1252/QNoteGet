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

int createUserCourse(int userId,int courseId);
bool getUserCourses(int userId, std::vector<int>& courses);
bool deleteUserCourse(int userId, int courseId);
bool deleteUserCourses(int userId);

#endif /* USERCOURSE_H_ */
