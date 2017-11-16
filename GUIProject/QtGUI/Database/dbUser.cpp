/*
 * user.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: ganesha
 */

#include "dbUser.h"
#include <pqxx/pqxx>
#include <ostream>

//creates a user and returns their id
int createUser(const std::string& name,int& password,const std::string& path, int update){
    	std::string statement = "INSERT INTO users(NAME, PASSWORD, PATH, UPDATE)";
    	std::string user = statement + " VALUES ('" + name + "','" + std::to_string(password) + "','" +
    			path + "','" + std::to_string(update) + "')" + "RETURNING ID;";

    pqxx::result R = executeReturn(user);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream userId;
    userId << R[i][0];
    return stoi(userId.str());
}

//resets all user fields
bool updateUser(int id, const std::string& name,int& password,const std::string& path, int update){
	std::string beg = "UPDATE USERS SET";
	std::string statement = beg + " NAME ='" + name + "', PASSWORD ='" +
		std::to_string(password) + "', PATH ='" + path + "', UPDATE ='" + std::to_string(update) +
		"' WHERE ID= '" + std::to_string(id) + "';";
    return execute(statement);
}

//sets all attributes by reference for caller
bool getUser(int id, std::string& name,int password, std::string& path, int& update) {
	std::string statement = "SELECT * FROM USERS WHERE ID=" + std::to_string(id);
	pqxx::result R = executeReturn(statement);
	if (R.empty()) {
	    	return false;
	}
	pqxx::result::size_type i = 0;
	std::stringstream sname, spass, spath, supdate;
	for (; i < R.size(); ++i) {
		sname << R[i][1];
		name = sname.str();
		spass << R[i][2];
		password = stoi(spass.str());
		spath << R[i][3];
		path = spath.str();
		supdate << R[i][4];
		update = stoi(supdate.str());
	}
	return R.empty();
}

bool deleteUser(int id) {
	std::string beg = "DELETE FROM USERS";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
	return execute(statement);
}





