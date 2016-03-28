#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:17:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MMI
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
    mainwindow.cpp \
    graph.cpp \
    node.cpp \
    edge.cpp \
    searchabstractbase.cpp \
    bfs.cpp

HEADERS  += \
    mainwindow.h \
    graph.h \
    node.h \
    edge.h \
    searchabstractbase.h \
    bfs.h

FORMS    += \
    mainwindow.ui
