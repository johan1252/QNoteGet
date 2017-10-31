#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T11:49:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    signinform.cpp \
    signupform.cpp

HEADERS  += mainwindow.h \
    signinform.h \
    signupform.h

FORMS    += mainwindow.ui \
    signinform.ui \
    signupform.ui

RESOURCES += \
    images.qrc \
    examplefolderstructure.qrc


