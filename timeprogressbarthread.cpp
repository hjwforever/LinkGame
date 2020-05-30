#include "timeprogressbarthread.h"

TimeProgressBarThread::TimeProgressBarThread()
{
    // 游戏计时器
    gameTimer = new QTimer(this);
//    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));

}

void TimeProgressBarThread::GamePause(){
    gameTimer->stop();
}

void TimeProgressBarThread::GameContinue(){
    gameTimer->start(1000);
}

void TimeProgressBarThread::run(){
    gameTimer->start(1000);
    emit TimeStar();

    cout<<"time star"<<endl;
}
