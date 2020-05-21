#include "mahjong.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mahjong w;
    w.show();
    return a.exec();
}
