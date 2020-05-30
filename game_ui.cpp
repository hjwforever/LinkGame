#include "game_ui.h"
#include "ui_game_ui.h"
#include"chooselevel_ui.h"
#include<iostream>
#include<QPixmap>
#include<QGraphicsScene>
#include<QList>
using namespace std;

Game_UI::Game_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_UI)
{
    ui->setupUi(this);
    Scence=new QGraphicsScene(this);
    Scence->setSceneRect(0,0,this->width(),this->height());
    ui->game_UI_graphicsView->setScene(Scence);
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

void Game_UI::drawLine(int x1,int y1,int x2,int y2)
{



       QPoint pointa(x1,y1);  //点A
       QPoint pointb(x2,y2);  //点B
       //Scence->addLine(QLine(pointa,pointb),QPen(Qt::PenStyle::SolidLine));
       QPen pen;
       pen.setColor("blue");
       pen.setWidth(2);

       QLine line(pointa,pointb);
      // painter.setBrush(Qt::red);
       //painter.drawLine(a.first,a.second,b.first,b.second);
       //line.setLine(line.x1(),line.y1()+80,line.x2(),line.y2()+80);

       cout<<"坐标："<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<endl;
      Scence->addLine(line,pen);

   ui->game_UI_graphicsView->update();
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
    //////////////////////////////
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            gameButtonMap[i][j]->setText(QString::number(gameMap[i][j]));
            gameButtonMap[i][j]->show();
        }

        cout<<endl;
    }
    ///////////////////////////////
}

bool Game_UI::allCleared()
{
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            if(gameMap[i][j] != 0)
                return false;
        }
        }
    return true;
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
            //连接信号槽，传递button的数组下标
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
    voiceplayer=new VoicePlayer;
    //voiceplayer->Play_Voice(1);//播放按钮音效

    if(count == 1){
        if(gameMap[row][column] == gameMap[vertex1.first][vertex1.second])
        {
            QList<Vertex> list;
            int turnNum = map.canLink_2(gameMap,row,column,vertex1.first,vertex1.second,list);
            if(turnNum!=-1)//判断能否连接消除
            {
                voiceplayer->Play_Voice(2);//播放消除音效
                gameMap[row][column]=0;
                gameMap[vertex1.first][vertex1.second]=0;
                gameButtonMap[row][column]->hide();
                gameButtonMap[vertex1.first][vertex1.second]->hide();
                count--;

                for(int i=0;i<list.length();i++)
                {
                    cout<<i<<"hhhhhhhhhh"<<list.at(i).first<<" "<<list.at(i).second<<endl;
                }

                MyButton *button1=gameButtonMap[row][column];
                MyButton *button2=gameButtonMap[vertex1.first][vertex1.second];
                MyButton *button3,*button4;
                if(turnNum == 0)
                {
                     drawLine(button1->x(),button1->y(),button2->x(),button2->y());
                }
                else if(turnNum == 1)
                {
                     button3=gameButtonMap[list.at(0).first][list.at(0).second];

                     drawLine(button1->x(),button1->y(),button3->x(),button3->y());
                     drawLine(button3->x(),button3->y(),button2->x(),button2->y());
                }
                else if(turnNum == 2)
                {
                     button3=gameButtonMap[list.at(0).first][list.at(0).second];
                     button4=gameButtonMap[list.at(1).first][list.at(1).second];

                     drawLine(button1->x(),button1->y(),button3->x(),button3->y());
                     drawLine(button3->x(),button3->y(),button4->x(),button4->y());
                     drawLine(button4->x(),button4->y(),button2->x(),button2->y());
                }
                    //drawLine(10,100,50,400);

                //drawLine(list.at(0).first,list.at(0).second,list.at(1).first,list.at(1).second);
                //判断是否全部消除(游戏通关)
                if(allCleared())
                {
                    cout<<"全部删除！！！"<<endl;
                }
            }
            else
            {
                voiceplayer->Play_Voice(1);//播放按钮音效
                vertex1.first = row;
                vertex1.second = column;
            }
        }
        else
        {
            voiceplayer->Play_Voice(1);//播放按钮音效
            vertex1.first = row;
            vertex1.second = column;
        }
    }
    else if(count ==0){
        voiceplayer->Play_Voice(1);//播放按钮音效
        vertex1.first = row;
        vertex1.second = column;
        count++;
    }
}


