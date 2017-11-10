#pragma once

class Course;

using namespace std;

class Course {
public:
        //TODO: Add CourseCategory Class and update constructor for Course class.
        //Course(string courseName, string rootUrl,vector<CourseCategory> categories);
        Course(string courseName, string rootUrl);

        string getCourseName();
        //vector<CourseCategory> getCategories();
        string getRootUrl();
        void setRootUrl(string path);
        //void setCategories(CourseCategory category);
        //void addCategory(CourseCategory category);
        //void removeCategory(CourseCategory category);

private:
        string courseName;
        string rootUrl;
        //vector<CourseCategory> categories;
};
