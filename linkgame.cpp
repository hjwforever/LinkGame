#include "linkgame.h"
#include "ui_linkgame.h"
#include"chooselevel_ui.h"
#include"set_ui.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSysInfo>

extern Set_UI *set_ui;

LinkGame::LinkGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LinkGame)
{
    ui->setupUi(this);
}

LinkGame::~LinkGame()
{
    delete ui;
}


void LinkGame::on_onePersonButton_clicked()
{
    ChooseLevel_UI *chooseUI_One = new ChooseLevel_UI;
    chooseUI_One->show();
    this->close();//这里不能用delete，因为this是main函数中创建的栈空间系统自动释放
}

void LinkGame::on_twoPersonButton_clicked()
{
    ChooseLevel_UI *chooseUI_Two = new ChooseLevel_UI;
    chooseUI_Two->show();
    this->close();//这里不能用delete，因为this是main函数中创建的栈空间系统自动释放
}

void LinkGame::on_setButton_clicked()
{
    set_ui->setParentName("linkgame_ui");
    set_ui->show();
}
