#include "autoproblemsolvethread.h"

AutoProblemSolveThread::AutoProblemSolveThread()
{
}

AutoProblemSolveThread::AutoProblemSolveThread(int** gameMap_0,int rowSize,int columnSize,bool showProgress,int sleepTime)
{
    stopped=false;
    this->gameMap=gameMap_0;
    this->showProgress=showProgress;
    this->sleepTime=sleepTime;
    this->rowSize=rowSize;
    this->columnSize=columnSize;
}

void AutoProblemSolveThread::stop(){
    stopped=true;
}

void AutoProblemSolveThread::run(){

    for(int i=0;i<rowSize;i++){
        for(int j=0;j<columnSize;j++){
            cout<<gameMap[i][j]<<" ";
        }
        cout<<endl;
    }

    while(!allCleared(gameMap,rowSize,columnSize)){
        if(stopped) break;
        bool hasSollution=false;
        for(int i=1;i<=rowSize-2;i++){
            if(stopped) break;
            for(int j=1;j<=columnSize-2;j++){
                if(stopped) break;
                if(gameMap[i][j]!=0){
                    for (int m=1;m<=rowSize-2;m++) {
                        if(stopped) break;
                        for(int n=1;n<=columnSize-2;n++){
                            if(stopped) break;
                            if(gameMap[m][n]!=0&&gameMap[i][j]==gameMap[m][n]){
                                QList<Vertex> *list=new QList<Vertex>();
                                int turnNum = map.canLink_2(gameMap,i,j,m,n,*list);
                                if(!stopped&&turnNum!=-1){
                                    hasSollution=true;
                                    Sleep(sleepTime);
                                    gameMap[i][j]=0;
                                    gameMap[m][n]=0;
                                    emit drawPathLine(i,j,m,n,list);
                                    Sleep(300);
                                    emit hideButton(i,j,m,n);
                                }
                            }
                        }
                    }
                }
            }
        }
        if(!hasSollution) {
            cout<<"нч╫Б AutoProblemSolveThread"<<endl;
            break;
        }
        if(!showProgress){
            break;
        }
    }
    emit autoSolveFinish();
    stopped=false;
}

bool AutoProblemSolveThread::allCleared(int** gameMap,int rowSize,int columnSize)
{
    for(int i=1;i<rowSize-1;i++){
        for(int j=1;j<columnSize-1;j++){
            if(gameMap[i][j] != 0)
                return false;
        }
    }
    return true;
}
