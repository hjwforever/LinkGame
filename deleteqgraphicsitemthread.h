#ifndef DELETEQGRAPHICSITEMTHREAD_H
#define DELETEQGRAPHICSITEMTHREAD_H

#include <QThread>
#include <iostream>
#include<windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class DeleteQGraphicsItemThread : public QThread
{
    Q_OBJECT
public:
    DeleteQGraphicsItemThread();
    DeleteQGraphicsItemThread(int x,int y);
    void stop();
    void run() override;

signals:
    void deleteItem(int x,int y);

private:
    volatile bool stopped;
    int x=0;
    int y=0;
};

#endif // DELETEQGRAPHICSITEMTHREAD_H
