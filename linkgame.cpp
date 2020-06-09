#include "linkgame.h"
#include "ui_linkgame.h"
#include"chooselevel_ui.h"
#include"set_ui.h"
#include"login_ui.h"
#include"game_ui.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSysInfo>

extern Set_UI *set_ui;

LinkGame::LinkGame(QWidget *parent)
    : MyMainWindow(parent)
    , ui(new Ui::LinkGame)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPixmap pixmap1(":/image/button_icon/linkgame_ui/single_mode.png");
    ui->onePersonButton->resize(pixmap1.size());
    ui->onePersonButton->setIcon(pixmap1);
    ui->onePersonButton->setIconSize(pixmap1.size());
    ui->onePersonButton->setMask(pixmap1.mask());
    ui->onePersonButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap2(":/image/button_icon/linkgame_ui/double_mode.png");
    ui->twoPersonButton->resize(pixmap2.size());
    ui->twoPersonButton->setIcon(pixmap2);
    ui->twoPersonButton->setIconSize(pixmap2.size());
    ui->twoPersonButton->setMask(pixmap2.mask());
    ui->twoPersonButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap3(":/image/button_icon/linkgame_ui/list.png");
    ui->ranking_List_Button->resize(pixmap3.size());
    ui->ranking_List_Button->setIcon(pixmap3);
    ui->ranking_List_Button->setIconSize(pixmap3.size());
    ui->ranking_List_Button->setMask(pixmap3.mask());
    ui->ranking_List_Button->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap4(":/image/button_icon/linkgame_ui/set.png");
    ui->setButton->resize(pixmap4.size());
    ui->setButton->setIcon(pixmap4);
    ui->setButton->setIconSize(pixmap4.size());
    ui->setButton->setMask(pixmap4.mask());
    ui->setButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap5(":/image/button_icon/linkgame_ui/about.png");
    ui->aboutButton->resize(pixmap5.size());
    ui->aboutButton->setIcon(pixmap5);
    ui->aboutButton->setIconSize(pixmap5.size());
    ui->aboutButton->setMask(pixmap5.mask());
    ui->aboutButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap6(":/image/button_icon/linkgame_ui/exit.png");
    ui->exitButton->resize(pixmap6.size());
    ui->exitButton->setIcon(pixmap6);
    ui->exitButton->setIconSize(pixmap6.size());
    ui->exitButton->setMask(pixmap6.mask());
    ui->exitButton->setStyleSheet("QToolButton{border:0px;}");

}

LinkGame::~LinkGame()
{
    delete ui;
}


void LinkGame::on_onePersonButton_clicked()
{
    set_ui->isTwoPeople=false;
    ChooseLevel_UI *chooseUI_One = new ChooseLevel_UI;
    chooseUI_One->show();
    this->close();//���ﲻ����delete����Ϊthis��main�����д�����ջ�ռ�ϵͳ�Զ��ͷ�
}

void LinkGame::on_twoPersonButton_clicked()
{
    set_ui->isTwoPeople=true;
    if(!set_ui->hasLogin){
        //set_ui->connectToServer();
        Login_UI *loginUI=new Login_UI;
        loginUI->show();
        this->close();
    }else{
        Game_UI *gameUI=new Game_UI;
        connect(this, SIGNAL(signal_createEmptyMap()), gameUI, SLOT(createEmptyGameMap()));
        gameUI->show();
        emit signal_createEmptyMap();
        this->close();
    }

//    ChooseLevel_UI *chooseUI_Two = new ChooseLevel_UI;
//    chooseUI_Two->show();
//    this->close();//���ﲻ����delete����Ϊthis��main�����д�����ջ�ռ�ϵͳ�Զ��ͷ�
}

void LinkGame::on_setButton_clicked()
{
    set_ui->setParentName("linkgame_ui");
    set_ui->show();
}

void LinkGame::on_exitButton_clicked()
{
    qApp->quit();
}

void LinkGame::on_aboutButton_clicked()
{
    MessageDialog* messageDialog = new MessageDialog(this,"制作人：陈庆洋、邓硕、胡江浩、黄俊雯\n制作日期：2020.5-2020.6");
    messageDialog->show();
}
