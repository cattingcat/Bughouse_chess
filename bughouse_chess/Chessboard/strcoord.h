#ifndef STRCOORD_H
#define STRCOORD_H
#include <QString>
#include <QPoint>
#include <QObject>
#include <iostream>

class StrCoord: public QObject {
    Q_OBJECT
private:
    int _x;
    int _y;




    void setX(int x){
        _x = x;
    }

    void setY(int y){
        _y = y;
    }

public:
    StrCoord(int x, int y): QObject(){
        _x = x;
        _y = y;
    }

    StrCoord(const StrCoord& sc): QObject(){
        this->_x = sc._x;
        this->_y = sc._y;
    }

    StrCoord(const QString& s): QObject(){
        const char* cs = s.toLower().toStdString().c_str();
        _x = cs[0] - 'a';
        _y = cs[1] - '1';
    }

    StrCoord(const char* cs): QObject(){
        const char* s = QString(cs).toLower().toStdString().c_str();
        _x = s[0] - 'a';
        _y = s[1] - '1';
    }

    int x(){
        return _x;
    }

    int y(){
        return _y;
    }

    QPoint toPoint(){
        return QPoint(_x, _y);
    }

    bool hasUp(){
        return y() < 7;
    }
    bool hasDown(){
        return y() > 0;
    }
    bool hasLeft(){
        return x() > 0;
    }
    bool hasRight(){
        return x() < 7;
    }


    bool up(){
        if(y() < 7){
            ++_y;
            return true;
        } else {
            return false;
        }
    }
    bool down(){
        if(y() > 0){
            --_y;
            return true;
        } else {
            return false;
        }
    }
    bool left(){
        if(x() > 0){
            --_x;
            return true;
        } else {
            return false;
        }
    }
    bool right(){
        if(x() < 7){
            ++_x;
            return true;
        } else {
            return false;
        }
    }

    QString toString() const{
        QString res(2, 'A');
        res[0] = _x + 'a';
        res[1] = _y + '1';
        return res;
    }
};

#endif // STRCOORD_H
