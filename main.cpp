#include "linkgame.h"

#include <QApplication>

#include"set_ui.h"
extern Set_UI *set_ui;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    LinkGame w;
    //    w.show();

    set_ui=new Set_UI;
    set_ui->setFixedSize(300,450);
    set_ui->hide();

    LinkGame w;
    w.show();

    return a.exec();
}
