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
    ui->label3->setVisible(false);

    // 进度条
    ui->gametime_label->setText("59");
    ui->gametime_label->setStyleSheet("color:white");
    ui->timeBar->setTextVisible(false);
    ui->timeBar->setMaximum(60);
    ui->timeBar->setMinimum(0);
    ui->timeBar->setValue(60);
    // 游戏计时器
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
    numOfPic =2+level*6;
}

int Game_UI::getLevel(){
    return this->level;
}

void Game_UI::drawLine(int x1,int y1,int x2,int y2)
{
    QPoint pointa(x1+edgeOfButton/2,y1+edgeOfButton/2);  //点A
    QPoint pointb(x2+edgeOfButton/2,y2+edgeOfButton/2);  //点B
    QPen pen;
    pen.setColor("white");
    pen.setWidth(4);
    QLine line(pointa,pointb);
    ///////////////////////////////////
    cout<<"坐标："<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<endl;
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
    ui->score_Label->setText(QString::fromLocal8Bit("得分：")+QString::number(score));
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

        //删除元素
        for(int i=0; i<item_list_p.size(); i++){
            Scence->removeItem(item_list_p[i]);  //从scene移除
            delete item_list_p[i];  //释放内存
        }
}

bool Game_UI::autoEliminateBlock(int** gameMap_0,bool showProgress,int index_x1,int index_y1,int index_x2,int index_y2){

    if(gameMap_0[index_x1][index_y1] == gameMap_0[index_x2][index_y2])
    {
        QList<Vertex> list;
        int turnNum = map.canLink_2(gameMap_0,index_x1,index_y1,index_x2,index_y2,list);
        if(turnNum!=-1)//判断能否连接消除
        {
            gameMap_0[index_x1][index_y1]=0;
            gameMap_0[index_x2][index_y2]=0;
            if(showProgress){
                //画线
                int x1,y1,x2,y2;
                MyButton *button1=gameButtonMap[index_x1][index_y1];
                MyButton *button2=gameButtonMap[index_x2][index_y2];
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

                qApp->processEvents();
                Sleep(500);
//                gameMap[index_x1][index_y1]=0;
//                gameMap[index_x2][index_y2]=0;
                gameButtonMap[index_x1][index_y1]->hide();
                gameButtonMap[index_x2][index_y2]->hide();

                Erasure_Score();
                qApp->processEvents();

            }


//            voiceplayer=new VoicePlayer;
//            voiceplayer->Play_Voice(2);//播放消除音效



            //判断是否全部消除(游戏通关)
            if(allCleared(gameMap_0))
            {
                ////////////////////////////////待添加结束界面
                cout<<"全部删除！！！"<<endl;
                ////////////////////////////////
            }
            return true;
        }
        else
        {
            //voiceplayer->Play_Voice(1);//播放按钮音效
            return false;
        }
    }
    else
    {
        //voiceplayer->Play_Voice(1);//播放按钮音效
        return false;
    }
}

/*
 *自动解题
 */
bool Game_UI::autoProblemSolve(int** gameMap_0,bool showProgress){

    while(!allCleared(gameMap_0)){
        bool hasSollution=false;
        for(int i=1;i<=rowSize-2;i++){
            for(int j=1;j<=columnSize-2;j++){
                if(gameMap_0[i][j]!=0){
                    for (int m=1;m<=rowSize-2;m++) {
                        for(int n=1;n<=columnSize-2;n++){
                            if(gameMap_0[m][n]!=0){
                                if(autoEliminateBlock(gameMap_0,showProgress,i,j,m,n)){
                                    hasSollution=true;
                                }

                            }
                        }
                    }
                }
            }
        }
        if(!hasSollution) {
            cout<<"无解"<<endl;
            return false;
        }
        if(!showProgress){
            break;
        }
    }
    cout<<"有解"<<endl;
    return true;    //***************************************************************暂时返回true
}

void Game_UI::tip(int** gameMap_0){
    while(!allCleared(gameMap_0)) {
        bool hasSollution=false;
        for(int i=1;i<=rowSize-2;i++){
            for(int j=1;j<=columnSize-2;j++){
                if(gameMap_0[i][j]!=0){
                    for (int m=1;m<=rowSize-2;m++) {
                        for(int n=1;n<=columnSize-2;n++){
                            if(gameMap_0[m][n]!=0){
                                if(gameMap_0[i][j] == gameMap_0[m][n])
                                {
                                    QList<Vertex> list;
                                    int turnNum = map.canLink_2(gameMap_0,i,j,m,n,list);
                                    if(turnNum!=-1)//判断能否连接消除
                                    {
                                        //画线
                                        int x1,y1,x2,y2;
                                        MyButton *button1=gameButtonMap[i][j];
                                        MyButton *button2=gameButtonMap[m][n];
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

                                        qApp->processEvents();
                                        hasSollution=true;
                                        goto label;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(!hasSollution) {
            break;
        }
    }
    label:;
}

//游戏进度条
void Game_UI::gameTimerEvent(){
    //进度条计时效果
    if(ui->timeBar->value() == 0)
    {
        gameTimer->stop();

        //提示框
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

bool Game_UI::allCleared(int** gameMap)
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

    //此处可能呀清空游戏数据

    delete this;
}

void Game_UI::on_beginButton_clicked()
{
    ui->label3->setVisible(false);
    ui->pauseButton->setText(QString::fromLocal8Bit("暂停"));
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
    ui->score_Label->setText(QString::fromLocal8Bit("得分：")+QString::number(score));
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
            //连接信号槽，传递button的数组下标
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
            if(turnNum!=-1)//判断能否连接消除
            {
                count--;
                voiceplayer->Play_Voice(2);//播放消除音效

                gameMap[row][column]=0;
                gameMap[vertex1.first][vertex1.second]=0;
                gameButtonMap[row][column]->hide();
                gameButtonMap[vertex1.first][vertex1.second]->hide();

                Erasure_Score();
                for(int i=0;i<list.length();i++)//**************************************************
                {
                    cout<<i<<"hhhhhhhhhh"<<list.at(i).first<<" "<<list.at(i).second<<endl;
                }//*******************************************************************************

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
                //判断是否全部消除(游戏通关)
                if(allCleared(gameMap))
                {
                    ////////////////////////////////待添加结束界面
                    cout<<"全部删除！！！"<<endl;
                    ////////////////////////////////
                }

                int** copyGameMap=(int**) malloc(rowSize*sizeof(int*));
                for(int i=0;i<rowSize;i++){
                    copyGameMap[i]=(int*)malloc(columnSize*sizeof(int));
                    for(int j=0;j<columnSize;j++){
                        copyGameMap[i][j]=gameMap[i][j];
                    }
                }
                if(!autoProblemSolve(copyGameMap,false)){
                    cout<<"陷入僵局"<<endl;
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
    voiceplayer->Stop_Voice();
}

//暂停继续按钮
void Game_UI::on_pauseButton_clicked()
{
    if(!isPause)
    {
        setAllButtonVisible(false);
        isPause=true;
        gameTimer->stop();
        ui->pauseButton->setText(QString::fromLocal8Bit("继续"));
    }
    else if(isPause)
    {
        setAllButtonVisible(true);
        isPause=false;
        gameTimer->start(1000);
        ui->pauseButton->setText(QString::fromLocal8Bit("暂停"));
    }
     ui->label3->setVisible(isPause); //设置遮挡画布（图片）的可见性
}

void Game_UI::on_autoSolveProblemButton_clicked()
{

    autoProblemSolve(gameMap,true);
}

void Game_UI::on_tipButton_clicked()
{
    tip(gameMap);
}
