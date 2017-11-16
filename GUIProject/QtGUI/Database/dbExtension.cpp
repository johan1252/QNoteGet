/*
 * extensions.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: ganesha
 */


/*
 * extension.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: ganesha
 */
#include <pqxx/pqxx>
#include <ostream>
#include "dbCourse.h"

//creates a Extension and returns their id
int createExtension(const std::string& name){
    	std::string statement = "INSERT INTO EXTENSIONS(NAME)";
    	std::string course = statement + " VALUES ('" + name + "')" + "RETURNING ID;";

    pqxx::result R = executeReturn(course);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream courseId;
    courseId << R[i][0];
    return stoi(courseId.str());
}

bool deleteExtension(int id) {
	std::string beg = "DELETE FROM EXTENSIONS";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
	return execute(statement);
}

bool deleteExtensionByName(const std::string& name) {
	std::string beg = "DELETE FROM EXTENSIONS";
	std::string statement = beg +
		" WHERE NAME= '" + name + "';";
	return execute(statement);
}

