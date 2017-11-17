#include "dbDatabase.h"

void dbCreateTableQueries() {
		std::string users = "CREATE TABLE USERS("  \
					  "ID SERIAL PRIMARY KEY NOT NULL," \
					  "NAME           TEXT       NOT NULL," \
                      "PASSWORD       INT       NOT NULL," \
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

        dbExecute(users);
        dbExecute(courses);
        dbExecute(userCourses);
        dbExecute(preferences);
        dbExecute(extensions);
        dbExecute(userPreferences);
}

void dbCreatePreDefinedCourses() {
    std::string course320 = "INSERT INTO COURSES("  \
                  "NAME,PATH)" \
                  "VALUES ('CISC320','http://research.cs.queensu.ca/home/cisc320/')";

    std::string course451 = "INSERT INTO COURSES("  \
                  "NAME,PATH)" \
                  "VALUES ('ELEC451','http://post.queensu.ca/~nm7/ELEC451/')";

    std::string course124 = "INSERT INTO COURSES("  \
                  "NAME,PATH)" \
                  "VALUES ('CISC124','http://research.cs.queensu.ca/home/cisc124w/')";

    std::string course320Preferences = "INSERT INTO PREFERENCES("  \
                                       "COURSEID," \
                                       "NAME," \
                                       "PATH)" \
                                       "VALUES ('1','Assignments','http://research.cs.queensu.ca/home/cisc320/Fall2017/Assignments.html')" \
                                       ",('1','Excercise','http://research.cs.queensu.ca/home/cisc320/Fall2017/Exercises.html')" \
                                       ",('1','Lecture Notes','http://research.cs.queensu.ca/home/cisc320/Fall2017/LectureContent/LectureNotes.html')";

    std::string course451Preferences = "INSERT INTO PREFERENCES("  \
                                       "COURSEID," \
                                       "NAME," \
                                       "PATH)" \
                                       "VALUES ('2','Content','http://post.queensu.ca/~nm7/ELEC451/protected/')";

    std::string course124Preferences = "INSERT INTO PREFERENCES("  \
                                       "COURSEID," \
                                       "NAME," \
                                       "PATH)" \
                                       "VALUES ('3','Assignments','http://research.cs.queensu.ca/home/cisc124w/Fall2017/Assignments.html')" \
                                       ",('3','Excercises','http://research.cs.queensu.ca/home/cisc124w/Fall2017/Exercises.html')" \
                                       ",('3','Lecture Notes','http://research.cs.queensu.ca/home/cisc124w/Fall2017/LectureContent/LectureNotes.html')";

    dbExecute(course320);
    dbExecute(course451);
    dbExecute(course124);
    dbExecute(course320Preferences);
    dbExecute(course451Preferences);
    dbExecute(course124Preferences);
}

int dbRunDatabase() {

// Uncomment the following two lines to "refresh" the database.
    /*
    createTableQueries();
    dbCreatePreDefinedCourses();
    */

//  Extra commands for debugging DB.
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
    return 0;
}
