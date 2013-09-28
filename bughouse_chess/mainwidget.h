#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include "chessboard.h"

class MainWidget: public QWidget{
    Q_OBJECT
private:
    QHBoxLayout *layout;
public:
    MainWidget(QWidget* parent = 0): QWidget(parent){
        layout = new QHBoxLayout(this);
        layout->addWidget(new Chessboard);
        layout->addWidget(new Chessboard);
        setLayout(layout);
    }
};

#endif // MAINWIDGET_H
