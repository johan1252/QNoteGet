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
        std::string statement = "INSERT INTO USERPREFERENCES(USERID, COURSEID, PREFERENCEID, EXTENSIONID)";
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


bool dbGetUserPreferences(int userId, int& courseId, std::vector<int>& preferences) {
    std::string statement = "SELECT PREFERENCEID FROM USERPREFERENCES";
    std::string sql = statement + " WHERE COURSEID= '" + std::to_string(courseId) + "'AND USERID= '" + std::to_string(userId) + "'" + ";";
    pqxx::result R = dbExecuteReturn(sql);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    for (; i < R.size(); ++i) {
        std::stringstream spreference("");
        int preference;
        spreference << R[i][0];
        preference = stoi(spreference.str());
        preferences.push_back(preference);
    }
    return true;
}

bool dbGetUserExtensions(int userId, int& courseId, int& preferenceId, std::vector<int>& extensions) {
    std::string statement = "SELECT EXTENSIONID FROM USERPREFERENCES";
    std::string sql = statement + " WHERE COURSEID= '" + std::to_string(courseId) + "'AND USERID= '" + std::to_string(userId) + "'AND PREFERENCEID= '" + std::to_string(preferenceId) + "'" + ";";
    pqxx::result R = dbExecuteReturn(sql);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    for (; i < R.size(); ++i) {
        std::stringstream sextension("");
        int extension;
        sextension << R[i][0];
        extension = stoi(sextension.str());
        extensions.push_back(extension);
    }
    return true;
}



bool dbDeleteUserPreference(int id) {
	std::string beg = "DELETE FROM USERPREFERENCES";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}




