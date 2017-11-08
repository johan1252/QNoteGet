#pragma once

#include <pqxx/pqxx>
#include <string>
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

// Class Declarations
class database;

/*
 * Database class
 */
class database{
    public:
        static void dbCreateUserRow(const string username, int passHash, string path, int updateInterval);
        static void dbEndDatabaseConnection();
    private:
        static bool createTableRow(const string tableName, vector<string> fields, vector<string> values);
};
