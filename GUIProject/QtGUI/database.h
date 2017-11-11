#pragma once

#include <pqxx/pqxx>
#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include "Course.h"

using namespace std;

// Class Declarations
class Database;

/*
 * Database class
 */
class Database{
    public:
        static void dbCreateUserRow(const string username, int passHash, string path, int updateInterval);
        static void dbEndDatabaseConnection();
        static int dbGetPasswordForUsername(string username);
        static string dbGetCoursePath(string courseName);
        static void dbCreateUserCoursesRow(string username, Course userCourse);

    private:
        static bool createTableRow(const string tableName, vector<string> fields, vector<string> values);
        static int dbGetCourseId(string courseName);
        static int dbGetUserId(string courseName);
};
