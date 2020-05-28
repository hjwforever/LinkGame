#include "linkgame.h"
#include "ui_linkgame.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSysInfo>

#include"chooselevel_ui.h"
#include"set_ui.h"

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
    this->close();//���ﲻ����delete����Ϊthis��main�����д�����ջ�ռ�ϵͳ�Զ��ͷ�
}

void LinkGame::on_twoPersonButton_clicked()
{
    ChooseLevel_UI *chooseUI_Two = new ChooseLevel_UI;
    chooseUI_Two->show();
    this->close();//���ﲻ����delete����Ϊthis��main�����д�����ջ�ռ�ϵͳ�Զ��ͷ�
}

void LinkGame::on_setButton_clicked()
{
    set_ui->setParentName("linkgame_ui");
    set_ui->show();
    //delete this;
}
