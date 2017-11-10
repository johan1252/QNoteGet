#pragma once

#include <pqxx/pqxx>
#include <string>
#include <exception>
#include <iostream>
#include <vector>

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

    private:
        static bool createTableRow(const string tableName, vector<string> fields, vector<string> values);
};
