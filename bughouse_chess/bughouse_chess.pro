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
    img/w_king - ����� (14).bmp \
    img/w_king - ����� (13).bmp \
    img/w_king - ����� (12).bmp \
    img/w_king - ����� (11).bmp \
    img/w_king - ����� (10).bmp \
    img/w_king - ����� (9).bmp \
    img/w_king - ����� (8).bmp \
    img/w_king - ����� (7).bmp \
    img/w_king - ����� (6).bmp \
    img/w_king - ����� (5).bmp \
    img/w_king - ����� (4).bmp \
    img/w_king - ����� (3).bmp \
    img/w_king - ����� (2).bmp \
    img/chess_fighters.jpg
