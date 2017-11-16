/*
 * preferences.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: ganesha
 */

#include <pqxx/pqxx>
#include <ostream>
#include "dbPreference.h"

//creates a Preference and returns their id
int createPreference(int courseId, const std::string& name,const std::string& path) {
    	std::string statement = "INSERT INTO PREFERENCES(COURSEID, NAME, PATH)";
    	std::string preference = statement + " VALUES ('" + std::to_string(courseId) + "','" + name + "','" +
    			path + "')" + "RETURNING ID;";

    pqxx::result R = executeReturn(preference);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream preferenceId;
    preferenceId << R[i][0];
    return stoi(preferenceId.str());
}


//sets all attributes by reference for caller
//bool getPreference(int id, int courseId, std::string& name, std::string& path) {
//	std::string statement = "SELECT * FROM PREFERENCES WHERE ID=" + std::to_string(id);
//	pqxx::result R = executeReturn(statement);
//	if (R.empty()) {
//	    	return false;
//	}
//	pqxx::result::size_type i = 0;
//	std::stringstream scourse, spath, sname;
//	for (; i < R.size(); ++i) {
//		sname << R[i][2];
//		name = sname.str();
//		spath << R[i][1];
//		path = spath.str();
//	}
//	return R.empty();
//}

bool deletePreference(int id) {
	std::string beg = "DELETE FROM PREFERENCES";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
	return execute(statement);
}



