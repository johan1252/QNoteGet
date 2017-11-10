#include "Database.h"

pqxx::connection DBconnection("dbname=d977ktitdsgsqp user=qohiknwjuwjacn password=f1ef440e6c254a34c4e638e3dbca1abb9bac8c14acd110309b9955bc8b51af3a host=ec2-50-17-201-204.compute-1.amazonaws.com port=5432 requiressl=1");

bool Database::createTableRow(string tableName, vector<string> fields, vector<string> values) {
  try {
    pqxx::work txn(DBconnection);

    string sql = "INSERT INTO " + tableName + " (";

    int size = fields.size();
    int count = 1;

    // Iterate over fields adding them to SQL statement.
    for (auto field : fields) {
        sql += field;

        // Add a comma between fields, except for the last field
        if (count < size) {
            count += 1;
            sql += ",";
        }
    }

    sql += ") VALUES (";

    size = values.size();
    count = 1;
    // Iterate over values adding them to SQL statement.
    for (auto value : values) {
        sql += "'" + value + "'";

        // Add a comma between values, except for the last value
        if (count < size) {
            count += 1;
            sql += ",";
        }
    }

    sql += ")";

    // For debuggin sql statement
    //cout << sql << endl;

    pqxx::result r = txn.exec(sql);
    txn.commit();
  }
  catch (const exception &e) {
    cout << "Could not update table :" << tableName << " " << e.what();
    return false;
   }
  return true;
}


void Database::dbCreateUserRow(const string username, int passHash, string path, int updateInterval) {

    vector<string> userTableFields = {"name","password","filedirectory","updateinterval"};
    vector<string> userTablevalues = {username,to_string(passHash),path,to_string(updateInterval)};

    //TODO: update this to real table name
    string tableName = "userqt";

    createTableRow(tableName, userTableFields, userTablevalues);
}

void Database::dbEndDatabaseConnection() {
    DBconnection.disconnect();
}

// Returns the password associated with a username, or -1 if the username does not exist
int Database::dbGetPasswordForUsername(string username){
    int password = -1;
    try {
      pqxx::work txn(DBconnection);

      string sql = "SELECT password FROM userqt WHERE name = '" + username + "'";

      // For debuggin sql statement
      //cout << sql << endl;

      pqxx::result r = txn.exec(sql);
      // Iterate through result to get password
      for (int rownum=0; rownum < r.size(); ++rownum)
       {
         const pqxx::result::tuple row = r[rownum];

         for (int colnum=0; colnum < row.size(); ++colnum)
         {
           const pqxx::result::field field = row[colnum];
           password = stoi(field.c_str());
         }
       }
      txn.commit();
    }
    catch (const exception &e) {
      cout << "Could not get password for :" << username << " " << e.what();
      return password;
     }
    return password;
}
