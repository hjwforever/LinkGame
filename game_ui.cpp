#include "game_ui.h"
#include "ui_game_ui.h"
#include"chooselevel_ui.h"
#include<iostream>
#include<QPixmap>
#include<QGraphicsScene>
using namespace std;

Game_UI::Game_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_UI)
{
    ui->setupUi(this);
    voiceplayer=new VoicePlayer;
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

    voiceplayer->Play_Voice(1);//播放按钮音效
}
