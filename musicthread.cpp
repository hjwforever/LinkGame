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
    stopped=false;
}

