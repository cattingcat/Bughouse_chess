#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0): QMainWindow(parent)
    {
        setMinimumHeight(300);
        setMinimumWidth(500);
        setCentralWidget(new MainWidget(this));
    }

    ~MainWindow()
    {
    }
    
private:

};

#endif // MAINWINDOW_H
