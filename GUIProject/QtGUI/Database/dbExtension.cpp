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
#include <QDebug>
#include "dbCourse.h"

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

std::vector<int> dbCreateMultipleExtensions(std::vector<std::string>& names){
    std::vector<int> newIDs;
    std::string statement = "INSERT INTO EXTENSIONS(NAME)";
    if (names.size() == 0){
        newIDs.push_back(-1);
        return newIDs;
    }
    if (names.size() == 1){
        statement += " VALUES ('" + names[0] + "') RETURNING ID;";
    }
    else{
        statement += " VALUES ";
        for (unsigned long i = 0; i < names.size(); i++){
            if (i == names.size() - 1){
                statement += "('" + names[i] + "') RETURNING ID;";
            }
            else{
                statement += "('" + names[i] + "'),";
            }
        }
    }

    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()){
        newIDs.push_back(-1);
        return newIDs;
    }

    std::string sid;
    for (int i = 0; i < R.size(); i++){
        sid = R[i][0].c_str();
        newIDs.push_back(std::stoi(sid));
    }
    return newIDs;
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
bool dbGetExtensionByName(int& id, const std::string& name) {
     std::string statement = "SELECT id FROM EXTENSIONS WHERE NAME='" + name + "';";
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
        id = -1;
        return false;
    }
    pqxx::result::size_type i = 0;
    std::stringstream sid;
    for (; i < R.size(); ++i) {
        sid << R[i][0];
        id = std::stoi(sid.str());
    }
    return true;
    // comment so bitbucket reflects changes, delete afterwards

}

std::vector<std::pair<int, std::string> > dbGetExtensionsAndNames(){
    std::string statement = "SELECT * FROM EXTENSIONS;";
    std::vector<std::pair <int, std::string>> pairVec;
    std::pair <int, std::string> idNamePair;
    pqxx::result R = dbExecuteReturn(statement);

    if (R.empty()){
        idNamePair = std::make_pair(-1, "null");
        pairVec.push_back(idNamePair);
        return pairVec;
    }

    pqxx::result::size_type i = 0;
    std::string sid;
    std::string name;
    for (; i < R.size(); i++){
        sid = R[i][0].c_str();
        name = R[i][1].c_str();
        idNamePair = std::make_pair(std::stoi(sid), name);
        pairVec.push_back(idNamePair);
    }

    return pairVec;
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
    std::string sid;
    sid = R[i][0].c_str();
    id = std::stoi(sid);
    return true;
}
