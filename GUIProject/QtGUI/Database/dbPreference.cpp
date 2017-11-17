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
int dbCreatePreference(int courseId, const std::string& name,const std::string& path) {
    	std::string statement = "INSERT INTO PREFERENCES(COURSEID, NAME, PATH)";
    	std::string preference = statement + " VALUES ('" + std::to_string(courseId) + "','" + name + "','" +
    			path + "')" + "RETURNING ID;";

    pqxx::result R = dbExecuteReturn(preference);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream preferenceId;
    preferenceId << R[i][0];
    return stoi(preferenceId.str());
}

//given a courseId you get a vector of preferenceIds
bool dbGetPreferenceIds(int courseId,std::vector<int> preferences){
    std::string statement = "SELECT * FROM PREFERENCES WHERE courseid='" + std::to_string(courseId) + "'";
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    for (; i < R.size(); ++i) {
        std::stringstream id("");
        int pid;
        id << R[i][0];
        pid = stoi(id.str());
        preferences.push_back(pid);
    }
    return R.empty();
}

bool dbGetPreference(int id,std::string& name,std::string& path) {
    std::string statement = "SELECT * FROM PREFERENCES WHERE ID=" + std::to_string(id);
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    std::stringstream spath, sname;
    for (; i < R.size(); ++i) {
        sname << R[i][2];
        name = sname.str();
        spath << R[i][3];
        path = spath.str();
    }
    return true;
}

bool dbDeletePreference(int id) {
	std::string beg = "DELETE FROM PREFERENCES";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}



