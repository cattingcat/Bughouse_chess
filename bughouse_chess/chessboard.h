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
    QPoint *selected_cell;

public:
    Chessboard(QWidget* parent = 0): QWidget(parent){
        field = new uint*[8];
        for(int i = 0; i < 8; ++i){
            field[i] = new uint[8];
            field[i][i] = i;
        }
        pad = 25;
    }

    virtual ~Chessboard(){
        for(int i = 0; i < 8; ++i){
            delete field[i];
        }
        delete field;
    }

protected:
    virtual void paintEvent(QPaintEvent *e){
        QPainter painter(this);
        int min_sz = minDim();

        QRect widget_rect = e->rect();
        painter.drawRect(widget_rect);
        painter.drawRect(0, 0, min_sz, min_sz);

        min_sz -= pad;
        int d = min_sz / 8;
        for(int i = 0; i < min_sz; i += d){
            painter.drawLine(i + pad, 0, i + pad, min_sz);
            painter.drawLine(pad, i, min_sz + pad, i);
        }
        painter.drawLine(pad, min_sz, min_sz + pad, min_sz);


        for(int i = 0; i < 8; ++i){
            bool flag = i % 2 == 0;
            for(int j = 0; j < 8; ++j){
                QRect cr = getRectByCoord(i, j);
                bool flag2 = j % 2 == 0;
                if(flag && flag2  || (!flag) && (!flag2)){
                    painter.fillRect(cr, Qt::blue);
                }
            }
        }

        if(selected_cell){
            QRect cell = getRectByCoord(*selected_cell);
            qDebug() << cell;
            painter.drawPixmap(cell, QPixmap(":/img/w_king.png"));
        }

    }

    virtual void mousePressEvent(QMouseEvent *e){
        int x = e->x();
        int y = e->y();
        int min_sz = minDim();
        if(x > min_sz || y > min_sz)
            return;
        int d = (min_sz - pad) / 8;
        int x_cell = (x - pad) / d;
        int y_cell = 7 - (y / d);
        if(selected_cell)
            delete selected_cell;
        selected_cell = new QPoint(x_cell, y_cell);
        qDebug() << *selected_cell;
        repaint();
    }

    QRect getRectByCoord(QPoint p){
        return getRectByCoord(p.x(), p.y());
    }

    QRect getRectByCoord(int x, int y){
        x = x > 7 ? 7 : x < 0 ? 0 : x;
        y = y > 7 ? 7 : y < 0 ? 0 : y;
        int min_sz = minDim();
        min_sz -= pad;
        float d = min_sz / 8.0;
        //return QRect(x * d + pad, min_sz - d - (y * d), d, d);
        return QRect(x * d + pad + 1, min_sz - d - (y * d) + 1, d - 1, d - 1);
    }



    int minDim(){
        int dim = (width() > height() ? height() : width()) - 1;
        dim -= pad;
        int tmp = dim / 8.0;
        return tmp * 8 + pad;
    }

signals:
    void cellClicked(int x, int y);

};

#endif // CHESSBOARD_H
