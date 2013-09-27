#-------------------------------------------------
#
# Project created by QtCreator 2013-09-27T17:51:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bughouse_chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessboard.cpp \
    mainwidget.cpp

HEADERS  += mainwindow.h \
    chessboard.h \
    mainwidget.h

FORMS    += mainwindow.ui
