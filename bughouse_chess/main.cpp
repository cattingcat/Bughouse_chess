#include "mainwindow.h"
#include <QApplication>
#include "chessboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Chessboard::getPixmap(11);
    
    return a.exec();
}
