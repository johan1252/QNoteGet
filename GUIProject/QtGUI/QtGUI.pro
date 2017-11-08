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

INCLUDEPATH += /usr/local/Cellar/libpqxx/4.0.1_2/include

# Johan's computer needs the -L paths. Shouldn't harm others if not found at that location.
LIBS += -L/usr/local/Cellar/libpqxx/4.0.1_2/lib/ -lpqxx -L/usr/local/Cellar/libpq/9.6.5/lib/ -lpq -lcurl -L/usr/local/Cellar/boost/1.65.1/lib/ -lboost_system -lboost_regex -lboost_filesystem

SOURCES += main.cpp\
        mainwindow.cpp \
    signinform.cpp \
    signupform.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    signinform.h \
    signupform.h \
    database.h

FORMS    += mainwindow.ui \
    signinform.ui \
    signupform.ui

RESOURCES += \
    images.qrc \
    testingdirectories.qrc


