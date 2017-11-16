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
int createCourse(const std::string& name,const std::string& path);
bool updateCourse(int id, const std::string& name,const std::string& path);
bool getCourse(int id, std::string& name,std::string& path);
bool deleteCourse(int id);
#endif /* COURSE_H_ */
