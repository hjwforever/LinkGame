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
    // ������
    ui->gametime_label->setText("59");
    ui->gametime_label->setStyleSheet("color:white");
    ui->score_Label->setStyleSheet("color:white");
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

void Game_UI::changeAutoState(){
    if(!isPause){
        if(isAutoSolve){
            isAutoSolve=false;
            ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("�Զ�����"));
        }else{
            isAutoSolve=true;
            ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("�ֶ�����"));
        }
    }

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

void Game_UI::drawPathLine_exe(int index_x1,int index_y1,int index_x2,int index_y2,QList<Vertex> *list){
    cout<<"drawPathLine"<<endl;
    int x1,y1,x2,y2;
    MyButton *button1=gameButtonMap[index_x1][index_y1];
    MyButton *button2=gameButtonMap[index_x2][index_y2];
    MyButton *button3;
    if(list->length() == 0)
    {
        drawLine(button1->x(),button1->y(),button2->x(),button2->y());
    }
    else if(list->length() == 1)
    {
        button3=gameButtonMap[list->at(0).first][list->at(0).second];
        drawLine(button1->x(),button1->y(),button3->x(),button3->y());
        drawLine(button3->x(),button3->y(),button2->x(),button2->y());
    }
    else if(list->length() == 2)
    {
        x1=list->at(0).second*edgeOfButton+start_x;
        y1=list->at(0).first*edgeOfButton+start_y;
        x2=list->at(1).second*edgeOfButton+start_x;
        y2=list->at(1).first*edgeOfButton+start_y;
        drawLine(button1->x(),button1->y(),x1,y1);
        drawLine(x1,y1,x2,y2);
        drawLine(x2,y2,button2->x(),button2->y());
    }
    qApp->processEvents();

    //�ж��Ƿ�ȫ������(��Ϸͨ��)
//    if(allCleared(gameMap))
//    {
//        //gameOver();
//        cout<<"ȫ��ɾ��������"<<endl;
//    }
}

