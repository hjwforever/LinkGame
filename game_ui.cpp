#include "game_ui.h"
#include "ui_game_ui.h"
#include"chooselevel_ui.h"
#include"deleteqgraphicsitemthread.h"
#include<iostream>
#include<QPixmap>
#include<QGraphicsScene>
#include<QList>
#include<QPixmap>
#include<QSize>
#include"linkgame.h"
#include"set_ui.h"
using namespace std;

extern Set_UI *set_ui;
Game_UI::Game_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_UI)
{
    ui->setupUi(this);
    Scence=new QGraphicsScene(this);
    Scence->setSceneRect(0,0,this->width(),this->height());
    ui->game_UI_graphicsView->setScene(Scence);

    ui->score_Label->setStyleSheet("color:white");

    // ������
    ui->gametime_label->setText("59");
    ui->gametime_label->setStyleSheet("color:white");
    ui->timeBar->setTextVisible(false);
    ui->timeBar->setMaximum(60);
    ui->timeBar->setMinimum(0);
    ui->timeBar->setValue(60);
    // ��Ϸ��ʱ��
    gameTimer = new QTimer;
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));
    gameTimer->start(1000);

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
    QPen pen;
    pen.setColor("white");
    pen.setWidth(4);
    QLine line(pointa,pointb);
    ///////////////////////////////////
    cout<<"���꣺"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<endl;
    ////////////////////////////////////
    Scence->addLine(line,pen);
    ui->game_UI_graphicsView->update();
    DeleteQGraphicsItemThread *thread=new DeleteQGraphicsItemThread(x1+edgeOfButton/2,y1+edgeOfButton/2);
    thread->start();
    connect(thread, SIGNAL(deleteItem(int,int)),this, SLOT(on_deleteThread(int,int)));
}

void Game_UI::Erasure_Score()
{
    score++;
    erasure_Interval = Erasure_Time.restart();
    if(erasure_Interval<=1500){
        continuous_Erasure++;
        score+=continuous_Erasure;
    }else{
        continuous_Erasure = 0;
    }
    ui->score_Label->setText(QString::fromLocal8Bit("�÷֣�")+QString::number(score));
    ui->score_Label->setStyleSheet("color:white");
}

void Game_UI::initButtonImage()
{
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            gameButtonMap[i][j]->setStyleSheet(QString("QPushButton{border-image: url(:/image/button_icon/%1/%2.png)}").arg(currentModel[set_ui->currentModelNum]).arg(gameMap[i][j]).toLatin1().data());
        }
    }
}

void Game_UI::on_deleteThread(int x,int y){
    QList<QGraphicsItem *> item_list_p = Scence->items(QRectF(x, y, 1, 1), Qt::IntersectsItemShape);

        //ɾ��Ԫ��
        for(int i=0; i<item_list_p.size(); i++){
            Scence->removeItem(item_list_p[i]);  //��scene�Ƴ�
            delete item_list_p[i];  //�ͷ��ڴ�
        }
}

//��Ϸ������
void Game_UI::gameTimerEvent(){
    //��������ʱЧ��
    if(ui->timeBar->value() == 0)
    {
        gameTimer->stop();

        //��ʾ��
        QMessageBox::information(this, "game over", "play again>_<");
        QMessageBox msgBox;
        msgBox.setText(tr("<span style='color: blue; font-size: 24px;'>   Game Over!</span/p>"));
        msgBox.setInformativeText(tr("Do you want to continue?"));
        msgBox.setStandardButtons(QMessageBox::Retry
                                  | QMessageBox::Yes
                                  | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Save);
       // msgBox.setIconPixmap(QPixmap(":/image/button_icon/fruit/2.png"));
        msgBox.setIconPixmap(QPixmap(":/image/button_icon/fruit/2.png").scaled(QSize(60,40), Qt::KeepAspectRatio));
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Retry:
            qDebug() << "Retry";
            on_beginButton_clicked();
            break;
        case QMessageBox::Yes:
            qDebug() << "Yes";
            break;
        case QMessageBox::No:
            qDebug() << "No";
            LinkGame *linkGame_ui=new LinkGame;
            linkGame_ui->show();
            delete this;
            break;
        }
    }
    else
    {
        ui->timeBar->setValue(ui->timeBar->value() - 1);
        if(ui->gametime_label->text()!="0")
        ui->gametime_label->setText(QString::number(ui->timeBar->value() - 1));
        else
        ui->timeBar->setValue(0);

    }
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

void Game_UI::on_returnButton_clicked()
{
    ChooseLevel_UI *chooseLevel_ui=new ChooseLevel_UI;
    chooseLevel_ui->show();

    //�˴�����ѽ�����Ϸ����

    delete this;
}

void Game_UI::on_beginButton_clicked()
{
    ui->timeBar->setValue(60);
    ui->gametime_label->setText(QString::number(59));
    gameTimer->stop();
    gameTimer=new QTimer;
    gameTimer->start(1000);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));

    gameMap=map.creatMap(rowSize,columnSize,level,numOfPic);
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            //gameButtonMap[i][j]->setText(QString::number(gameMap[i][j]));
            gameButtonMap[i][j]->show();
        }
    }
    initButtonImage();
    score=0;
    continuous_Erasure=0;
    erasure_Interval=0;
    Scence->clear();
    ui->score_Label->setText(QString::fromLocal8Bit("�÷֣�")+QString::number(score));
    ui->score_Label->setStyleSheet("color:white");
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
            //myButton->setText(QString::number(gameMap[i][j]));
            gameButtonMap[i][j]=myButton;
        }
        /////////////////
        cout<<endl;
        //////////////////
    }
    initButtonImage();
}

void Game_UI::setAllButtonVisible(bool visible){
    for(int i=0;i<rowSize;i++){
        for(int j=0;j<columnSize;j++){
            if(gameMap[i][j]!=0){
                if(visible){
                    gameButtonMap[i][j]->show();
                }else{
                    gameButtonMap[i][j]->hide();
                }
            }
        }
    }
}

void Game_UI::on_myButton_clicked(int row,int column){
    voiceplayer=new VoicePlayer;
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
                Erasure_Score();
                for(int i=0;i<list.length();i++)
                {
                    cout<<i<<"hhhhhhhhhh"<<list.at(i).first<<" "<<list.at(i).second<<endl;
                }

                int x1,y1,x2,y2;
                MyButton *button1=gameButtonMap[row][column];
                MyButton *button2=gameButtonMap[vertex1.first][vertex1.second];
                MyButton *button3;
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
                //�ж��Ƿ�ȫ������(��Ϸͨ��)
                if(allCleared())
                {
                    ////////////////////////////////����ӽ�������
                    cout<<"ȫ��ɾ��������"<<endl;
                    ////////////////////////////////
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

//��ͣ������ť
void Game_UI::on_pauseButton_clicked()
{
    if(!isPause)
    {
        setAllButtonVisible(false);
        isPause=true;
        gameTimer->stop();
        ui->pauseButton->setText(QString::fromLocal8Bit("����"));
        //allButtonHide();
    }
    else if(isPause)
    {
        setAllButtonVisible(true);
        isPause=false;
        gameTimer->start(1000);
        ui->pauseButton->setText(QString::fromLocal8Bit("��ͣ"));
    }
}
