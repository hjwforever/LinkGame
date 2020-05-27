#include "linkgame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //jaosfha f
    QApplication a(argc, argv);
    LinkGame w;
    w.show();
    return a.exec();
}
