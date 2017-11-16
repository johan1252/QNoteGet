/*
 * extensions.h
 *
 *  Created on: Nov 15, 2017
 *      Author: ganesha
 */

#ifndef EXTENSION_H_
#define EXTENSION_H_
#include <pqxx/pqxx>
#include <string>
#include "dbExecute.h"

int createExtension(const std::string& name);
bool deleteExtension(int id);
bool deleteExtensionByName(const std::string& name);

#endif /* EXTENSION_H_ */
