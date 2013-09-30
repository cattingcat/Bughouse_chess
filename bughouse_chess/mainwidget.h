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
        _cb1 = new Chessboard(Chessboard::WHITE, this);
        _cb2 = new Chessboard(Chessboard::BLACK, this);
        _btn = new QPushButton("btn", this);

        this->connect(_btn, SIGNAL(clicked()), SLOT(slot()));
        this->connect(_cb1, SIGNAL(cellClicked(QString)), SLOT(cellClicked(QString)));

        cb_layout->addWidget(_cb1);
        cb_layout->addWidget(_cb2);
        _layout->addLayout(cb_layout);
        _layout->addWidget(_btn);
        setLayout(_layout);
    }

private slots:
    void slot(){
        (*_cb1)["A1"] = Chessboard::CHESSMAN_KING | Chessboard::WHITE;
        (*_cb1)["C6"] = Chessboard::CHESSMAN_KING | Chessboard::BLACK;
        _cb1->addPathElement("c1");
        _cb1->addPathElement("c2");
        _cb1->addPathElement("c3");
        _cb1->addPathElement("d3");
    }

    void cellClicked(QString s){
        std::cout << s.toStdString() << std::endl;
    }

};

#endif // MAINWIDGET_H
