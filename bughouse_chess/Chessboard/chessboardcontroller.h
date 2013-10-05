#ifndef CHESSBOARDCONTROLLER_H
#define CHESSBOARDCONTROLLER_H
#include "strcoord.h"
#include "chessboardwidget.h"
#include <iostream>

class ChessboardController: public QObject{
    Q_OBJECT
    ChessboardWidget* _wdg;
    ChessboardWidget::ChessmanColor _my_side;

public:
    ChessboardController(ChessboardWidget* wdg, ChessboardWidget::ChessmanColor color): QObject(wdg){
        _wdg = wdg;
        _my_side = color;
        connect(wdg, SIGNAL(cellClicked(StrCoord, QMouseEvent)), SLOT(cellClicked(StrCoord, QMouseEvent)));
        initChessmans();
    }

    void initChessmans(){
        StrCoord coord("a2");
        do{
            _wdg->set(coord, _my_side | ChessboardWidget::PAWN);
        }while(coord.right());
    }

public slots:
    void cellClicked(const StrCoord& sc, const QMouseEvent& e){
        uint figure = _wdg->get(sc);
        bool select = _wdg->selected();
        if(select){
            _wdg->set(sc, _wdg->get(_wdg->selectedCell()));
            _wdg->removeSelected();
        } else {
            _wdg->setSelect(sc);
        }

    }
};

#endif // CHESSBOARDCONTROLLER_H
