#include "set_ui.h"
#include "ui_set_ui.h"

#include"linkgame.h"
#include"chooselevel_ui.h"

Set_UI::Set_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Set_UI)
{
    ui->setupUi(this);
    gameSound = new QMediaPlayer;//创建播放器
    gameList = new QMediaPlaylist;//创建播放列表
    gameList->addMedia(QUrl("qrc:/voice/music1.mp3"));//添加音乐
    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//循环播放
    gameSound->setPlaylist(gameList);
    gameSound->setVolume(50);
}

Set_UI::~Set_UI()
{
    delete ui;
}

void Set_UI::closeEvent(QCloseEvent *event){
    this->hide();
}

void Set_UI::setParentName(string parentName){
    this->parentName=parentName;
}
string Set_UI::getParentName(){
    return this->parentName;
}

void Set_UI::on_returnButton_clicked()
{
//    if(parentName=="linkgame_ui"){
//        LinkGame *linkgame_ui=new LinkGame;
//        linkgame_ui->show();
//    }else if(parentName=="chooseLevel_ui"){
//        ChooseLevel_UI *chooseLevel_ui=new ChooseLevel_UI;
//        chooseLevel_ui->show();
//    }
    this->hide();
}



void Set_UI::on_BGM_pushButton_clicked()
{
    QString s;
    s=ui->BGM_pushButton->text();
    if(s=="开")
    {
        gameSound->play();
        ui->BGM_pushButton->setText("关");
    }else{
        gameSound->pause();
        ui->BGM_pushButton->setText("开");
    }
}
