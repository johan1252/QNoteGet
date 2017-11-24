/*
 * userPreferences.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: ganesha
 */

#include <pqxx/pqxx>
#include <ostream>
#include <vector>
#include "dbUserPreference.h"
#include <QDebug>

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

std::vector<int> dbCreateMultipleUserPreferences(int userId, int courseId, int preferenceId, std::vector<int> extensionsIds){
    std::vector<int> userPrefIds;
    if (extensionsIds.size() == 0){
        userPrefIds.push_back(-1);
        return userPrefIds;
    }

    std::string statement = "INSERT INTO USERPREFERENCES(USERID, COURSEID, PREFERENCEID, EXTENSIONID)";

    if(extensionsIds.size() == 1){
        statement += " VALUES ('" + std::to_string(userId) + "', '" + std::to_string(courseId) + "', '" +
                std::to_string(preferenceId) + "', '" + std::to_string(extensionsIds[0]) + "') RETURNING ID;";
    }
    else{
        statement += "VALUES ";
        for (int i = 0; i < extensionsIds.size(); i++){
            if (i == extensionsIds.size() - 1){
                statement += "('" + std::to_string(userId) + "', '" + std::to_string(courseId) + "', '" +
                        std::to_string(preferenceId) + "', '" + std::to_string(extensionsIds[0]) + "') RETURNING ID;";
            }
            else{
                 statement += "('" + std::to_string(userId) + "', '" + std::to_string(courseId) + "', '" +
                        std::to_string(preferenceId) + "', '" + std::to_string(extensionsIds[0]) + "'), ";
            }
        }
    }

    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()){
        userPrefIds.push_back(-1);
        return userPrefIds;
    }
    pqxx::result::size_type i = 0;
    std::stringstream sid;
    int id;
    for (; i < R.size(); ++i){
        sid << R[i][0];
        id = std::stoi(sid.str());
        userPrefIds.push_back(id);
    }
    return userPrefIds;

}

bool dbGetUserPreferences(int userId, const int& courseId, std::vector<int>& preferences) {
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

bool dbGetUserExtensions(int userId, const int& courseId, int& preferenceId, std::vector<int>& extensions) {
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

bool dbDeleteUserCategoryPreference(const int userId, const int courseId, const std::vector<int> idsToDelete){
    std::string beg = "DELETE FROM USERPREFERENCES ";
    std::string statement = beg + "WHERE USERID='" + std::to_string(userId) + "' AND COURSEID='" +
            std::to_string(courseId) + "' ";
    if (idsToDelete.size() == 0){
        return false;
    }
    else if (idsToDelete.size() == 1){
        statement += "AND PREFERENCEID='" + std::to_string(idsToDelete[0]) + "';";
    }
    else{
        statement += "AND PREFERENCEID IN (";
        for (int i = 0; i < idsToDelete.size(); i++){
            if ( i == idsToDelete.size() - 1){
                statement += std::to_string(idsToDelete[i]) + ");";
            }
            else{
                statement += std::to_string(idsToDelete[i]) + ", ";
            }
        }
    }
    qDebug() << "INSIDE dbUserPreference, statement is: " << QString::fromStdString(statement);
    return dbExecute(statement);
}

bool dbDeleteUserExtensionPreference(const int userId, const int courseId, const int preferenceId, const std::vector<int> idsToDelete){
std::string beg = "DELETE FROM USERPREFERENCES ";
std::string statement = beg + "WHERE USERID='" + std::to_string(userId) + "' AND COURSEID='" +
        std::to_string(courseId) + "' AND PREFERENCEID='" + std::to_string(preferenceId) + "' ";
if (idsToDelete.size() == 0){
    return false;
}
else if(idsToDelete.size() == 1){
    statement += "AND EXTENSIONID='" + std::to_string(idsToDelete[0]) + "';";
}
else{
    statement += "AND EXTENSIONID IN (";
    for (int i = 0; i < idsToDelete.size(); i++){
        if (i == idsToDelete.size() - 1){
            statement += std::to_string(idsToDelete[i]) + ");";
        }
        else{
            statement += std::to_string(idsToDelete[i]) + ", ";
        }
    }
}

return dbExecute(statement);
}


