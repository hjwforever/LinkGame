#include "musicthread.h"

MusicThread::MusicThread()
{
    stopped=false;
}

void MusicThread::stop(){
    stopped = true;
}

void MusicThread::run(){
//    while(!stopped){
////        srand((unsigned)time(NULL));
////        int randNum=1+rand()%2;
////        Sleep(randNum*500);
//        cout<<"11111111111111111"<<endl;
//    }

    cout<<"11111111111111111"<<endl;

    stopped=false;
}
