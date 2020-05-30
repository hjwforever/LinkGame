#include "linkgame.h"
#include <QApplication>
#include"set_ui.h"
extern Set_UI *set_ui;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    set_ui=new Set_UI;
    set_ui->hide();
    LinkGame w;
    w.show();

    return a.exec();
}
