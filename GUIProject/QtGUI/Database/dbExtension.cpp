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
#include <string>

//creates a Extension and returns their id
int dbCreateExtension(const std::string& name){
    	std::string statement = "INSERT INTO EXTENSIONS(NAME)";
    	std::string course = statement + " VALUES ('" + name + "')" + "RETURNING ID;";

    pqxx::result R = dbExecuteReturn(course);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream courseId;
    courseId << R[i][0];
    return stoi(courseId.str());
}

bool dbDeleteExtension(int id) {
	std::string beg = "DELETE FROM EXTENSIONS";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}

bool dbDeleteExtensionByName(const std::string& name) {
	std::string beg = "DELETE FROM EXTENSIONS";
	std::string statement = beg +
		" WHERE NAME= '" + name + "';";
    return dbExecute(statement);
}

//sets all attributes by reference for caller
bool dbGetExtensionName(int id, std::string& name) {
    std::string statement = "SELECT * FROM EXTENSIONS WHERE ID=" + std::to_string(id);
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    std::stringstream spath, sname;
    for (; i < R.size(); ++i) {
        sname << R[i][1];
        name = sname.str();
    }
    return R.empty();
    // comment so bitbucket reflects changes, delete afterwards

}

bool dbGetExtensionID(int& id, const std::string& name){
    std::string statement = "SELECT * FROM EXTENSIONS WHERE NAME='" + name + "';";
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()){
        return false;
    }

    pqxx::result::size_type i = 0;
    std::stringstream sid;
    for (; i < R.size(); i++){
        sid << R[i][0];
        id = std::stoi(sid.str());
    }
    return true;
}
