#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QWidget>
#include <QPaintEvent>
#include <QPaintEngine>
#include <QtGlobal>
#include <QDebug>
#include <QBrush>
#include <QString>



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
    QPoint *_selected_cell;

    QColor _black_cell;
    QColor _white_cell;

    bool _locked;

public:
    Chessboard(QWidget* parent = 0): QWidget(parent){
        _field = new uint*[8];
        for(int i = 0; i < 8; ++i){
            _field[i] = new uint[8];
            for(int j = 0; j < 8; ++j){
                _field[i][j] = 0;
            }
        }

        _pad = 25;

        _selected_cell = 0;

        _black_cell = Qt::black;
        _white_cell = Qt::white;

        _locked = false;

        _field[0][1] = CHESSMAN_KING | WHITE;
        (*this)["C6"] = CHESSMAN_KING | WHITE;
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
                if((flag && flag2)  || ((!flag) && (!flag2))){
                    painter.fillRect(cr, _black_cell);
                } else {
                    painter.fillRect(cr, _white_cell);
                }

                uint figure = _field[i][j];
                if(figure){
                    painter.drawPixmap(getRectByCoord(i, j), getPixmap(figure));
                }
            }
        }

        if(_selected_cell){
            QRect cell = getRectByCoord(*_selected_cell);
            painter.drawPixmap(cell, QPixmap(":/img/w_king.png"));
        }

    }

    virtual void mousePressEvent(QMouseEvent *e){
        if(_locked)
            return;
        int x = e->x();
        int y = e->y();
        int min_sz = minDim();
        if(x > min_sz || y > min_sz)
            return;
        int d = (min_sz - _pad) / 8;
        int x_cell = (x - _pad) / d;
        int y_cell = 7 - (y / d);
        if(_selected_cell)
            delete _selected_cell;
        _selected_cell = new QPoint(x_cell, y_cell);
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

#define F(x) (((figure_mask) & (x)) == (x))
#ifdef F
    QPixmap getPixmap(uint figure_mask){
        QString color_str("");
        QString figure_str("");
        if(F(WHITE)){
            color_str = "w";
        } else {
            color_str = "b";
        }
        if(F(CHESSMAN_PAWN)){
            figure_str = "pawn";
        } else if(F(CHESSMAN_ELEPHANT)){
            figure_str = "elephant";
        } else if(F(CHESSMAN_HORSE)){
            figure_str = "horse";
        } else if(F(CHESSMAN_ROOK)){
            figure_str = "rook";
        } else if(F(CHESSMAN_QUEEN)){
            figure_str = "queen";
        } else if(F(CHESSMAN_KING)){
            figure_str = "king";
        } else {
            figure_str = "error";
        }
        return QPixmap(":/img/" + color_str + "_" + figure_str + ".png");
    }
#undef F
#endif

    uint& operator[](QString s){
        char c = s[0].toLower().toLatin1();
        int d = s[1].digitValue();
        int c_index = (c - 'a') > 7 ? 7 : (c - 'a');
        int d_index = d > 7 ? 7 : (d - 1);
        return _field[c_index][d_index];
    }
public:
    bool lock(){
        if(_locked)
            return false;
        if(_selected_cell)
            delete _selected_cell;
        _selected_cell = 0;
        _locked = true;
        repaint();
        return true;
    }

    bool unlock(){
        if(!_locked)
            return false;
        _locked = false;
        return true;
    }

signals:
    void cellClicked(int x, int y);

};

#endif // CHESSBOARD_H
