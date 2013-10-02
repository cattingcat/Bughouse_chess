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
    mainwidget.cpp \
    Chessboard/chessboardwidget.cpp \
    Chessboard/strcoord.cpp \
    Chessboard/chessboardcontroller.cpp

HEADERS  += mainwindow.h \
    mainwidget.h \
    Chessboard/chessboardwidget.h \
    Chessboard/strcoord.h \
    Chessboard/chessboardcontroller.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    img/w_queen.bmp \
    img/w_king.bmp \
    img/chess_fighters.jpg
