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
        BLACK = 64,
        WHITE = 128
    };
    enum Chessman{
        CHESSMAN_KING = 1,
        CHESSMAN_QUEEN = 2,
        CHESSMAN_PAWN = 4, // пешка
        CHESSMAN_ELEPHANT = 8,
        CHESSMAN_HORSE = 16,
        CHESSMAN_ROOK = 32 // ладья
    };

private:
    uint **_field;
    uint _pad;
    QPoint *selected_cell;

    QColor _black_cell;
    QColor _white_cell;

public:
    Chessboard(QWidget* parent = 0): QWidget(parent){
        _field = new uint*[8];
        for(int i = 0; i < 8; ++i){
            _field[i] = new uint[8];
            _field[i][i] = i;
        }
        _pad = 25;
        _black_cell = Qt::black;
        _white_cell = Qt::white;
    }

    virtual ~Chessboard(){
        for(int i = 0; i < 8; ++i){
            delete _field[i];
        }
        delete _field;
    }

protected:
    virtual void paintEvent(QPaintEvent *e){
        QPainter painter(this);
        int min_sz = minDim();

        QRect widget_rect = e->rect();
        painter.drawRect(widget_rect);
        painter.drawRect(0, 0, min_sz, min_sz);

        min_sz -= _pad;
        int d = min_sz / 8;
        for(int i = 0; i < min_sz; i += d){
            painter.drawLine(i + _pad, 0, i + _pad, min_sz);
            painter.drawLine(_pad, i, min_sz + _pad, i);
        }
        painter.drawLine(_pad, min_sz, min_sz + _pad, min_sz);


        for(int i = 0; i < 8; ++i){
            bool flag = i % 2 == 0;
            for(int j = 0; j < 8; ++j){
                QRect cr = getRectByCoord(i, j);
                bool flag2 = j % 2 == 0;
                if(flag && flag2  || (!flag) && (!flag2)){
                    painter.fillRect(cr, _black_cell);
                } else {
                    painter.fillRect(cr, _white_cell);
                }

                uint figure = _field[i][j];
            }
        }

        if(selected_cell){
            QRect cell = getRectByCoord(*selected_cell);
            painter.drawPixmap(cell, QPixmap(":/img/w_king.png"));
        }

    }

    virtual void mousePressEvent(QMouseEvent *e){
        int x = e->x();
        int y = e->y();
        int min_sz = minDim();
        if(x > min_sz || y > min_sz)
            return;
        int d = (min_sz - _pad) / 8;
        int x_cell = (x - _pad) / d;
        int y_cell = 7 - (y / d);
        if(selected_cell)
            delete selected_cell;
        selected_cell = new QPoint(x_cell, y_cell);
        repaint();
    }

    QRect getRectByCoord(QPoint p){
        return getRectByCoord(p.x(), p.y());
    }

    QRect getRectByCoord(int x, int y){
        x = x > 7 ? 7 : x < 0 ? 0 : x;
        y = y > 7 ? 7 : y < 0 ? 0 : y;
        int min_sz = minDim();
        min_sz -= _pad;
        float d = min_sz / 8.0;
        return QRect(x * d + _pad + 1, min_sz - d - (y * d) + 1, d - 1, d - 1);
    }

    int minDim(){
        int dim = (width() > height() ? height() : width()) - 1;
        dim -= _pad;
        int tmp = dim / 8.0;
        return tmp * 8 + _pad;
    }

public:
    static QPixmap getPixmap(uint figure_mask){
        uint test = (CHESSMAN_HORSE | WHITE);
        qDebug() << ((test & CHESSMAN_HORSE) == CHESSMAN_HORSE);
        qDebug() << ((test & CHESSMAN_KING) == CHESSMAN_KING);
        qDebug() << ((test & WHITE) == WHITE);
        qDebug() << ((test & BLACK) == BLACK);


        return QPixmap(":/img/w_king.png");
    }

signals:
    void cellClicked(int x, int y);

};

#endif // CHESSBOARD_H
