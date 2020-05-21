#include "mahjong.h"

#include <QApplication>
#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout<<"»Æ¿¡ö©Ì«Ç¿ÁË£¡"<<endl;
    QApplication a(argc, argv);
    Mahjong w;
    w.show();
    return a.exec();
}
