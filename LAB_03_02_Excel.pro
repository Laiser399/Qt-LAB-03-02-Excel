#-------------------------------------------------
#
# Project created by QtCreator 2018-10-12T22:25:08
#
#-------------------------------------------------

QT       += core gui xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LAB_03_02_Excel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp \
    schedule.cpp \
    TeachersList.cpp \
    tableview.cpp

HEADERS  += mainwindow.h \
    tablemodel.h \
    schedule.h \
    TeachersList.h \
    tableview.h

FORMS    += mainwindow.ui
