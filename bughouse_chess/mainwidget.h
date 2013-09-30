#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "chessboard.h"
#include <QPushButton>
#include <iostream>

class MainWidget: public QWidget{
    Q_OBJECT
private:
    QVBoxLayout *_layout;
    Chessboard* _cb1;
    Chessboard* _cb2;
    QPushButton* _btn;

public:
    MainWidget(QWidget* parent = 0): QWidget(parent){
        _layout = new QVBoxLayout(this);
        QHBoxLayout* cb_layout = new QHBoxLayout(this);
        _cb1 = new Chessboard(this);
        _cb2 = new Chessboard(this);
        _btn = new QPushButton("btn", this);

        this->connect(_btn, SIGNAL(clicked()), SLOT(slot()));

        cb_layout->addWidget(_cb1);
        cb_layout->addWidget(_cb2);
        _layout->addLayout(cb_layout);
        _layout->addWidget(_btn);
        setLayout(_layout);
    }

private slots:
    void slot(){        
        bool b = _cb1->lock();
        if(!b)
            _cb1->unlock();
    }
};

#endif // MAINWIDGET_H
