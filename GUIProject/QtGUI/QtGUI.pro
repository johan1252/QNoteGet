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
    database.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    database.h \
    user.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc \
    testingdirectories.qrc


