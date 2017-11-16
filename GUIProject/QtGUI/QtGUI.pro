#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T11:49:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = QtGUI
TEMPLATE = app

# Johan include path for libpqxx
INCLUDEPATH += /usr/local/Cellar/libpqxx/4.0/include

# Marshall include path for libpqxx
INCLUDEPATH += /usr/local/Cellar/libpqxx/4.0.1_2/include

# Johan include path for boost
INCLUDEPATH += /usr/local/Cellar/boost/1.65.1/include

# Johan's & Marshall's computer needs the -L paths. Shouldn't harm others if not found at that location.
LIBS += -L/usr/local/Cellar/libpqxx/4.0/lib/ -L/usr/local/Cellar/libpqxx/4.0.1_2/lib/ -lpqxx -L/usr/local/Cellar/libpq/9.6.5/lib/ -lpq -lcurl -L/usr/local/Cellar/boost/1.65.1/lib/ -lboost_system -lboost_regex -lboost_filesystem

SOURCES +=\
    Database/dbCourse.cpp \
    Database/dbDatabase.cpp \
    Database/dbExecute.cpp \
    Database/dbExtension.cpp \
    Database/dbPreference.cpp \
    Database/dbUser.cpp \
    Database/dbUserCourse.cpp \
    Database/dbUserPreference.cpp \
    Backend.cpp \
    Course.cpp \
    CourseCategory.cpp \
    Credentials.cpp \
    Database.cpp \
    Main.cpp \
    Mainwindow.cpp \
    User.cpp


HEADERS  += \
    Database/dbCourse.h \
    Database/dbDatabase.h \
    Database/dbExecute.h \
    Database/dbExtension.h \
    Database/dbPreference.h \
    Database/dbUser.h \
    Database/dbUserCourse.h \
    Database/dbUserPreference.h \
    Backend.h \
    Course.h \
    CourseCategory.h \
    Credentials.h \
    Database.h \
    Mainwindow.h \
    User.h


FORMS    += \
    Mainwindow.ui \
    Credentials.ui

RESOURCES += \
    images.qrc \
    testingdirectories.qrc


