#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H
#include <QWidget>
#include <QPaintEvent>
#include <QPaintEngine>
#include <QtGlobal>
#include <QDebug>
#include <QBrush>
#include <QString>
#include <QList>
#include "strcoord.h"



class ChessboardWidget: public QWidget{
    Q_OBJECT
public:
    typedef QPoint Coord;
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

    Coord _selected_cell;
    bool _selected;

    QColor _black_cell;
    QColor _white_cell;

    bool _locked;

    uint _my_color;

    QList<Coord> _draw_path;

public:
    ChessboardWidget(ChessmanColor my_color = WHITE, QWidget* parent = 0): QWidget(parent){
        _my_color = my_color;

        _field = new uint*[8];
        for(int i = 0; i < 8; ++i){
            _field[i] = new uint[8];
            for(int j = 0; j < 8; ++j){
                _field[i][j] = 0;
            }
        }

        _pad = 25;

        _selected = false;

        _black_cell = Qt::gray;
        _white_cell = Qt::white;

        _locked = false;
    }

    virtual ~ChessboardWidget(){
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
                painter.drawRect(cr);

                uint figure = _field[i][j];
                if(figure){
                    painter.drawPixmap(getRectByCoord(i, j), getPixmap(figure));
                    painter.drawRect(cr);
                }
            }
        }

        if(_selected){
            QRect cell = getRectByCoord(_selected_cell);
            painter.setBrush(QBrush(QColor(0, 150, 0, 120)));
            painter.drawRect(cell);
        }

        if(!_draw_path.empty()){
            for(QList<Coord>::Iterator it = _draw_path.begin(); it != _draw_path.end(); ++it){
                painter.setBrush(QBrush(QColor(0, 150, 0, 120)));
                painter.drawRect(getRectByCoord(*it));
            }
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

        emit cellClicked(StrCoord(x_cell, y_cell), *e);
    }

    QRect getRectByCoord(Coord p){
        return getRectByCoord(p.x(), p.y());
    }

    QRect getRectByCoord(int x, int y){
        x = x > 7 ? 7 : x < 0 ? 0 : x;
        y = y > 7 ? 7 : y < 0 ? 0 : y;
        int min_sz = minDim();
        min_sz -= _pad;
        float d = min_sz / 8.0;
        return QRect(x * d + _pad, min_sz - d - (y * d), d, d);
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
        return QPixmap(":/Chessboard/img/" + figure_str + "_" + color_str + ".png");
    }
#undef F
#endif

    Coord strToCoord(QString s){
        char c = s[0].toLower().toLatin1();
        int d = s[1].digitValue();
        int c_index = (c - 'a') > 7 ? 7 : (c - 'a');
        int d_index = d > 7 ? 7 : (d - 1);
        return Coord(c_index, d_index);
    }

public:
    bool lock(){
        if(_locked)
            return false;
        _selected = false;
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

    uint& operator[](StrCoord s){
        return _field[s.x()][s.y()];
    }

    uint get(StrCoord s){
        return operator [](s);
    }

    void set(StrCoord s, uint mask){
        operator [](s) = mask;
        repaint();
    }


    void addPathElement(int x, int y){
        addPathElement(Coord(x, y));
    }

    void addPathElement(QString s){
        addPathElement(strToCoord(s));
    }

    void addPathElement(Coord coord){
        _draw_path.push_back(coord);
        repaint();
    }

    void clearPath(){
        _draw_path.clear();
        repaint();
    }

    void selectCell(StrCoord s){
        selectCell(s.toPoint());
    }

    void selectCell(int x, int y){
        selectCell(Coord(x, y));
    }

    void selectCell(Coord coord){
        _selected = true;
        _selected_cell = coord;
    }

    bool selected(){
        return _selected;
    }

    void removeSelection(){
        _selected = false;
    }

    StrCoord selectedCell(){
        return StrCoord(_selected_cell.x(), _selected_cell.y());
    }

signals:
    void cellClicked(StrCoord, QMouseEvent);

};

#endif // CHESSBOARDWIDGET_H
