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

int dbCreateExtension(const std::string& name);
bool dbDeleteExtension(int id);
bool dbDeleteExtensionByName(const std::string& name);
bool dbGetExtensionName(int id, std::string& name);
bool dbGetExtensionID(int& id, const std::string& name);
// comment so bitbucket reflects changes, delete afterwards

#endif /* EXTENSION_H_ */
