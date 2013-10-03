#ifndef CHESSBOARDCONTROLLER_H
#define CHESSBOARDCONTROLLER_H
#include "strcoord.h"
#include "chessboardwidget.h"
#include <iostream>

class ChessboardController: public QObject{
    Q_OBJECT
    ChessboardWidget* _wdg;
    ChessboardWidget::ChessmanColor _color;

public:
    ChessboardController(ChessboardWidget* wdg, ChessboardWidget::ChessmanColor color): QObject(wdg){
        _wdg = wdg;
        _color = color;
        connect(wdg, SIGNAL(cellClicked(StrCoord, QMouseEvent)), SLOT(cellClicked(StrCoord, QMouseEvent)));
        initChessmans();
    }

    void initChessmans(){
        StrCoord coord("a2");
        do{
            _wdg->set(coord, _color | ChessboardWidget::PAWN);
        }while(coord.right());
    }

public slots:
    void cellClicked(const StrCoord& sc, const QMouseEvent& e){
        std::cout<<sc.toString().toStdString() << std::endl;
        if(_wdg->get(sc) == 0)
            _wdg->set(sc, ChessboardWidget::ELEPHANT | ChessboardWidget::BLACK);
        else
            _wdg->set(sc,0);

    }
};

#endif // CHESSBOARDCONTROLLER_H
