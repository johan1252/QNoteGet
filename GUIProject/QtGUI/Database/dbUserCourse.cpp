/*
 * userUserCourse.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: ganesha
 */

#include <pqxx/pqxx>
#include <ostream>
#include "dbCourse.h"



//create a single row, returns the unique id
int createUserCourse(int userId,int courseId){
    	std::string statement = "INSERT INTO USERCOURSES(courseId, userId)";
    	std::string course = statement + " VALUES ('" + std::to_string(courseId) + "','" +
    			std::to_string(userId) + "')" + "RETURNING ID;";

    pqxx::result R = executeReturn(course);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream id;
    id << R[i][0];
    return stoi(id.str());
}

//return all courseID's that a user is registered to
bool getUserCourses(int userId, std::vector<int>& courses) {
	std::string statement = "SELECT COURSEID FROM USERCOURSES WHERE userId=" + std::to_string(userId);
    pqxx::result R = executeReturn(statement);
    pqxx::result::size_type i = 0;

    	for (; i < R.size(); ++i) {
    		std::stringstream sid("");
		std::string id;
		sid << R[i][0];
		id = sid.str();
		courses.push_back(stoi(id));
    	}
    	return R.empty();
}

//deletes all instances related to the user
bool deleteUserCourses(int userId) {
	std::cout << "entered";
	std::string beg = "DELETE FROM USERCOURSES";
	std::string statement = beg +
		" WHERE USERID= '" + std::to_string(userId) + "';";
	return execute(statement);
}

//deletes a single row - this instance for this user
bool deleteUserCourse(int userId, int courseId) {
	std::string beg = "DELETE FROM USERCOURSES";
	std::string statement = beg +
		" WHERE USERID= '" + std::to_string(userId) + "' AND COURSEID= '" + std::to_string(courseId) + "';";
	return execute(statement);
}



