/*
 * courses.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: ganesha
 */
#include <pqxx/pqxx>
#include <ostream>
#include "dbCourse.h"

//creates a Course and returns their id
int createCourse(const std::string& name,const std::string& path){
    	std::string statement = "INSERT INTO Courses(NAME, PATH)";
    	std::string course = statement + " VALUES ('" + name + "','" +
    			path + "')" + "RETURNING ID;";

    pqxx::result R = executeReturn(course);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream courseId;
    courseId << R[i][0];
    return stoi(courseId.str());
}

//resets all Course fields
bool updateCourse(int id, const std::string& name,const std::string& path){
	std::string beg = "UPDATE COURSES SET";
	std::string statement = beg + " NAME ='" + name + "', PATH ='" + path +
			"' WHERE ID= '" + std::to_string(id) + "';";
    return execute(statement);
}

//sets all attributes by reference for caller
bool getCourse(int id, std::string& name, std::string& path) {
	std::string statement = "SELECT * FROM COURSES WHERE ID=" + std::to_string(id);
	pqxx::result R = executeReturn(statement);
	if (R.empty()) {
	    	return false;
	}
	pqxx::result::size_type i = 0;
	std::stringstream spath, sname;
	for (; i < R.size(); ++i) {
		sname << R[i][1];
		name = sname.str();
		spath << R[i][2];
		path = spath.str();
	}
	return R.empty();
}

bool deleteCourse(int id) {
	std::string beg = "DELETE FROM COURSES";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
	return execute(statement);
}
