#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QWidget>
#include <QPaintEvent>
#include <QPaintEngine>
#include <QtGlobal>
#include <QDebug>
#include <QBrush>


class Chessboard: public QWidget{
    Q_OBJECT
public:
    enum ChessmanColor{
        BLACK = 8,
        WHITE = 16
    };

    enum Chessman{
        CHESSMAN_KING = 0,
        CHESSMAN_QUEEN = 1,
        CHESSMAN_PAWN = 2, // пешка
        CHESSMAN_ELEPHANT = 3,
        CHESSMAN_HORSE = 4,
        CHESSMAN_ROOK = 5 // ладья
    };

private:
    uint **field;
    uint pad;

public:

    Chessboard(QWidget* parent = 0): QWidget(parent){
        field = new uint*[8];
        for(int i = 0; i < 8; ++i){
            field[i] = new uint[8];
            field[i][i] = i;
        }

        pad = 25;
    }

    virtual void paintEvent(QPaintEvent *e){
        QPainter p(this);
        int min_sz = minDim();

        QRect r = e->rect();
        p.drawRect(r.x(), r.y(), r.width() - 1, r.height() - 1);
        p.drawRect(0, 0, min_sz, min_sz);

        min_sz -= pad;
        float d = min_sz/8.0;
        for(float i = 0.0; i < min_sz; i += d){
            p.drawLine(i + pad, 0, i + pad, min_sz);
            p.drawLine(pad, i, min_sz + pad, i);
        }
        p.drawLine(pad, min_sz, min_sz + pad, min_sz);




        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){
                uint f = field[i][j];
                QRect r = getRectByCoord(i, j);
                if(i == j)
                    p.fillRect(r, Qt::green);
            }
        }
    }

    QRect getRectByCoord(int x, int y){
        x = x > 7 ? 7 : x < 0 ? 0 : x;
        y = y > 7 ? 7 : y < 0 ? 0 : y;
        int min_sz = minDim();
        min_sz -= pad;
        float d = min_sz / 8.0;
        //return QRect(x * d + pad, min_sz - d - (y * d), d, d);
        return QRect(x * d + pad + 1, min_sz - d - (y * d) + 1, d-1, d-1 );
    }



    int minDim(){
        return (width() > height() ? height() : width()) - 1;
    }
};

#endif // CHESSBOARD_H
