#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:17:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MMI
TEMPLATE = app


SOURCES += main.cpp\
    graphview.cpp \
    graphmodel.cpp \
    graphcontroller.cpp

HEADERS  += \
    graphview.h \
    graphmodel.h \
    graphcontroller.h

FORMS    += mainwindow.ui
