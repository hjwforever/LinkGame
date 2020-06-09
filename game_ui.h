#ifndef GAME_UI_H
#define GAME_UI_H

#include <QMainWindow>
#include <QPixmap>
#include <QBitmap>
#include"map.h"
#include"mybutton.h"
#include"voiceplayer.h"
#include<QGraphicsScene>
#include<QElapsedTimer>
#include<QGraphicsItem>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include "timeprogressbarthread.h"
#include"autoproblemsolvethread.h"
#include"linklist.h"

namespace Ui {
class Game_UI;
}

class Game_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_UI(QWidget *parent = nullptr);
    ~Game_UI();
    void setLevel(int level);
    int getLevel();
    VoicePlayer *voiceplayer=new VoicePlayer;
    bool allCleared(int** gameMap);
    void initButtonImage();
    void drawLine(int x1,int y1,int x2,int y2);
    void Erasure_Score();
    void setAllButtonVisible(bool visible);//设置按钮是否可见
    void tip(int** gameMap);
    void resetMap();
    bool isDeadlock(int** gameMap_0);
    void gameOver();
    bool hasSollution(int** gameMap);
    void freeGameMap(int** gameMap);

//protected:
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
private:
    QPoint clickPos;

private slots:
    void on_returnButton_clicked();
    void on_beginButton_clicked();
    void slot_myButton_clicked(int row,int y);
    void createGameMap();
    void createEmptyGameMap();
    void on_deleteThread(int x,int y);
    void on_pauseButton_clicked();
    void gameTimerEvent(); // 游戏计时回调
    void on_autoSolveProblemButton_clicked();
    void on_tipButton_clicked();
    //bool autoEliminateBlock(int** gameMap_0,bool showProgress,int index_x1,int index_y1,int index_x2,int index_y2);
    void drawPathLine_exe(int index_x1,int index_y1,int index_x2,int index_y2,QList<Vertex> *list);
    void hideButton_exe(int index_x1,int index_y1,int index_x2,int index_y2);
    void changeAutoState();

    void on_resetButton_clicked();

    void on_prepareButton_clicked();
    void slot_startPK(int** gameMap);

    void slot_ChangeHasPrepared(bool win);

private:

    Ui::Game_UI *ui;
    int level=1;                                 //难度等级
    Map map;                                   //游戏地图
    int** gameMap;                         //存储地图中按钮中编号的二维数�
    int rowSize=10;                         //行的大小
    int columnSize=10;                    //列的大小
    int numOfPic=10;                      //图片种类
    int start_x=20;                        //(0�)按钮的横坐标起始位置，ps�0�)按钮不显�
    int start_y=20;                        //(0�)按钮的纵坐标起始位置
    int edgeOfButton=60;              //按钮边长
    int score = 0;                            //得分
    int continuous_Erasure = 0;      //连消次数
    int erasure_Interval = 0;          //两次消除间隔，ms
    int tipTimes=3;
    bool isPause=false;
    bool isAutoSolve=false;
    bool isPrepared=false;
    QString currentModel[5]={"fruit","animal","gem","face_easy","face_hard"};
    QElapsedTimer Erasure_Time;
    Vertex vertex1,vertex2;
    int count=0;             //解题按钮计数�
    MyButton*** gameButtonMap;//存放按钮地址的二维数�
    QGraphicsScene *Scence;
    QTimer *gameTimer;
    AutoProblemSolveThread *autoProblemSolveThread;
};

#endif // GAME_UI_H
