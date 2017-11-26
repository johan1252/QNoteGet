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
#include <vector>
#include "dbExecute.h"

int dbCreateExtension(const std::string& name);
std::vector<int> dbCreateMultipleExtensions(std::vector<std::string>& names);
bool dbDeleteExtension(int id);
bool dbDeleteExtensionByName(const std::string& name);
bool dbGetExtensionByName(int& id, const std::string& name);
std::vector<std::pair <int, std::string>> dbGetExtensionsAndNames();
bool dbGetExtensionName(int id, std::string& name);
bool dbGetExtensionID(int& id, const std::string& name);

#endif /* EXTENSION_H_ */
