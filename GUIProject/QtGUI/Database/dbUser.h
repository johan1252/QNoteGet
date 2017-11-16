/*
 * user.h
 *
 *  Created on: Nov 13, 2017
 *      Author: ganesha
 */

#ifndef USER_H_
#define USER_H_

#include <pqxx/pqxx>
#include <string>
#include "dbExecute.h"


int createUser(const std::string& name,const std::string& password,const std::string& path, int update);
bool updateUser(int id, const std::string& name,int& password,const std::string& path, int update);
bool getUser(int id, std::string& name,int& password, std::string& path, int& update);
bool deleteUser(int id);
#endif /* USER_H_ */
