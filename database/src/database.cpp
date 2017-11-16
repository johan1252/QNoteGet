#include "createTable.h"

void createTableQueries(pqxx::connection& c) {
		std::string users = "CREATE TABLE USERS("  \
					  "ID INT SERIAL PRIMARY KEY NOT NULL," \
					  "NAME           TEXT       NOT NULL," \
					  "PASSWORD       TEXT       NOT NULL," \
					  "PATH           TEXT       NOT NULL," \
					  "UPDATE         TIMESTAMP  NOT NULL);";

		std::string courses = "CREATE TABLE COURSES("  \
				  	  "ID       INT PRIMARY KEY  NOT NULL," \
					  "PATH     TEXT             NOT NULL," \
					  "NAME     TEXT             NOT NULL);";

		std::string userCourses = "CREATE TABLE USERCOURSES("  \
					  "ID         INT SERIAL PRIMARY KEY      NOT NULL," \
					  "COURSEID   INT REFERENCES COURSES(ID)  NOT NULL," \
					  "USERID     INT REFERENCES USERS(ID)    NOT NULL);";

		std::string preferences = "CREATE TABLE PREFERENCES("  \
				      "ID         INT SERIAL PRIMARY KEY            NOT NULL," \
					  "PATH       TEXT                              NOT NULL," \
					  "COURSEID   INT REFERENCES COURSES(COURSEID)  NOT NULL," \
					  "USERID     INT REFERENCES USERS(USERID)      NOT NULL);";

		std::string extensions = "CREATE TABLE EXTENSIONS("  \
					   "ID       INT PRIMARY KEY  NOT NULL," \
					   "NAME     TEXT             NOT NULL);";

		std::string userPreferences = "CREATE TABLE USERPREFERENCES("  \
					   "ID           INT SERIAL PRIMARY KEY          NOT NULL," \
					   "USERID       INT REFERENCES USERS(ID)        NOT NULL," \
					   "COURSEID     INT REFERENCES COURSES(ID)      NOT NULL," \
					   "PREFERENCEID INT REFERENCES PREFERENCES(ID)  NOT NULL," \
					   "EXTENSIONID  INT REFERENCES EXTENSIONS(ID)   NOT NULL);";
		createTable(c, userPreferences);

}

int main(int, char *argv[]) {
	pqxx::connection c("dbname=d977ktitdsgsqp user=qohiknwjuwjacn password=f1ef440e6c254a34c4e638e3dbca1abb9bac8c14acd110309b9955bc8b51af3a host=ec2-50-17-201-204.compute-1.amazonaws.com port=5432 requiressl=1");
<<<<<<< HEAD
=======
	std::string sql = "CREATE TABLE TESTMAYTHA("  \
		      "ID INT PRIMARY KEY     NOT NULL," \
		      "NAME           TEXT    NOT NULL," \
		      "PASSWORD       TEXT     NOT NULL);";
>>>>>>> d33a54edca79a21046ba343ebbcd8e96509ba3ae

	std::string sql = "";
	c.disconnect();
}
