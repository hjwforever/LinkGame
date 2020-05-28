#ifndef MUSICTHREAD_H
#define MUSICTHREAD_H

#include <QThread>
#include <iostream>
#include<windows.h>
#include <QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QMediaPlaylist>

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
    void InitMusicPlayer();
    QMediaPlayer *gameSound ;//= new QMediaPlayer;//创建播放器
    QMediaPlaylist *gameList; //= new QMediaPlaylist;//创建播放链表

private:
    volatile bool stopped;
};

#endif // MUSICTHREAD_H
