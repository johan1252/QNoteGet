#ifndef USER_H
#define USER_H

#endif // USER_H

class User;

using namespace std;

class User {
public:
        User(string uName,int pw,string directory,int interval);
        string getUsername();
        int getPassword();
        string getFileDirectory();
        int getUpdateInterval();
        //vector<Course> getSubscribedCourses()
        void setPassword(int pw);
        void setUpdateInterval(int interval);
        //void setCourses(vector<Course> subscribedCourses);s

private:
        string username;
        int passwordHash;
        string fileDirectory;
        int updateInterval;
        //vector<Course> subscribedCourse;
};
