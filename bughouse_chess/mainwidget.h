#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Chessboard/chessboardwidget.h"
#include <QPushButton>
#include <iostream>
#include "Chessboard/chessboardcontroller.h"

class MainWidget: public QWidget{
    Q_OBJECT
private:
    QVBoxLayout *_layout;
    ChessboardWidget* _cb1;
    ChessboardWidget* _cb2;
    QPushButton* _btn;

public:
    MainWidget(QWidget* parent = 0): QWidget(parent){
        _layout = new QVBoxLayout(this);
        QHBoxLayout* cb_layout = new QHBoxLayout(this);
        _cb1 = new ChessboardWidget(ChessboardWidget::WHITE, this);
        _cb2 = new ChessboardWidget(ChessboardWidget::BLACK, this);
        _btn = new QPushButton("btn", this);

        this->connect(_btn, SIGNAL(clicked()), SLOT(slot()));

        ChessboardController* cbc = new ChessboardController(_cb1, ChessboardWidget::WHITE);

        cb_layout->addWidget(_cb1);
        cb_layout->addWidget(_cb2);
        _layout->addLayout(cb_layout);
        _layout->addWidget(_btn);
        setLayout(_layout);
    }

private slots:
    void slot(){
        (*_cb1)["C6"] = ChessboardWidget::KING | ChessboardWidget::BLACK;
        _cb1->set("a1", ChessboardWidget::ELEPHANT | ChessboardWidget:: BLACK);
        _cb1->addPathElement("c1");
        _cb1->addPathElement("c2");
        _cb1->addPathElement("c3");
        _cb1->addPathElement("d3");
    }

};

#endif // MAINWIDGET_H
