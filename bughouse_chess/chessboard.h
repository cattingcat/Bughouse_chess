#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QWidget>
#include <QPaintEvent>
#include <QPaintEngine>
#include <QtGlobal>
#include <QDebug>


class Chessboard: public QWidget{
    Q_OBJECT
public:
    enum Chessman{
        CHESSMAN_KING,
        CHESSMAN_QUEEN,
        CHESSMAN_PAWN, // пешка
        CHESSMAN_ELEPHANT,
        CHESSMAN_HORSE,
        CHESSMAN_ROOK // ладья
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

        QRect sr = fillCell(2, 2);
        qDebug() << "fc " << sr;
        //p.drawEllipse(sr.x(), sr.y(), sr.width(), sr.height());
        //p.drawEllipse(0, 0, 5, 5);
    }

    QRect fillCell(int x, int y){
        QPainter p(this);
        int min_sz = minDim();
        float d = min_sz / 8.0;
        float cell_sz = (min_sz - pad) / 8.0;
        return QRect(x * d + pad, min_sz - (y * d + pad), cell_sz, cell_sz);
    }

    int minDim(){
        return (width() > height() ? height() : width()) - 1;
    }
};

#endif // CHESSBOARD_H
