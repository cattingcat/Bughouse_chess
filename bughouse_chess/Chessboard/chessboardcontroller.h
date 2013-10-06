#ifndef CHESSBOARDCONTROLLER_H
#define CHESSBOARDCONTROLLER_H
#include "strcoord.h"
#include "chessboardwidget.h"
#include <iostream>
#include <QList>

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

        _wdg->set("A1", _my_side | ChessboardWidget::ROOK);
        _wdg->set("H1", _my_side | ChessboardWidget::ROOK);

        _wdg->set("B1", _my_side | ChessboardWidget::ELEPHANT);
        _wdg->set("G1", _my_side | ChessboardWidget::ELEPHANT);

        _wdg->set("C1", _my_side | ChessboardWidget::HORSE);
        _wdg->set("F1", _my_side | ChessboardWidget::HORSE);

        _wdg->set("D1", _my_side | ChessboardWidget::QUEEN);
        _wdg->set("E1", _my_side | ChessboardWidget::KING);
    }

#define IS(x) ((mask & x) == x)
    QList<ChessboardWidget::Coord> getPossiblePath(){
        StrCoord coord = _wdg->selectedCell();
        uint mask = _wdg->get(coord);
        QList<ChessboardWidget::Coord>  res;

        if(IS(ChessboardWidget::PAWN)){
            if(coord.y() == 1){
                StrCoord tmp = coord;
                tmp.up();
                res.push_back(tmp);
                tmp.up();
                res.push_back(tmp);
            } else if(coord.hasUp()){
                StrCoord tmp = coord;
                tmp.up();
                res.push_back(tmp);
            }
            return res;
        } else if(IS(ChessboardWidget::ROOK)){
            return res;
        } else if(IS(ChessboardWidget::ELEPHANT)){
            return res;
        } else if(IS(ChessboardWidget::HORSE)){
            return res;
        } else if(IS(ChessboardWidget::QUEEN)){
            return res;
        } else { // ChessboardWidget::KING
            return res;
        }
    }
#undef IS

public slots:
    void cellClicked(const StrCoord& sc, const QMouseEvent& e){
        uint figure = _wdg->get(sc);
        bool select = _wdg->selected();
        if(select){
            _wdg->set(sc, _wdg->get(_wdg->selectedCell()));
            _wdg->removeSelected();
            _wdg->clearPath();
        } else if((_wdg->get(sc) & _my_side) == _my_side){
            _wdg->setSelect(sc);
            _wdg->setPath(getPossiblePath());
        } else {
            return;
        }

    }
};

#endif // CHESSBOARDCONTROLLER_H
