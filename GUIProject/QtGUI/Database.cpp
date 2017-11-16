#include "Database.h"

pqxx::connection DBconnection("dbname=d977ktitdsgsqp user=qohiknwjuwjacn password=f1ef440e6c254a34c4e638e3dbca1abb9bac8c14acd110309b9955bc8b51af3a host=ec2-50-17-201-204.compute-1.amazonaws.com port=5432 requiressl=1");

/*
 * Generic function that can make a row in ANY DB table.
 * Currently used to insert rows into user table, and usercourses table.
 */
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

/*
 * Function to create a row in users DB table.
 */
void Database::dbCreateUserRow(const string username, int passHash, string path, int updateInterval) {

    vector<string> userTableFields = {"username","password","filedirectory","updateinterval"};
    vector<string> userTablevalues = {username,to_string(passHash),path,to_string(updateInterval)};

    //TODO: update this to real table name
    string tableName = "userqt";

    createTableRow(tableName, userTableFields, userTablevalues);
}

/*
 * Function to end database connection.
 */
void Database::dbEndDatabaseConnection() {
    DBconnection.disconnect();
}

/*
 *  Returns the password associated with a username, or -1 if the username does not exist
 */
int Database::dbGetPasswordForUsername(string username){
    int password = -1;
    try {
      pqxx::work txn(DBconnection);

      string sql = "SELECT password FROM userqt WHERE username = '" + username + "'";

      // For debuggin sql statement
      //cout << sql << endl;

      pqxx::result r = txn.exec(sql);
      // Iterate through result to get password
      for (unsigned long rownum=0; rownum < r.size(); ++rownum)
       {
         const pqxx::result::tuple row = r[rownum];

         for (unsigned int colnum=0; colnum < row.size(); ++colnum)
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

/*
 * Function to get a course's DB courseid. To be used in future DB calls.
 */
int Database::dbGetCourseId(string courseName){
    int courseId = -1;
    try {
      pqxx::work txn(DBconnection);

      string sql = "SELECT courseid FROM courses WHERE coursename = '" + courseName + "'";

      // For debuggin sql statement
      //cout << sql << endl;

      pqxx::result r = txn.exec(sql);

      // Iterate through result to get courseid (should only match one because courseName is "UNIQUE" in DB)
      for (unsigned long rownum=0; rownum < r.size(); ++rownum)
       {
         const pqxx::result::tuple row = r[rownum];

         for (unsigned int colnum=0; colnum < row.size(); ++colnum)
         {
           const pqxx::result::field field = row[colnum];
           courseId = stoi(field.c_str());
         }
       }
      txn.commit();
    }
    catch (const exception &e) {
      cout << "Could not get courseId for :" << courseName << " " << e.what();
      return courseId;
     }
    return courseId;
}

/*
 * Function to get a user's DB userid from database.
 */
int Database::dbGetUserId(string userName){
    int userId = -1;
    try {
      pqxx::work txn(DBconnection);

      string sql = "SELECT userid FROM userqt WHERE username = '" + userName + "'";

      // For debuggin sql statement
      //cout << sql << endl;

      pqxx::result r = txn.exec(sql);

      // Iterate through result to get userid (should only match one because username is "UNIQUE" in DB)
      for (unsigned long rownum=0; rownum < r.size(); ++rownum)
       {
         const pqxx::result::tuple row = r[rownum];

         for (unsigned int colnum=0; colnum < row.size(); ++colnum)
         {
           const pqxx::result::field field = row[colnum];
           userId = stoi(field.c_str());
         }
       }
      txn.commit();
    }
    catch (const exception &e) {
      cout << "Could not get userId for :" << userName << " " << e.what();
      return userId;
     }
    return userId;
}

/*
 * Fetch a course URL/Path from the DB using course name.
 */
string Database::dbGetCoursePath(string courseName){
    string coursePath = "";
    try {
      pqxx::work txn(DBconnection);

      string sql = "SELECT coursepath FROM courses WHERE coursename = '" + courseName + "'";

      // For debuggin sql statement
      //cout << sql << endl;

      pqxx::result r = txn.exec(sql);

      // Iterate through result to get coursePath (should only match one because courseName is "UNIQUE" in DB)
      for (unsigned long rownum=0; rownum < r.size(); ++rownum)
      {
         const pqxx::result::tuple row = r[rownum];

         for (unsigned int colnum=0; colnum < row.size(); ++colnum)
         {
           const pqxx::result::field field = row[colnum];
           coursePath = field.c_str();
         }
       }
      txn.commit();
    }
    catch (const exception &e) {
      cout << "Could not get coursePath for :" << courseName << " " << e.what();
      return coursePath;
    }
    return coursePath;
}

/*
 * Create an entry in usercourses table between a username and a course object.
 */
void Database::dbCreateUserCoursesRow(string username, Course userCourse) {
    int courseId = dbGetCourseId(userCourse.getCourseName());
    int userId = dbGetUserId(username);

    if (courseId == -1 || userId == -1){
        cout << "ERROR, courseId or userId could not be found. UserId: " << userId << " CourseId: " << courseId << endl;
    }

    vector<string> userTableFields = {"userid","courseid"};
    vector<string> userTablevalues = {to_string(userId),to_string(courseId)};

    string tableName = "usercourses";

    createTableRow(tableName, userTableFields, userTablevalues);
}
