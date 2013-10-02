#ifndef STRCOORD_H
#define STRCOORD_H
#include <QString>
#include <QPoint>
#include <QObject>

class StrCoord: public QObject {
    Q_OBJECT
private:
    QString _s;

    StrCoord(int x, int y): QObject(){
        QString leter_coord('a' + x);
        QString digit_coord = QString::number(1 + y);
        _s = QString(leter_coord + digit_coord);
    }

    void setX(int x){
        _s[0] = 'a' + x;
    }

    void setY(int y){
        _s[1] = QString::number(1 + y)[0];
    }

public:
    StrCoord(const StrCoord& sc): QObject(){
        _s = sc._s;
    }

    StrCoord(const QString& s): QObject(){
        _s = s;
    }

    StrCoord(const char* cs): QObject(){
        _s = QString(cs);
    }

    int x(){
        char c = _s[0].toLower().toLatin1();
        int c_index = (c - 'a') > 7 ? 7 : (c - 'a');
        return c_index;
    }

    int y(){
        int d = _s[1].digitValue();
        int d_index = d > 7 ? 7 : (d - 1);
        return d_index;
    }

    QPoint toPoint(){
        return QPoint(x(), y());
    }

    bool up(){
        if(y() < 7){

        } else {
            return false;
        }
    }

    bool down(){
        if(y() > 0){

        } else {
            return false;
        }
    }

    bool left(){
        if(x() > 0){

        } else {
            return false;
        }
    }

    bool right(){
        if(x() < 7){

        } else {
            return false;
        }
    }

    QString toString(){
        return _s;
    }
};

#endif // STRCOORD_H
