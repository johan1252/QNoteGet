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
    Course.cpp \
    Database.cpp \
    Main.cpp \
    Mainwindow.cpp \
    User.cpp \
    CourseCategory.cpp \
    Backend.cpp \
    Credentials.cpp

HEADERS  += \
    Course.h \
    Database.h \
    Mainwindow.h \
    User.h \
    CourseCategory.h \
    Backend.h \
    Credentials.h

FORMS    += \
    Mainwindow.ui \
    Credentials.ui

RESOURCES += \
    images.qrc \
    testingdirectories.qrc


