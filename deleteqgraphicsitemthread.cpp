#include "deleteqgraphicsitemthread.h"

DeleteQGraphicsItemThread::DeleteQGraphicsItemThread()
{
}

DeleteQGraphicsItemThread::DeleteQGraphicsItemThread(int x,int y)
{
    stopped=false;
    this->x=x;
    this->y=y;
}

void DeleteQGraphicsItemThread::stop(){
    stopped=true;
}

void DeleteQGraphicsItemThread::run(){
    Sleep(200);
    emit deleteItem(x,y);
    stopped=false;
}
