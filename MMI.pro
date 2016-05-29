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
    nearest_neighbor.cpp \
    double_tree.cpp \
    branch_and_bound.cpp \
    tsp_bruteforce.cpp \
    bellman_ford.cpp \
    edmonds_karp.cpp \
    dijkstra.cpp

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
    nearest_neighbor.h \
    double_tree.h \
    branch_and_bound.h \
    tsp_bruteforce.h \
    bellman_ford.h \
    edmonds_karp.h \
    dijkstra.h

FORMS    += \
    mainwindow.ui
