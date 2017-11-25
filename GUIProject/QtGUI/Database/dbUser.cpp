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
int dbCreateUser(const std::string name,int password,const std::string path, int update){
    	std::string statement = "INSERT INTO users(NAME, PASSWORD, PATH, UPDATE)";
    	std::string user = statement + " VALUES ('" + name + "','" + std::to_string(password) + "','" +
    			path + "','" + std::to_string(update) + "')" + "RETURNING ID;";

    pqxx::result R = dbExecuteReturn(user);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream userId;
    userId << R[i][0];
    return stoi(userId.str());
}

//resets all user fields
bool dbUpdateUser(int id, const std::string& name,int& password,const std::string& path, int update){
	std::string beg = "UPDATE USERS SET";
	std::string statement = beg + " NAME ='" + name + "', PASSWORD ='" +
		std::to_string(password) + "', PATH ='" + path + "', UPDATE ='" + std::to_string(update) +
		"' WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}

//sets all attributes by reference for caller
bool dbGetUser(int id, std::string& name,int& password, std::string& path, int& update) {
	std::string statement = "SELECT * FROM USERS WHERE ID=" + std::to_string(id);
    pqxx::result R = dbExecuteReturn(statement);
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

//gets id via name
bool dbGetUserByName(std::string name,int& id) {
    std::string statement = "SELECT * FROM USERS WHERE NAME='" + name + "'";
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
         return false;
    }
    pqxx::result::size_type i = 0;
    std::stringstream sid;
    for (; i < R.size(); ++i) {
        sid << R[i][0];
        id = stoi(sid.str());
    }
    return true;
}

//sets all attributes by reference for caller
bool dbGetUserWithUsername(std::string name,int& password, std::string& path, int& update) {
    std::string statement = "SELECT * FROM USERS WHERE NAME='" + name + "'";
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    std::stringstream sname, spass, spath, supdate;
    for (; i < R.size(); ++i) {
        std::cout << "\n\n" << spass.str() << std::endl;
        sname << R[i][1];
        name = sname.str();
        spass << R[i][2];
        password = stoi(spass.str());
        spath << R[i][3];
        path = spath.str();
        supdate << R[i][4];
        update = stoi(supdate.str());
    }
    return true;
}

bool deleteUser(int id) {
	std::string beg = "DELETE FROM USERS";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}





