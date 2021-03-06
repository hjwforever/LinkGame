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
#include"rankinglist.h"

using namespace std;

extern Set_UI *set_ui;
Game_UI::Game_UI(QWidget *parent) :
    MyMainWindow(parent),
    ui(new Ui::Game_UI)
{
    ui->setupUi(this);
    Scence=new QGraphicsScene(this);
    Scence->setSceneRect(0,0,this->width(),this->height());
    ui->game_UI_graphicsView->setScene(Scence);
    ui->score_Label->setStyleSheet("color:white");
    ui->label3->setVisible(false);
    //ui->label->setStyleSheet("color:white");
    this->setMinimumSize(45,45);
    setWindowTitle("LinkGame");

    QPixmap pixmap1(":/image/button_icon/game_ui/restart.png");
    ui->beginButton->resize(pixmap1.size());
    ui->beginButton->setIcon(pixmap1);
    ui->beginButton->setIconSize(pixmap1.size());
    ui->beginButton->setMask(pixmap1.mask());
    ui->beginButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap2(":/image/button_icon/game_ui/pause.png");
    ui->pauseButton->resize(pixmap2.size());
    ui->pauseButton->setIcon(pixmap2);
    ui->pauseButton->setIconSize(pixmap2.size());
    ui->pauseButton->setMask(pixmap2.mask());
    ui->pauseButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap3(":/image/button_icon/game_ui/auto_solve_problem.png");
    ui->autoSolveProblemButton->resize(pixmap3.size());
    ui->autoSolveProblemButton->setIcon(pixmap3);
    ui->autoSolveProblemButton->setIconSize(pixmap3.size());
    ui->autoSolveProblemButton->setMask(pixmap3.mask());
    ui->autoSolveProblemButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap4(":/image/button_icon/game_ui/remind3.png");
    ui->tipButton->resize(pixmap4.size());
    ui->tipButton->setIcon(pixmap4);
    ui->tipButton->setIconSize(pixmap4.size());
    ui->tipButton->setMask(pixmap4.mask());
    ui->tipButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap5(":/image/button_icon/game_ui/reset.png");
    ui->resetButton->resize(pixmap5.size());
    ui->resetButton->setIcon(pixmap5);
    ui->resetButton->setIconSize(pixmap5.size());
    ui->resetButton->setMask(pixmap5.mask());
    ui->resetButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap6(":/image/button_icon/return2.png");
    ui->returnButton->resize(pixmap6.size());
    ui->returnButton->setIcon(pixmap6);
    ui->returnButton->setIconSize(pixmap6.size());
    ui->returnButton->setMask(pixmap6.mask());
    ui->returnButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap7(":/image/button_icon/game_ui/prepare.png");
    ui->prepareButton->resize(pixmap7.size());
    ui->prepareButton->setIcon(pixmap7);
    ui->prepareButton->setIconSize(pixmap7.size());
    ui->prepareButton->setMask(pixmap7.mask());
    ui->prepareButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap8(":/image/button_icon/linkgame_ui/list.png");
    ui->rankingListButton->resize(pixmap8.size());
    ui->rankingListButton->setIcon(pixmap8);
    ui->rankingListButton->setIconSize(pixmap8.size());
    ui->rankingListButton->setMask(pixmap8.mask());
    ui->rankingListButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap9(":/image/button_icon/game_ui/playback.png");
    ui->rePlayToolButton->resize(pixmap9.size());
    ui->rePlayToolButton->setIcon(pixmap9);
    ui->rePlayToolButton->setIconSize(pixmap9.size());
    ui->rePlayToolButton->setMask(pixmap9.mask());
    ui->rePlayToolButton->setStyleSheet("QToolButton{border:0px;}");

    if(!set_ui->isTwoPeople){
        ui->rankingListButton->hide();
    }

    ui->rePlayToolButton->hide();
    ui->win_lose_gameover_Label->hide();

    ui->name_Label->setText(set_ui->name);
    connect(set_ui, SIGNAL(signal_startPK(int**)),this, SLOT(slot_startPK(int**)));
    connect(set_ui, SIGNAL(signal_ChangeHasPrepared(bool)),this, SLOT(slot_ChangeHasPrepared(bool)));

}

