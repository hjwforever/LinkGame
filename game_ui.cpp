#include "game_ui.h"
#include "ui_game_ui.h"
#include"chooselevel_ui.h"
#include<iostream>
using namespace std;

Game_UI::Game_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_UI)
{
    ui->setupUi(this);
}

Game_UI::~Game_UI()
{
    delete ui;
}

void Game_UI::setLevel(int level){
    this->level=level;
}

int Game_UI::getLevel(){
    return this->level;
}

void Game_UI::on_returnButton_clicked()
{
    ChooseLevel_UI *chooseLevel_ui=new ChooseLevel_UI;
    chooseLevel_ui->show();

    //此处可能呀清空游戏数据

    delete this;
}

void Game_UI::on_beginButton_clicked()
{
    gameMap=map.creatMap(rowSize,columnSize,level,numOfPic);
    ////////////////////////
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            gameButtonMap[i][j]->setText(QString::number(gameMap[i][j]));
        }
        cout<<endl;
    }
    ///////////////////////////////
}

void Game_UI::createGameMap(){
    MyButton *button=new MyButton;
    gameButtonMap=(MyButton***) malloc(rowSize*sizeof(MyButton**));
    for(int i=0;i<rowSize;i++){
        gameButtonMap[i]=(MyButton**)malloc(columnSize*sizeof(MyButton*));
        for(int j=0;j<columnSize;j++){
            gameButtonMap[i][j]=button;
        }
    }

    gameMap=map.creatMap(rowSize,columnSize,level,numOfPic);

    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            /////////////////
            cout<<gameMap[i][j]<<"\t";
            ///////////////////////
            MyButton *myButton=new MyButton;
            myButton->setParent(this);
            myButton->setCoordinate(i,j);
            myButton->setGeometry(start_x+j*edgeOfButton,start_y+i*edgeOfButton,edgeOfButton,edgeOfButton);
            myButton->show();
            connect(myButton, SIGNAL(clicked(int,int)),this, SLOT(on_myButton_clicked(int,int)));

            myButton->setText(QString::number(gameMap[i][j]));

            gameButtonMap[i][j]=myButton;
        }
        /////////////////
        cout<<endl;
        //////////////////
    }

}

void Game_UI::on_myButton_clicked(int row,int column){
    /////////////////
    cout<<row<<" "<<column<<endl;
    //////////////////////////////
    playvoice(1);
}

void Game_UI::playvoice(int index)
{
    gameSound = new QMediaPlayer;//创建播放器
    gameList = new QMediaPlaylist;//创建播放列表
    QString url="qrc:/voice/button_Sound/sound.mp3";
    url.insert(29,QString::number(index));
    cout<<url.toStdString()<<endl;
    gameList->addMedia(QUrl(url));//添加音乐
    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);//播放一次
    gameSound->setPlaylist(gameList);
    gameSound->setVolume(20);
    gameSound->play();
}
