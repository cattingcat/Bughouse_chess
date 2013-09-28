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

RESOURCES += \
    res.qrc

OTHER_FILES += \
    img/w_queen.bmp \
    img/w_king.bmp \
    img/w_king - копия (14).bmp \
    img/w_king - копия (13).bmp \
    img/w_king - копия (12).bmp \
    img/w_king - копия (11).bmp \
    img/w_king - копия (10).bmp \
    img/w_king - копия (9).bmp \
    img/w_king - копия (8).bmp \
    img/w_king - копия (7).bmp \
    img/w_king - копия (6).bmp \
    img/w_king - копия (5).bmp \
    img/w_king - копия (4).bmp \
    img/w_king - копия (3).bmp \
    img/w_king - копия (2).bmp \
    img/chess_fighters.jpg