Game_UI::~Game_UI()
{
    delete ui;
}

void Game_UI::closeEvent(QCloseEvent *event){
    if(set_ui->hasLogin){
        if(set_ui->isTwoPeople&&set_ui->ispking){
            set_ui->tcpsocket->write("MIDFIELDEXIT");
        }
        set_ui->tcpsocket->disconnectFromHost();
    }
    exit(0);
}

void Game_UI::freeGameMap(int** gameMap){
    for(int i=0;i<rowSize;i++){
        free(gameMap[i]);
        gameMap[i]=nullptr;
    }
}

bool Game_UI::hasSollution(int** gameMap){
    int** copyGameMap=(int**) malloc(rowSize*sizeof(int*));
    for(int i=0;i<rowSize;i++){
        copyGameMap[i]=(int*)malloc(columnSize*sizeof(int));
        for(int j=0;j<columnSize;j++){
            copyGameMap[i][j]=gameMap[i][j];
        }
    }

    while(!allCleared(copyGameMap)){
        bool hasSollution=false;
        for(int i=1;i<=rowSize-2;i++){
            for(int j=1;j<=columnSize-2;j++){
                if(copyGameMap[i][j]!=0){
                    for (int m=1;m<=rowSize-2;m++) {
                        for(int n=1;n<=columnSize-2;n++){
                            if(copyGameMap[m][n]!=0&&copyGameMap[i][j]==copyGameMap[m][n]){
                                QList<Vertex> *list=new QList<Vertex>();
                                int turnNum = map.canLink_2(copyGameMap,i,j,m,n,*list);
                                if(turnNum!=-1){
                                    hasSollution=true;
                                    copyGameMap[i][j]=0;
                                    copyGameMap[m][n]=0;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(!hasSollution) {
            return false;
//            cout<<"无解 hasSollution(int** gameMap)"<<endl;
            break;
        }
    }
    return true;
    /////////////////////////////////////////////////释放copyGameMap内存
}

void Game_UI::resetMap(){
    LinkList<Vertex*> *remainVertexList=new LinkList<Vertex*>;
    LinkList<int> *remainPictrueList=new LinkList<int>;
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize;j++){
            if(gameMap[i][j]){
                Vertex *vertex=new Vertex();
                vertex->first=i;
                vertex->second=j;
                remainVertexList->tailInsert(vertex);
                remainPictrueList->tailInsert(gameMap[i][j]);
            }
        }
    }

    srand(time(NULL));

    while (remainVertexList->getLen()) {
        int randNum=rand()%remainVertexList->getLen();
        Vertex *tempVertex;
        remainVertexList->del(randNum,tempVertex);
        int picIndex=0;
        remainPictrueList->del(0,picIndex);
        gameMap[tempVertex->first][tempVertex->second]=picIndex;
        gameButtonMap[tempVertex->first][tempVertex->second]->setStyleSheet(QString("QPushButton{border-image: url(:/image/button_icon/%1/%2.png)}").arg(currentModel[set_ui->currentModelNum]).arg(picIndex).toLatin1().data());
    }

    while(!hasSollution(gameMap)){
        resetMap();
    }

    remainVertexList->~LinkList();
    remainPictrueList->~LinkList();
}

void Game_UI::changeAutoState(){
    if(!isPause){
        if(isAutoSolve){
            isAutoSolve=false;
            //ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("自动解题"));
            QPixmap pixmap1(":/image/button_icon/game_ui/auto_solve_problem.png");
            ui->autoSolveProblemButton->resize(pixmap1.size());
            ui->autoSolveProblemButton->setIcon(pixmap1);
            ui->autoSolveProblemButton->setIconSize(pixmap1.size());
            ui->autoSolveProblemButton->setMask(pixmap1.mask());
            ui->autoSolveProblemButton->setStyleSheet("QToolButton{border:0px;}");
        }else{
            isAutoSolve=true;
            //ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("手动解题"));
            QPixmap pixmap1(":/image/button_icon/game_ui/manual_problem_solving.png");
            ui->autoSolveProblemButton->resize(pixmap1.size());
            ui->autoSolveProblemButton->setIcon(pixmap1);
            ui->autoSolveProblemButton->setIconSize(pixmap1.size());
            ui->autoSolveProblemButton->setMask(pixmap1.mask());
            ui->autoSolveProblemButton->setStyleSheet("QToolButton{border:0px;}");
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
    QPoint pointa(x1+edgeOfButton/2,y1+edgeOfButton/2);  //点A
    QPoint pointb(x2+edgeOfButton/2,y2+edgeOfButton/2);  //点B
    QPen pen;
    pen.setColor("white");
    pen.setWidth(4);
    QLine line(pointa,pointb);
    ///////////////////////////////////
//    cout<<"坐标："<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<endl;
    ////////////////////////////////////
    Scence->addLine(line,pen);
    ui->game_UI_graphicsView->update();
    DeleteQGraphicsItemThread *thread=new DeleteQGraphicsItemThread(x1+edgeOfButton/2,y1+edgeOfButton/2);
    thread->start();
    connect(thread, SIGNAL(deleteItem(int,int)),this, SLOT(on_deleteThread(int,int)));
}

void Game_UI::drawPathLine_exe(int index_x1,int index_y1,int index_x2,int index_y2,QList<Vertex> *list){
//    cout<<"drawPathLine"<<endl;
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

    //判断是否全部消除(游戏通关)
//    if(allCleared(gameMap))
//    {
//        //gameOver();
//        cout<<"全部删除！！！"<<endl;
//    }
}

void Game_UI::hideButton_exe(int index_x1,int index_y1,int index_x2,int index_y2){
    gameButtonMap[index_x1][index_y1]->hide();
    gameButtonMap[index_x2][index_y2]->hide();
    Erasure_Score();
    //判断是否全部消除(游戏通关)
    if(allCleared(gameMap))
    {
        gameOver();
//        cout<<"全部删除！！！"<<endl;
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
    ui->score_Label->setText(QString::fromLocal8Bit("得分：")+QString::number(score));
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

//bool Game_UI::autoEliminateBlock(int** gameMap_0,bool showProgress,int index_x1,int index_y1,int index_x2,int index_y2){
//    cout<<"showProgress "<<showProgress<<" "<<index_x1<<" "<<index_y1<<" "<<index_x2<<" "<<index_y2<<endl;
//    if(gameMap_0[index_x1][index_y1] == gameMap_0[index_x2][index_y2])
//    {
//        QList<Vertex> list;
//        int turnNum = map.canLink_2(gameMap_0,index_x1,index_y1,index_x2,index_y2,list);
//        if(turnNum!=-1)//判断能否连接消除
//        {
//            //判断是否全部消除(游戏通关)
//            if(allCleared(gameMap_0))
//            {
//                ////////////////////////////////待添加结束界面
//                gameOver();
//                cout<<"全部删除！！！"<<endl;
//                ////////////////////////////////
//            }
//            return true;
//        }
//        else
//        {
//            //voiceplayer->Play_Voice(1);//播放按钮音效
//            return false;
//        }
//        voiceplayer->Stop_Voice();
//    }
//    else
//    {
//        //voiceplayer->Play_Voice(1);//播放按钮音效
//        return false;
//    }
//}

/*
 *判定僵局
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
                                    if(turnNum!=-1)//判断能否连接消除
                                    {
                                        //画线
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

//游戏进度条
void Game_UI::gameTimerEvent(){
    //进度条计时效果
    if(ui->timeBar->value() == 0)
    {
        //游戏结束
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
    if(!set_ui->isTwoPeople){
        ui->rePlayToolButton->show();
    }

    setAllButtonVisible(false);

    if(!set_ui->ispking){
        QPixmap myPix(":/image/button_icon/game_over_pink.png");
        ui->win_lose_gameover_Label->setPixmap(myPix);
        ui->win_lose_gameover_Label->setScaledContents(true);
        ui->win_lose_gameover_Label->show();
        //显示gameover图片////////////////////////////////////////////////////////////////////////////////
    }

    if(set_ui->hasLogin){
        QString endMsg="END:"+set_ui->mail;
        set_ui->tcpsocket->write(endMsg.toUtf8().data());
    }

    //倒计时停止
    if(!set_ui->ispking) gameTimer->stop();


    //游戏时限内结束游戏，奖励加分2*level*剩余秒数
    score+=ui->gametime_label->text().toInt()*2*level;
    ui->score_Label->setText(QString::fromLocal8Bit("得分：")+QString::number(score));

//    //提示框
//    QMessageBox::information(this, "Game Over!", tr("<span style='color: blue; font-size: 24px;'>   Your score:%1").arg(QString::number(score)));
//    ui->score_Label->setText(QString::fromLocal8Bit("得分：")+QString::number(score));


    //重新开始
    //if(!set_ui->ispking) on_beginButton_clicked();


///////////////////强制提示框,Yes，Retry,Cancel  分别 对应无影响，重新开始，返回主界面
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
    if(isAutoSolve)
    {
        autoProblemSolveThread->stop();
        Sleep(500);
    }

    freeGameMap(gameMap);
    if(rePlay_vertex_queue->length()!=0){
        rePlay_vertex_queue->~QQueue();
    }

    if(set_ui->isTwoPeople){
        if(set_ui->ispking){
            set_ui->tcpsocket->write("MIDFIELDEXIT");
        }
        LinkGame *linkgame=new LinkGame;
        linkgame->show();
    }else{
        ChooseLevel_UI *chooseLevel_ui=new ChooseLevel_UI;
        chooseLevel_ui->show();
    }

    //此处可能呀清空游戏数据

    delete this;
}

void Game_UI::on_beginButton_clicked()
{
    ui->rePlayToolButton->hide();
    tipTimes=3;
//    ui->label->setText(QString::fromLocal8Bit("%1/3").arg(QString::number(tipTimes)));
    QPixmap pixmap4(QString(":/image/button_icon/game_ui/remind%1.png").arg(QString::number(tipTimes)));
    ui->tipButton->resize(pixmap4.size());
    ui->tipButton->setIcon(pixmap4);
    ui->tipButton->setIconSize(pixmap4.size());
    ui->tipButton->setMask(pixmap4.mask());
    ui->tipButton->setStyleSheet("QToolButton{border:0px;}");
    freeGameMap(gameMap);

    if(isRePlay){
        isRePlay=false;
        rePlayTimer->stop();
    }

    if(rePlay_vertex_queue->length()!=0){
        rePlay_vertex_queue->clear();
    }

    if(isAutoSolve){
        autoProblemSolveThread->stop();
    }
    ui->label3->setVisible(false);
    ui->win_lose_gameover_Label->setVisible(false);
//    ui->pauseButton->setText(QString::fromLocal8Bit("暂停"));

    QPixmap pixmap1(":/image/button_icon/game_ui/pause.png");
    ui->pauseButton->resize(pixmap1.size());
    ui->pauseButton->setIcon(pixmap1);
    ui->pauseButton->setIconSize(pixmap1.size());
    ui->pauseButton->setMask(pixmap1.mask());
    ui->pauseButton->setStyleSheet("QToolButton{border:0px;}");

    ui->timeBar->setValue(60);
    ui->gametime_label->setText(QString::number(59));
    gameTimer->stop();
    gameTimer=new QTimer;
    gameTimer->start(1000);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));
    gameMap=map.creatMap(rowSize,columnSize,level,numOfPic);

    rePlayGameMap=(int**) malloc(rowSize*sizeof(int*));
    for(int i=0;i<rowSize;i++){
        rePlayGameMap[i]=(int*)malloc(columnSize*sizeof(int));
        for(int j=0;j<columnSize;j++){
            rePlayGameMap[i][j]=gameMap[i][j];
        }
    }

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
//    qDebug()<<"creatGameMap";
    // 进度条
    ui->gametime_label->setText("59");
    ui->gametime_label->setStyleSheet("color:white");
    ui->score_Label->setStyleSheet("color:white");
    ui->timeBar->setTextVisible(false);
    ui->timeBar->setMaximum(60);
    ui->timeBar->setMinimum(0);
    ui->timeBar->setValue(60);
    // 游戏计时器
    gameTimer = new QTimer;
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));
    gameTimer->start(1000);


    ui->prepareButton->hide();
    MyButton *button=new MyButton;
    gameButtonMap=(MyButton***) malloc(rowSize*sizeof(MyButton**));
    for(int i=0;i<rowSize;i++){
        gameButtonMap[i]=(MyButton**)malloc(columnSize*sizeof(MyButton*));
        for(int j=0;j<columnSize;j++){
            gameButtonMap[i][j]=button;
        }
    }

    gameMap=map.creatMap(rowSize,columnSize,level,numOfPic);

    rePlayGameMap=(int**) malloc(rowSize*sizeof(int*));
    for(int i=0;i<rowSize;i++){
        rePlayGameMap[i]=(int*)malloc(columnSize*sizeof(int));
        for(int j=0;j<columnSize;j++){
            rePlayGameMap[i][j]=gameMap[i][j];
        }
    }

    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            /////////////////
//            cout<<gameMap[i][j]<<"\t";
            ///////////////////////
            MyButton *myButton=new MyButton;
            myButton->setParent(this);
            myButton->setCoordinate(i,j);
            myButton->setGeometry(start_x+j*edgeOfButton,start_y+i*edgeOfButton,edgeOfButton,edgeOfButton);
            myButton->show();
            //连接信号槽，传递button的数组下标
            connect(myButton, SIGNAL(clicked(int,int)),this, SLOT(slot_myButton_clicked(int,int)));
            //myButton->setText(QString::number(gameMap[i][j]));
            gameButtonMap[i][j]=myButton;
        }
        /////////////////
//        cout<<endl;
        //////////////////
    }
    initButtonImage();
}

void Game_UI::createEmptyGameMap(){
    // 进度条
    ui->gametime_label->setText("59");
    ui->gametime_label->setStyleSheet("color:white");
    ui->score_Label->setStyleSheet("color:white");
    ui->timeBar->setTextVisible(false);
    ui->timeBar->setMaximum(60);
    ui->timeBar->setMinimum(0);
    ui->timeBar->setValue(60);

    ui->beginButton->hide();
    ui->autoSolveProblemButton->hide();
    ui->pauseButton->hide();
    ui->resetButton->hide();

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
            MyButton *myButton=new MyButton;
            myButton->setParent(this);
            myButton->setCoordinate(i,j);
            myButton->setGeometry(start_x+j*edgeOfButton,start_y+i*edgeOfButton,edgeOfButton,edgeOfButton);
            //myButton->show();
            //连接信号槽，传递button的数组下标
            connect(myButton, SIGNAL(clicked(int,int)),this, SLOT(slot_myButton_clicked(int,int)));
            //myButton->setText(QString::number(gameMap[i][j]));
            gameButtonMap[i][j]=myButton;
        }
    }
}

void Game_UI::setAllButtonVisible(bool visible){
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
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

void Game_UI::slot_myButton_clicked(int row,int column){
    if(!isRePlay){
        Vertex *rePlayVertex=new Vertex;
        rePlayVertex->first=row;
        rePlayVertex->second=column;
        rePlay_vertex_queue->enqueue(rePlayVertex);
    }

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
//                for(int i=0;i<list.length();i++)//**************************************************
//                {
////                    cout<<i<<"hhhhhhhhhh"<<list.at(i).first<<" "<<list.at(i).second<<endl;
//                }//*******************************************************************************

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
                    gameOver();
//                    cout<<"全部删除！！！"<<endl;
                    ////////////////////////////////
                }

//                int** copyGameMap=(int**) malloc(rowSize*sizeof(int*));
//                for(int i=0;i<rowSize;i++){
//                    copyGameMap[i]=(int*)malloc(columnSize*sizeof(int));
//                    for(int j=0;j<columnSize;j++){
//                        copyGameMap[i][j]=gameMap[i][j];
//                    }
//                }
                if(isDeadlock(gameMap)&&!allCleared(gameMap)){
                    resetMap();
//                    cout<<"陷入僵局"<<endl;
                }
            }
            else
            {
                voiceplayer->Play_Voice(1);//播放按钮音效
                vertex1.first = row;
                vertex1.second = column;
            }

            list.~QList();
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
    //voiceplayer->Stop_Voice();
    voiceplayer->~VoicePlayer();
//    delete voiceplayer;
//    voiceplayer=nullptr;
}

//暂停继续按钮
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
//        ui->pauseButton->setText(QString::fromLocal8Bit("继续"));
        QPixmap pixmap1(":/image/button_icon/game_ui/continue.png");
        ui->pauseButton->resize(pixmap1.size());
        ui->pauseButton->setIcon(pixmap1);
        ui->pauseButton->setIconSize(pixmap1.size());
        ui->pauseButton->setMask(pixmap1.mask());
        ui->pauseButton->setStyleSheet("QToolButton{border:0px;}");
    }
    else if(isPause)
    {
        if(isAutoSolve){
            autoProblemSolveThread->start();
        }

        setAllButtonVisible(true);
        isPause=false;
        gameTimer->start(1000);
//        ui->pauseButton->setText(QString::fromLocal8Bit("暂停"));
        QPixmap pixmap1(":/image/button_icon/game_ui/pause.png");
        ui->pauseButton->resize(pixmap1.size());
        ui->pauseButton->setIcon(pixmap1);
        ui->pauseButton->setIconSize(pixmap1.size());
        ui->pauseButton->setMask(pixmap1.mask());
        ui->pauseButton->setStyleSheet("QToolButton{border:0px;}");
    }
    ui->label3->setVisible(isPause); //设置遮挡画布（图片）的可见性
    if(isAutoSolve){
        ui->label3->setVisible(false); //设置遮挡画布（图片）的可见性
        setAllButtonVisible(true);
    }

}

void Game_UI::on_autoSolveProblemButton_clicked()
{
    if(isAutoSolve){
        autoProblemSolveThread->stop();
//        ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("自动解题"));
        QPixmap pixmap1(":/image/button_icon/game_ui/auto_solve_problem.png");
        ui->autoSolveProblemButton->resize(pixmap1.size());
        ui->autoSolveProblemButton->setIcon(pixmap1);
        ui->autoSolveProblemButton->setIconSize(pixmap1.size());
        ui->autoSolveProblemButton->setMask(pixmap1.mask());
        ui->autoSolveProblemButton->setStyleSheet("QToolButton{border:0px;}");
    }else{
        isAutoSolve=true;
        autoProblemSolveThread=new AutoProblemSolveThread(gameMap,rowSize,columnSize,true,250);
        connect(autoProblemSolveThread, SIGNAL(drawPathLine(int,int,int,int,QList<Vertex>*)),this, SLOT(drawPathLine_exe(int,int,int,int,QList<Vertex>*)));
        connect(autoProblemSolveThread, SIGNAL(hideButton(int,int,int,int)),this, SLOT(hideButton_exe(int,int,int,int)));
        connect(autoProblemSolveThread, SIGNAL(autoSolveFinish()),this, SLOT(changeAutoState()));
        autoProblemSolveThread->start();
//        ui->autoSolveProblemButton->setText(QString::fromLocal8Bit("手动解题"));
        QPixmap pixmap1(":/image/button_icon/game_ui/manual_problem_solving.png");
        ui->autoSolveProblemButton->resize(pixmap1.size());
        ui->autoSolveProblemButton->setIcon(pixmap1);
        ui->autoSolveProblemButton->setIconSize(pixmap1.size());
        ui->autoSolveProblemButton->setMask(pixmap1.mask());
        ui->autoSolveProblemButton->setStyleSheet("QToolButton{border:0px;}");
    }
}

void Game_UI::on_tipButton_clicked()
{
    if(set_ui->isTwoPeople&&!set_ui->ispking)
        return;
    if(tipTimes>0){
        tipTimes--;
        //ui->label->setText(QString::fromLocal8Bit("%1/3").arg(QString::number(tipTimes)));
        QPixmap pixmap4(QString(":/image/button_icon/game_ui/remind%1.png").arg(QString::number(tipTimes)));
        ui->tipButton->resize(pixmap4.size());
        ui->tipButton->setIcon(pixmap4);
        ui->tipButton->setIconSize(pixmap4.size());
        ui->tipButton->setMask(pixmap4.mask());
        ui->tipButton->setStyleSheet("QToolButton{border:0px;}");
//        if(isDeadlock(gameMap)&&!allCleared(gameMap)){
//            cout<<"僵局"<<endl;
//        }
        tip(gameMap);

        if(score<5){
            score=0;
        }else{
            score-=5;
        }
        ui->score_Label->setText(QString::fromLocal8Bit("得分：")+QString::number(score));
    }
}

void Game_UI::on_resetButton_clicked()
{
    resetMap();
    if(score<5){
        score=0;
    }else{
        score-=5;
    }
    ui->score_Label->setText(QString::fromLocal8Bit("得分：")+QString::number(score));
}

void Game_UI::on_prepareButton_clicked()
{
    ui->win_lose_gameover_Label->hide();
    if(!isPrepared){
        QString pkMsg="PK:"+set_ui->mail;
        set_ui->tcpsocket->write(pkMsg.toUtf8().data());
//        ui->prepareButton->setText(QString::fromLocal8Bit("取消准备"));
        QPixmap pixmap1(":/image/button_icon/game_ui/cancel_prepare.png");
        ui->prepareButton->resize(pixmap1.size());
        ui->prepareButton->setIcon(pixmap1);
        ui->prepareButton->setIconSize(pixmap1.size());
        ui->prepareButton->setMask(pixmap1.mask());
        ui->prepareButton->setStyleSheet("QToolButton{border:0px;}");
        isPrepared=true;
    }else{
        set_ui->tcpsocket->write("CANCALPK");
//        ui->prepareButton->setText(QString::fromLocal8Bit("准备"));
        QPixmap pixmap2(":/image/button_icon/game_ui/prepare.png");
        ui->prepareButton->resize(pixmap2.size());
        ui->prepareButton->setIcon(pixmap2);
        ui->prepareButton->setIconSize(pixmap2.size());
        ui->prepareButton->setMask(pixmap2.mask());
        ui->prepareButton->setStyleSheet("QToolButton{border:0px;}");
        isPrepared=false;
    }

}

void Game_UI::slot_startPK(int** pkgameMap){
    tipTimes=3;
//    ui->label->setText(QString::fromLocal8Bit("%1/3").arg(QString::number(tipTimes)));
    QPixmap pixmap4(QString(":/image/button_icon/game_ui/remind%1.png").arg(QString::number(tipTimes)));
    freeGameMap(gameMap);
    if(isAutoSolve){
        autoProblemSolveThread->stop();
    }
    ui->label3->setVisible(false);

    this->gameMap=pkgameMap;
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

    ui->prepareButton->hide();
    ui->win_lose_gameover_Label->hide();
}

void Game_UI::slot_ChangeHasPrepared(bool win){
    setAllButtonVisible(false);
    if(win){
        QPixmap myPix(":/image/button_icon/win_pink.png");
        ui->win_lose_gameover_Label->setPixmap(myPix);
        ui->win_lose_gameover_Label->setScaledContents(true);
        ui->win_lose_gameover_Label->show();
        //胜利的图片///////////////////////////////////////////////////////////////////////////////////////////////
    }else{
        QPixmap myPix(":/image/button_icon/lose_pink.png");
        ui->win_lose_gameover_Label->setPixmap(myPix);
        ui->win_lose_gameover_Label->setScaledContents(true);
        ui->win_lose_gameover_Label->show();
        //输的图片
    }

    ui->prepareButton->show();
    if(!isPrepared){
        QPixmap pixmap1(":/image/button_icon/game_ui/cancel_prepare.png");
        ui->prepareButton->resize(pixmap1.size());
        ui->prepareButton->setIcon(pixmap1);
        ui->prepareButton->setIconSize(pixmap1.size());
        ui->prepareButton->setMask(pixmap1.mask());
        ui->prepareButton->setStyleSheet("QToolButton{border:0px;}");
//        ui->prepareButton->setText(QString::fromLocal8Bit("取消准备"));
        isPrepared=true;
    }else{
        QPixmap pixmap1(":/image/button_icon/game_ui/prepare.png");
        ui->prepareButton->resize(pixmap1.size());
        ui->prepareButton->setIcon(pixmap1);
        ui->prepareButton->setIconSize(pixmap1.size());
        ui->prepareButton->setMask(pixmap1.mask());
        ui->prepareButton->setStyleSheet("QToolButton{border:0px;}");
//        ui->prepareButton->setText(QString::fromLocal8Bit("准备"));
        isPrepared=false;
    }

}

//void Game_UI::mousePressEvent(QMouseEvent *event)
//{
////    if (event->button() == Qt::LeftButton) {
////        pos = event->globalPos() - frameGeometry().topLeft();
////        event->accept();
////    }

//    if(event->button()==Qt::LeftButton)
//        clickPos=event->pos();

//}

//void Game_UI::mouseMoveEvent(QMouseEvent *event)
//{
////    if (event->buttons() & Qt::LeftButton) {
////        move(event->globalPos() - pos);
////        event->accept();
////    }
//    if(event->buttons()&Qt::LeftButton)
//        move(event->pos()+pos()-clickPos);
//}

void Game_UI::on_rankingListButton_clicked()
{
    RankingList *rankingList=new RankingList;
    rankingList->show();
    if(set_ui->hasLogin){
        QString getRankMsg="GETRANK:"+set_ui->mail;
        set_ui->tcpsocket->write(getRankMsg.toUtf8().data());
    }

}

//回放按钮
void Game_UI::on_rePlayToolButton_clicked()
{
    if(isRePlay){
//        ui->rePlayToolButton->setText(QString::fromLocal8Bit("回放"));
        QPixmap pixmap1(":/image/button_icon/game_ui/playback.png");
        ui->rePlayToolButton->resize(pixmap1.size());
        ui->rePlayToolButton->setIcon(pixmap1);
        ui->rePlayToolButton->setIconSize(pixmap1.size());
        ui->rePlayToolButton->setMask(pixmap1.mask());
        ui->rePlayToolButton->setStyleSheet("QToolButton{border:0px;}");
        isRePlay=false;
        rePlayTimer->stop();
    }else{
        ui->win_lose_gameover_Label->hide();
//        ui->rePlayToolButton->setText(QString::fromLocal8Bit("暂停回放"));
        QPixmap pixmap1(":/image/button_icon/game_ui/pause_playback.png");
        ui->rePlayToolButton->resize(pixmap1.size());
        ui->rePlayToolButton->setIcon(pixmap1);
        ui->rePlayToolButton->setIconSize(pixmap1.size());
        ui->rePlayToolButton->setMask(pixmap1.mask());
        ui->rePlayToolButton->setStyleSheet("QToolButton{border:0px;}");
        isRePlay=true;
        if(!set_ui->isTwoPeople){
            gameMap=rePlayGameMap;
            for(int i=1;i<rowSize-1;i++){
                for(int j=1;j<columnSize-1;j++){
                    //gameButtonMap[i][j]->setText(QString::number(gameMap[i][j]));
                    if(gameMap[i][j]!=0){
                        gameButtonMap[i][j]->show();
                    }
                }
            }
            initButtonImage();

            rePlayTimer = new QTimer;
            connect(rePlayTimer, SIGNAL(timeout()), this, SLOT(slot_rePlay()));
            rePlayTimer->start(500);
        }
    }
}

void Game_UI::slot_rePlay(){
    if(rePlay_vertex_queue->length()!=0){
        Vertex *rePlayVertex;
        rePlayVertex=rePlay_vertex_queue->dequeue();
        slot_myButton_clicked(rePlayVertex->first,rePlayVertex->second);
    }else{
        isRePlay=false;
        rePlayTimer->stop();
        freeGameMap(rePlayGameMap);
//        ui->rePlayToolButton->setText(QString::fromLocal8Bit("回放"));
        QPixmap pixmap1(":/image/button_icon/game_ui/playback.png");
        ui->rePlayToolButton->resize(pixmap1.size());
        ui->rePlayToolButton->setIcon(pixmap1);
        ui->rePlayToolButton->setIconSize(pixmap1.size());
        ui->rePlayToolButton->setMask(pixmap1.mask());
        ui->rePlayToolButton->setStyleSheet("QToolButton{border:0px;}");
        ui->rePlayToolButton->hide();
    }
}
