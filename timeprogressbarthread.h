#ifndef TIMEPROGRESSBARTHREAD_H
#define TIMEPROGRESSBARTHREAD_H

#include <QThread>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <QTimer>
using namespace  std;

class TimeProgressBarThread : public QThread
{
    Q_OBJECT

public:
    TimeProgressBarThread();
    void GamePause();
    void GameContinue();
    void run() override;


signals:
    void TimeStar();
private:
    QTimer *gameTimer;
};

#endif // TIMEPROGRESSBARTHREAD_H
