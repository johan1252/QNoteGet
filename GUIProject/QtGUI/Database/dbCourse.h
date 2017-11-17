/*
 * courses.h
 *
 *  Created on: Nov 14, 2017
 *      Author: ganesha
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <pqxx/pqxx>
#include <string>
#include "dbExecute.h"
int dbCreateCourse(const std::string& name,const std::string& path);
bool dbUpdateCourse(int id, const std::string& name,const std::string& path);
bool dbGetCourse(int id, std::string& name,std::string& path);
bool dbGetCourseId(int& courseId, std::string name);
bool dbGetAllCourses(std::vector<int>& courseIds);
bool dbDeleteCourse(int id);
#endif /* COURSE_H_ */
