/*
 * execute.h
 *
 *  Created on: Nov 13, 2017
 *      Author: ganesha
 */

#ifndef EXECUTE_H_
#define EXECUTE_H_

#include <iostream>
#include <pqxx/pqxx>

pqxx::result executeReturn(const std::string& sql);
bool execute(const std::string& sql);

#endif /* EXECUTE_H_ */
