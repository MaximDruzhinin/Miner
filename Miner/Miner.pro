#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T21:17:38
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11
TEMPLATE = subdirs

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Miner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphiccell.cpp \
    cell.cpp \
    icellpainter.cpp \
    cellpainter.cpp \
    minefield.cpp \
    minescene.cpp \
    minercore.cpp \
    miner.cpp

HEADERS  += mainwindow.h \
    graphiccell.h \
    cell.h \
    icellpainter.h \
    cellpainter.h \
    minefield.h \
    minescene.h \
    minercore.h \
    miner.h \
    icell.h 

FORMS    += mainwindow.ui


