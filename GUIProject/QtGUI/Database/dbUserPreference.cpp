/*
 * userPreferences.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: ganesha
 */

#include <pqxx/pqxx>
#include <ostream>
#include "dbUserPreference.h"

//creates a UserPreference and returns their id
int dbCreateUserPreference(int userId, int courseId, int preferenceId, int extensionId){
    	std::string statement = "INSERT INTO USERPREFERENCES(USERID, COURSEID, PREFERENCEID, EXTENSION)";
    	std::string userPreference = statement + " VALUES ('" + std::to_string(userId) + "','" +  std::to_string(courseId) + "','" +
    			std::to_string(preferenceId) + "','" + std::to_string(extensionId) + "')" + "RETURNING ID;";

    pqxx::result R = dbExecuteReturn(userPreference);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream userPreferenceId;
    userPreferenceId << R[i][0];
    return stoi(userPreferenceId.str());
}

//sets all attributes by reference for caller
//bool getUserPreference(int id, std::string& name, std::string& path) {
//	std::string statement = "SELECT * FROM COURSES WHERE ID=" + std::to_string(id);
//	pqxx::result R = executeReturn(statement);
//	if (R.empty()) {
//	    	return false;
//	}
//	pqxx::result::size_type i = 0;
//	std::stringstream spath, sname;
//	for (; i < R.size(); ++i) {
//		sname << R[i][1];
//		name = sname.str();
//		spath << R[i][2];
//		path = spath.str();
//	}
//	return R.empty();
//}

bool dbDeleteUserPreference(int id) {
	std::string beg = "DELETE FROM USERPREFERENCES";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}



