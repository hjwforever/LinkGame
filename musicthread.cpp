#include "musicthread.h"

MusicThread::MusicThread()
{
    stopped=false;

}

void MusicThread::stop(){
    gameSound->pause();
}

void MusicThread::run(){

    gameSound->play();
    cout<<"11111111111111111"<<endl;

    stopped=false;
}