void Game_UI::hideButton_exe(int index_x1,int index_y1,int index_x2,int index_y2){
    gameButtonMap[index_x1][index_y1]->hide();
    gameButtonMap[index_x2][index_y2]->hide();
    Erasure_Score();
    //�ж��Ƿ�ȫ������(��Ϸͨ��)
    if(allCleared(gameMap))
    {
        gameOver();
        cout<<"ȫ��ɾ��������"<<endl;
    }
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

//bool Game_UI::autoEliminateBlock(int** gameMap_0,bool showProgress,int index_x1,int index_y1,int index_x2,int index_y2){
//    cout<<"showProgress "<<showProgress<<" "<<index_x1<<" "<<index_y1<<" "<<index_x2<<" "<<index_y2<<endl;
//    if(gameMap_0[index_x1][index_y1] == gameMap_0[index_x2][index_y2])
//    {
//        QList<Vertex> list;
//        int turnNum = map.canLink_2(gameMap_0,index_x1,index_y1,index_x2,index_y2,list);
//        if(turnNum!=-1)//�ж��ܷ���������
//        {
//            //�ж��Ƿ�ȫ������(��Ϸͨ��)
//            if(allCleared(gameMap_0))
//            {
//                ////////////////////////////////����ӽ�������
//                gameOver();
//                cout<<"ȫ��ɾ��������"<<endl;
//                ////////////////////////////////
//            }
//            return true;
//        }
//        else
//        {
//            //voiceplayer->Play_Voice(1);//���Ű�ť��Ч
//            return false;
//        }
//        voiceplayer->Stop_Voice();
//    }
//    else
//    {
//        //voiceplayer->Play_Voice(1);//���Ű�ť��Ч
//        return false;
//    }
//}

/*
 *�ж�����
 */
bool Game_UI::isDeadlock(int** gameMap_0){
    for(int i=1;i<=rowSize-2;i++){
        for(int j=1;j<=columnSize-2;j++){
            if(gameMap_0[i][j]!=0){
                for (int m=1;m<=rowSize-2;m++) {
                    for(int n=1;n<=columnSize-2;n++){
                        if(gameMap_0[m][n]!=0&&gameMap_0[i][j]==gameMap_0[m][n]){
                            QList<Vertex> list;
                            int turnNum = map.canLink_2(gameMap_0,i,j,m,n,list);
                            if(turnNum!=-1){
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
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
                                    if(turnNum!=-1)//�ж��ܷ���������
                                    {
                                        //����
                                        drawPathLine_exe(i,j,m,n,&list);
                                        //                                        int x1,y1,x2,y2;
                                        //                                        MyButton *button1=gameButtonMap[i][j];
                                        //                                        MyButton *button2=gameButtonMap[m][n];
                                        //                                        MyButton *button3;
                                        //                                        if(turnNum == 0)
                                        //                                        {
                                        //                                            drawLine(button1->x(),button1->y(),button2->x(),button2->y());
                                        //                                        }
                                        //                                        else if(turnNum == 1)
                                        //                                        {
                                        //                                            button3=gameButtonMap[list.at(0).first][list.at(0).second];
                                        //                                            drawLine(button1->x(),button1->y(),button3->x(),button3->y());
                                        //                                            drawLine(button3->x(),button3->y(),button2->x(),button2->y());
                                        //                                        }
                                        //                                        else if(turnNum == 2)
                                        //                                        {
                                        //                                            x1=list.at(0).second*edgeOfButton+start_x;
                                        //                                            y1=list.at(0).first*edgeOfButton+start_y;
                                        //                                            x2=list.at(1).second*edgeOfButton+start_x;
                                        //                                            y2=list.at(1).first*edgeOfButton+start_y;
                                        //                                            drawLine(button1->x(),button1->y(),x1,y1);
                                        //                                            drawLine(x1,y1,x2,y2);
                                        //                                            drawLine(x2,y2,button2->x(),button2->y());
                                        //                                        }

                                        //                                        qApp->processEvents();
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

//��Ϸ������
void Game_UI::gameTimerEvent(){
    //��������ʱЧ��
    if(ui->timeBar->value() == 0)
    {
        //��Ϸ����
        gameOver();

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

void Game_UI::gameOver()
{
    //����ʱֹͣ
    gameTimer->stop();

    //��Ϸʱ���ڽ�����Ϸ�������ӷ�2*level*ʣ������
    score+=ui->gametime_label->text().toInt()*2*level;
    ui->score_Label->setText(QString::fromLocal8Bit("�÷֣�")+QString::number(score));

    //��ʾ��
    QMessageBox::information(this, "Game Over!", tr("<span style='color: blue; font-size: 24px;'>   Your score:%1 </span/p>\nplay again>_<").arg(QString::number(score)));
    ui->score_Label->setText(QString::fromLocal8Bit("�÷֣�")+QString::number(score));

    //���¿�ʼ
    on_beginButton_clicked();

///////////////////ǿ����ʾ��,Yes��Retry,Cancel  �ֱ� ��Ӧ��Ӱ�죬���¿�ʼ������������
//    QMessageBox msgBox;
//    msgBox.setText(tr("<span style='color: blue; font-size: 24px;'>   Game Over!</span/p>"));
//    msgBox.setInformativeText(tr("Do you want to continue?"));
//    msgBox.setStandardButtons(QMessageBox::Retry
//                              | QMessageBox::Yes
//                              | QMessageBox::No);
//    msgBox.setDefaultButton(QMessageBox::Save);
//    // msgBox.setIconPixmap(QPixmap(":/image/button_icon/fruit/2.png"));
//    msgBox.setIconPixmap(QPixmap(":/image/button_icon/fruit/2.png").scaled(QSize(60,40), Qt::KeepAspectRatio));
//    int ret = msgBox.exec();
//    switch (ret) {
//    case QMessageBox::Retry:
//        qDebug() << "Retry";
//        on_beginButton_clicked();
//        break;
//    case QMessageBox::Yes:
//        qDebug() << "Yes";
//        break;
//    case QMessageBox::No:
//        qDebug() << "No";
//        LinkGame *linkGame_ui=new LinkGame;
//        linkGame_ui->show();
//        delete this;
//        break;
//    }
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
    ui->label3->setVisible(false);
    ui->pauseButton->setText(QString::fromLocal8Bit("��ͣ"));
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
                count--;
                voiceplayer->Play_Voice(2);//����������Ч

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
                //�ж��Ƿ�ȫ������(��Ϸͨ��)
                if(allCleared(gameMap))
                {

                    ////////////////////////////////����ӽ�������
                    gameOver();
                    cout<<"ȫ��ɾ��������"<<endl;
                    ////////////////////////////////
                }

                int** copyGameMap=(int**) malloc(rowSize*sizeof(int*));
                for(int i=0;i<rowSize;i++){
                    copyGameMap[i]=(int*)malloc(columnSize*sizeof(int));
                    for(int j=0;j<columnSize;j++){
                        copyGameMap[i][j]=gameMap[i][j];
                    }
                }
                if(isDeadlock(copyGameMap)&&!allCleared(gameMap)){
                    cout<<"���뽩��"<<endl;
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
    voiceplayer->Stop_Voice();
}

//��ͣ������ť
void Game_UI::on_pauseButton_clicked()
{
    if(!isPause)
    {
        if(isAutoSolve){
            autoProblemSolveThread->stop();
        }

        setAllButtonVisible(false);
        isPause=true;
        gameTimer->stop();
        ui->pauseButton->setText(QString::fromLocal8Bit("����"));
    }
    else if(isPause)
    {
        if(isAutoSolve){
            autoProblemSolveThread->start();
        }

        setAllButtonVisible(true);
        isPause=false;
        gameTimer->start(1000);
        ui->pauseButton->setText(QString::fromLocal8Bit("��ͣ"));
    }
    ui->label3->setVisible(isPause); //�����ڵ�������ͼƬ���Ŀɼ���
    if(isAutoSolve){
        ui->label3->setVisible(false); //�����ڵ�������ͼƬ���Ŀɼ���
        setAllButtonVisible(true);
    }

}

void Game_UI::on_autoSolveProblemButton_clicked()
{
    if(isAutoSolve){
        autoProblemSolveThread->stop();
        ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("�Զ�����"));
    }else{
        isAutoSolve=true;
        autoProblemSolveThread=new AutoProblemSolveThread(gameMap,rowSize,columnSize,true,250);
        connect(autoProblemSolveThread, SIGNAL(drawPathLine(int,int,int,int,QList<Vertex>*)),this, SLOT(drawPathLine_exe(int,int,int,int,QList<Vertex>*)));
        connect(autoProblemSolveThread, SIGNAL(hideButton(int,int,int,int)),this, SLOT(hideButton_exe(int,int,int,int)));
        connect(autoProblemSolveThread, SIGNAL(autoSolveFinish()),this, SLOT(changeAutoState()));
        autoProblemSolveThread->start();
        ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("�ֶ�����"));
    }
}

void Game_UI::on_tipButton_clicked()
{
    if(isDeadlock(gameMap)&&!allCleared(gameMap)){
        cout<<"����"<<endl;
    }
    tip(gameMap);
}
