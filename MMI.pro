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
    dfs.cpp \
    edge.cpp \
    bfs.cpp \
    components.cpp \
    kruskal.cpp \
    prim.cpp \
    double_tree.cpp

HEADERS  += \
    mainwindow.h \
    graph.h \
    node.h \
    dfs.h \
    edge.h \
    bfs.h \
    components.h \
    kruskal.h \
    prim.h \
    double_tree.h

FORMS    += \
    mainwindow.ui
