#ifndef AUTOPROBLEMSOLVETHREAD_H
#define AUTOPROBLEMSOLVETHREAD_H

#include <QThread>
#include <iostream>
#include<windows.h>
#include <cstdlib>
#include <ctime>

#include"map.h"

using namespace std;

class AutoProblemSolveThread : public QThread
{
    Q_OBJECT
public:
    AutoProblemSolveThread();
    AutoProblemSolveThread(int** gameMap_0,int rowSize,int columnSize,bool showProgress,int sleepTime);
    void stop();
    void run() override;

    bool allCleared(int** gameMap,int rowSize,int columnSize);

signals:
    void drawPathLine(int index_x1,int index_y1,int index_x2,int index_y2,QList<Vertex> *list);
    void eliminate(int** gameMap_0,bool showProgress,int index_x1,int index_y1,int index_x2,int index_y2);
    void hideButton(int index_x1,int index_y1,int index_x2,int index_y2);
    void autoSolveFinish();

private:
    volatile bool stopped;
    int** gameMap=nullptr;
    int rowSize=10;
    int columnSize=10;
    int sleepTime=500;
    bool showProgress=true;
    Map map;
};

#endif // AUTOPROBLEMSOLVETHREAD_H
