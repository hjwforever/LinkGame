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

       QPoint pointa(x1+edgeOfButton/2,y1+edgeOfButton/2);  //��A
       QPoint pointb(x2+edgeOfButton/2,y2+edgeOfButton/2);  //��B
       //Scence->addLine(QLine(pointa,pointb),QPen(Qt::PenStyle::SolidLine));
       QPen pen;
       //pen.setColor("blue");
       pen.setColor("red");
       pen.setWidth(2);

       QLine line(pointa,pointb);
      // painter.setBrush(Qt::red);
       //painter.drawLine(a.first,a.second,b.first,b.second);
       //line.setLine(line.x1(),line.y1()+80,line.x2(),line.y2()+80);

       cout<<"���꣺"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<endl;
      Scence->addLine(line,pen);

   ui->game_UI_graphicsView->update();
}

void Game_UI::initButtonImage()
{
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            const char *c=QString("QPushButton{border-image: url(:/image/button_icon/fruit/%1.png)}").arg(QString::number(gameButtonMap[i][j]->text().toUInt())).toLatin1().data();
            gameButtonMap[i][j]->setStyleSheet(c);
            //gameButtonMap[i][j]->show();
        }

        cout<<endl;
    }
}

void Game_UI::on_returnButton_clicked()
{
    ChooseLevel_UI *chooseLevel_ui=new ChooseLevel_UI;
    chooseLevel_ui->show();

    //�˴�����ѽ�����Ϸ����

    delete this;
}

void Game_UI::on_beginButton_clicked()
{
    QIcon icon;
    icon.addFile("qrc:/image/button_icon/animal/1.png");

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
    initButtonImage();
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
            //�����źŲۣ�����button�������±�
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
    //voiceplayer->Play_Voice(1);//���Ű�ť��Ч

    if(count == 1){
        if(gameMap[row][column] == gameMap[vertex1.first][vertex1.second])
        {
            QList<Vertex> list;
            int turnNum = map.canLink_2(gameMap,row,column,vertex1.first,vertex1.second,list);
            if(turnNum!=-1)//�ж��ܷ���������
            {
                Scence->clear();
                voiceplayer->Play_Voice(2);//����������Ч
                gameMap[row][column]=0;
                gameMap[vertex1.first][vertex1.second]=0;
                gameButtonMap[row][column]->hide();
                gameButtonMap[vertex1.first][vertex1.second]->hide();
                count--;

                for(int i=0;i<list.length();i++)
                {
                    cout<<i<<"hhhhhhhhhh"<<list.at(i).first<<" "<<list.at(i).second<<endl;
                }

                int x1,y1,x2,y2;
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
                     x1=list.at(0).second*edgeOfButton+start_x;
                     y1=list.at(0).first*edgeOfButton+start_y;
                     x2=list.at(1).second*edgeOfButton+start_x;
                     y2=list.at(1).first*edgeOfButton+start_y;
                     drawLine(button1->x(),button1->y(),x1,y1);
                     drawLine(x1,y1,x2,y2);
                     drawLine(x2,y2,button2->x(),button2->y());
                }
                    //drawLine(10,100,50,400);

                //drawLine(list.at(0).first,list.at(0).second,list.at(1).first,list.at(1).second);
                //�ж��Ƿ�ȫ������(��Ϸͨ��)
                if(allCleared())
                {
                    cout<<"ȫ��ɾ��������"<<endl;
                }
            }
            else
            {
                voiceplayer->Play_Voice(1);//���Ű�ť��Ч
                vertex1.first = row;
                vertex1.second = column;
            }
        }
        else
        {
            voiceplayer->Play_Voice(1);//���Ű�ť��Ч
            vertex1.first = row;
            vertex1.second = column;
        }
    }
    else if(count ==0){
        voiceplayer->Play_Voice(1);//���Ű�ť��Ч
        vertex1.first = row;
        vertex1.second = column;
        count++;
    }
}


