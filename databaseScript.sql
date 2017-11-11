/* Drop all existing tables (order matters) to do a clean slate */
DROP TABLE userqt;
DROP TABLE usercourses;
DROP TABLE courses;

/* Re-create all the tables */
CREATE TABLE userqt (userid SERIAL PRIMARY KEY NOT NULL, username TEXT UNIQUE NOT NULL, password INT NOT NULL, fileDirectory TEXT NOT NULL, updateInterval INT NOT NULL);

CREATE TABLE courses (courseid SERIAL PRIMARY KEY NOT NULL, coursename TEXT UNIQUE NOT NULL, coursepath TEXT NOT NULL);

CREATE TABLE usercourses (userid INT NOT NULL, courseid INT REFERENCES courses(courseid) NOT NULL);

/* Add pre-defined course information to courses table */
INSERT INTO courses (coursename,coursepath) VALUES ('CISC320','http://research.cs.queensu.ca/home/cisc320/');

INSERT INTO courses (coursename,coursepath) VALUES ('ELEC451','http://post.queensu.ca/~nm7/ELEC451/');

/* Will need to switch out this course */
INSERT INTO courses (coursename,coursepath) VALUES ('CISC221','http://post.queensu.ca/~nm7/CISC221/');