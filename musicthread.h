#ifndef MUSICTHREAD_H
#define MUSICTHREAD_H

#include <QThread>
#include <iostream>
#include<windows.h>

#include <cstdlib>
#include <ctime>

using namespace std;

class MusicThread : public QThread
{
    Q_OBJECT
public:
    MusicThread();
    void stop();
    void run() override;

private:
    volatile bool stopped;
};

#endif // MUSICTHREAD_H
