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


int dbCreateUser(const std::string name,int password,const std::string path, int update);
bool dbUpdateUser(int id, const std::string& name,int& password,const std::string& path, int update);
bool dbGetUser(int id, std::string& name,int& password, std::string& path, int& update);
bool dbGetUserWithUsername(std::string name,int& password, std::string& path, int& update);
bool deleteUser(int id);

#endif /* USER_H_ */
