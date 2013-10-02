#ifndef CHESSBOARDCONTROLLER_H
#define CHESSBOARDCONTROLLER_H
#include "strcoord.h"
#include "chessboardwidget.h"
#include <iostream>

class ChessboardController: public QObject{
    Q_OBJECT
public:
    ChessboardController(ChessboardWidget* wdg): QObject(wdg){
        connect(wdg, SIGNAL(cellClicked(StrCoord)), SLOT(cellClicked(StrCoord)));
    }

public slots:
    void cellClicked(const StrCoord& sc){
        std::cout<<sc.toString().toStdString() << std::endl;
    }
};

#endif // CHESSBOARDCONTROLLER_H
