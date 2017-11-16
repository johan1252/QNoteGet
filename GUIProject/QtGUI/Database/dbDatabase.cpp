#include "dbDatabase.h"

void createTableQueries() {
		std::string users = "CREATE TABLE USERS("  \
					  "ID SERIAL PRIMARY KEY NOT NULL," \
					  "NAME           TEXT       NOT NULL," \
					  "PASSWORD       TEXT       NOT NULL," \
					  "PATH           TEXT       NOT NULL," \
					  "UPDATE         INT        NOT NULL);";

		std::string courses = "CREATE TABLE COURSES("  \
				  	  "ID       SERIAL PRIMARY KEY  NOT NULL," \
					  "NAME     TEXT             NOT NULL," \
					  "PATH     TEXT             NOT NULL);";

		std::string userCourses = "CREATE TABLE USERCOURSES("  \
					  "ID         SERIAL PRIMARY KEY      NOT NULL," \
					  "COURSEID   INT REFERENCES COURSES(ID)  NOT NULL," \
					  "USERID     INT REFERENCES USERS(ID)    NOT NULL);";

		std::string preferences = "CREATE TABLE PREFERENCES("  \
				 	 	  "ID       SERIAL PRIMARY KEY  NOT NULL," \
						  "COURSEID INT REFERENCES COURSES(ID)  NOT NULL," \
						  "NAME     TEXT             NOT NULL," \
						  "PATH     TEXT             NOT NULL);";

		std::string extensions = "CREATE TABLE EXTENSIONS("  \
					   "ID       SERIAL PRIMARY KEY  NOT NULL," \
					   "NAME     TEXT             NOT NULL);";

		std::string userPreferences = "CREATE TABLE USERPREFERENCES("  \
					   "ID           SERIAL PRIMARY KEY          NOT NULL," \
					   "USERID       INT REFERENCES USERS(ID)        NOT NULL," \
					   "COURSEID     INT REFERENCES COURSES(ID)      NOT NULL," \
					   "PREFERENCEID INT REFERENCES PREFERENCES(ID)  NOT NULL," \
					   "EXTENSIONID  INT REFERENCES EXTENSIONS(ID)   NOT NULL);";

		execute(users);
		execute(courses);
		execute(userCourses);
		execute(preferences);
		execute(extensions);
		execute(userPreferences);
}

//int main(int, char *argv[]) {

//	createTableQueries();
//	updateUser(16,"smith2", "pass2", "home2", 7);
//	std::cout << createUser("smith3", "pass2", "home2", 7);
//	std::string name, password, path;
//	int update;
//	getUser(16, name, password, path, update);
//	std::cout << name << password << path << update;
//	std::cout << createCourse("CISC 340","home");
//	updateCourse(1,"course2", "pathnext");
//	std::string name, path;
//	getCourse(1, name,path);
//	std::cout << name << path;
//	std::vector<int> courses;
//	createUserCourse(20,2);
//	createUserCourse(20,3);
//	deleteUserCourses(18);
//	getUserCourses(18, courses);
//	for (auto i = courses.begin(); i != courses.end(); ++i) {
//	    std::cout << *i << ' ';
//	}
//	createExtension("cpp");
//	deleteExtensionByName("cpp");

//}
