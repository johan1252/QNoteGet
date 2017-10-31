/*
 * createTable.h
 *
 *  Created on: Oct 29, 2017
 *      Author: ganesha
 */


#ifndef CREATETABLE_H_
#define CREATETABLE_H_

#include <pqxx/pqxx>
#include <string>

bool createTable(pqxx::connection& c,const std::string& sql);


#endif /* CREATETABLE_H_ */
