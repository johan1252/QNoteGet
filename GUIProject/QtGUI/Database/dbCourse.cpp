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
int dbCreateCourse(const std::string& name,const std::string& path){
    	std::string statement = "INSERT INTO Courses(NAME, PATH)";
    	std::string course = statement + " VALUES ('" + name + "','" +
    			path + "')" + "RETURNING ID;";

    pqxx::result R = dbExecuteReturn(course);
    if (R.empty()) {
    		return 0;
    }
    pqxx::result::size_type i = 0;
    std::stringstream courseId;
    courseId << R[i][0];
    return stoi(courseId.str());
}

//resets all Course fields
bool dbUpdateCourse(int id, const std::string& name,const std::string& path){
	std::string beg = "UPDATE COURSES SET";
	std::string statement = beg + " NAME ='" + name + "', PATH ='" + path +
			"' WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}

//sets all attributes by reference for caller
bool dbGetCourse(int id, std::string& name, std::string& path) {
	std::string statement = "SELECT * FROM COURSES WHERE ID=" + std::to_string(id);
    pqxx::result R = dbExecuteReturn(statement);
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

bool dbGetCourseId(int& courseId, std::string name) {
    std::string statement = "SELECT * FROM COURSES WHERE name='" + name + "'";
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    std::stringstream id;
    for (; i < R.size(); ++i) {
        id << R[i][0];
        courseId = stoi(id.str());
    }
    return true;
}

bool dbGetAllCourses(std::vector<int>& courseIds) {
    std::string statement = "SELECT * FROM COURSES";
    pqxx::result R = dbExecuteReturn(statement);
    if (R.empty()) {
            return false;
    }
    pqxx::result::size_type i = 0;
    for (; i < R.size(); ++i) {
        std::stringstream id("");
        int sid;
        id << R[i][0];
        sid = stoi(id.str());
        courseIds.push_back(sid);
    }
    return true;
}

bool dbDeleteCourse(int id) {
	std::string beg = "DELETE FROM COURSES";
	std::string statement = beg +
		" WHERE ID= '" + std::to_string(id) + "';";
    return dbExecute(statement);
}
