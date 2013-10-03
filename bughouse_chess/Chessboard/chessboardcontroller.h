#ifndef CHESSBOARDCONTROLLER_H
#define CHESSBOARDCONTROLLER_H
#include "strcoord.h"
#include "chessboardwidget.h"
#include <iostream>

class ChessboardController: public QObject{
    Q_OBJECT
    ChessboardWidget* _wdg;

public:
    ChessboardController(ChessboardWidget* wdg): QObject(wdg){
        _wdg = wdg;
        connect(wdg, SIGNAL(cellClicked(StrCoord, QMouseEvent)), SLOT(cellClicked(StrCoord, QMouseEvent)));
    }

public slots:
    void cellClicked(const StrCoord& sc, const QMouseEvent& e){
        std::cout<<sc.toString().toStdString() << std::endl;
        if(_wdg->get(sc) == 0)
            _wdg->set(sc, ChessboardWidget::CHESSMAN_KING | ChessboardWidget::WHITE);
        else
            _wdg->set(sc,0);

    }
};

#endif // CHESSBOARDCONTROLLER_H
