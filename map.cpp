#include "map.h"

#include<time.h>

#include"linklist.h"

Map::Map()
{

}

/*
 * 此处的rowSize和columnSize为包括外围一圈的行和列数
 * picNum为图标种类数
 */
int** Map::creatMap(int rowSize,int columnSize,int level,int picNum){
    LinkList<Vertex> emptyVertexList;   //存放空的点的链表
    this->maxsize=rowSize;
    //生成rowSize行columnSize的数组并初始化每一个元素为0
    int** map=(int**) malloc(rowSize*sizeof(int*));
     for(int i=0;i<rowSize;i++){
         map[i]=(int*)malloc(columnSize*sizeof(int));
         for(int j=0;j<columnSize;j++){
             map[i][j]=0;
             if(i!=0&&i!=rowSize-1&&j!=0&&j!=columnSize-1){     //初始化空点的链表
                 Vertex vertex;
                 vertex.first=i;
                 vertex.second=j;
                 emptyVertexList.tailInsert(vertex);
             }
         }
     }

     srand(time(NULL));

     int i=0;
     while(emptyVertexList.getLen()){

         bool allTraped=true;                                   //空的点位是否全部碰壁

         for(int i=0;i<emptyVertexList.getLen();i++){
             Vertex tempVertex;
             emptyVertexList.get(i,tempVertex);
             if(!isTrap(map,rowSize,columnSize,tempVertex)){
                 allTraped=false;
                 break;
             }
         }


         if(!allTraped){
             Vertex vertex_1;
             int indexOfvertex_1=rand()%emptyVertexList.getLen();   //从空位置中随便挑一个出来
             emptyVertexList.get(indexOfvertex_1,vertex_1);

             if(isTrap(map,rowSize,columnSize,vertex_1)){           //如果四面碰壁就跳过
                 vertex_1.isTraped=true;
                 continue;
             }

             map[vertex_1.first][vertex_1.second]=1+i%picNum;       //将图片编号加到该坐标中
             emptyVertexList.del(indexOfvertex_1,vertex_1);


            Vertex vertex_2;
             while (true) {
                 int indexOfvertex_2=rand()%emptyVertexList.getLen();   //从空位置中随便挑一个出来
                 emptyVertexList.get(indexOfvertex_2,vertex_2);
                 QList<Vertex> pairlist;
                 int numOfTurn=this->canLink_2(map,vertex_1.first,vertex_1.second,vertex_2.first,vertex_2.second,pairlist);
                 if(numOfTurn!=-1){
                     map[vertex_2.first][vertex_2.second]=1+i%picNum;       //将图片编号加到该坐标中
                     emptyVertexList.del(indexOfvertex_2,vertex_2);
                     i++;//放到真正添加图片编号的地方
                     break;
                 }

             }

         }else{
             Vertex vertex_1;
             int indexOfvertex_1=rand()%emptyVertexList.getLen();   //从空位置中随便挑一个出来
             emptyVertexList.del(indexOfvertex_1,vertex_1);
             map[vertex_1.first][vertex_1.second]=1+i%picNum;       //将图片编号加到该坐标中


             Vertex vertex_2;
             int indexOfvertex_2=rand()%emptyVertexList.getLen();   //从空位置中随便挑一个出来
             emptyVertexList.del(indexOfvertex_2,vertex_2);
             map[vertex_2.first][vertex_2.second]=1+i%picNum;       //将图片编号加到该坐标中

             i++;
         }

     }

     return map;
}

bool Map::isTrap(int** map,int rowSize,int columnSize,Vertex vertex_1){
    if(map[vertex_1.first][vertex_1.second+1]
            &&map[vertex_1.first][vertex_1.second-1]
            &&map[vertex_1.first+1][vertex_1.second]
            &&map[vertex_1.first-1][vertex_1.second]){     //如果该点上下左右都有东西挡着就先跳过这个点
        return true;
    }

    if(vertex_1.first==1){      //如果在第一行
        if(vertex_1.second!=1||vertex_1.second!=columnSize-2){
            if(map[vertex_1.first][vertex_1.second+1]
                    &&map[vertex_1.first][vertex_1.second-1]
                    &&map[vertex_1.first+1][vertex_1.second]){
                return true;
            }
        }
    }

    if(vertex_1.first==rowSize-2){      //如果在最后一行
        if(vertex_1.second!=1||vertex_1.second!=columnSize-2){
            if(map[vertex_1.first][vertex_1.second+1]
                    &&map[vertex_1.first][vertex_1.second-1]
                    &&map[vertex_1.first-1][vertex_1.second]){
                return true;
            }
        }
    }


    if(vertex_1.second==1){      //如果在第一列
        if(vertex_1.first!=1||vertex_1.first!=rowSize-2){
            if(map[vertex_1.first+1][vertex_1.second]
                    &&map[vertex_1.first-1][vertex_1.second]
                    &&map[vertex_1.first][vertex_1.second+1]){
                return true;
            }
        }
    }

    if(vertex_1.second==columnSize-2){      //如果在最后一列
        if(vertex_1.first!=1||vertex_1.first!=rowSize-2){
            if(map[vertex_1.first+1][vertex_1.second]
                    &&map[vertex_1.first-1][vertex_1.second]
                    &&map[vertex_1.first][vertex_1.second-1]){
                return true;
            }
        }
    }

    if(vertex_1.first==1&&vertex_1.second==1){                 //如果是左上角顶点
        if(map[vertex_1.first][vertex_1.second+1]
                &&map[vertex_1.first+1][vertex_1.second]){
            return true;
        }
    }

    if(vertex_1.first==1&&vertex_1.second==columnSize-2){                 //如果是右上角顶点
        if(map[vertex_1.first][vertex_1.second-1]
                &&map[vertex_1.first+1][vertex_1.second]){
            return true;
        }
    }

    if(vertex_1.first==rowSize-2&&vertex_1.second==1){                 //如果是左下角顶点
        if(map[vertex_1.first][vertex_1.second+1]
                &&map[vertex_1.first-1][vertex_1.second]){
            return true;
        }
    }

    if(vertex_1.first==rowSize-2&&vertex_1.second==columnSize-2){                 //如果是右下角顶点
        if(map[vertex_1.first][vertex_1.second-1]
                &&map[vertex_1.first-1][vertex_1.second]){
            return true;
        }
    }

    return false;
}


//0折连接////////////////////////////////////////////////////////////////////
//输入参数 两点的x，y坐标
//返回bool (是否属于0折连接)
bool Map::canLink_0(int** map,int x1,int y1,int x2,int y2)
{
    //if(map[x1][y1]!=map[x2][y2]) return false;
    // 如果不属于0折连接则返回false
    if(x1 == x2 && y1 == y2)
        return false;
    if(x1 != x2 && y1 != y2)
        return false;

    int min, max;

    // 如果两点的x坐标相等，则在水平方向上扫描
    if(x1 == x2) {
        min = y1 < y2 ? y1 : y2;
        max = y1 > y2 ? y1 : y2;
        for(int i=min+1; i < max; i++) {
            if(map[x1][i] !=0)
                return false;
        }
    }
    // 如果两点的y坐标相等，则在竖直方向上扫描
    else if(y1==y2){
        min = x1 < x2 ? x1 : x2;
        max = x1 > x2 ? x1 : x2;
        for(int i=min+1; i < max; i++) {
            if(map[i][y1] !=0)
                return false;
        }
    }
    return true;

}

//1折连接////////////////////////////////////////////////////////////////////
//输入参数 两点的x，y坐标
//返回Qpair (折点或者(-1,-1))
Vertex Map::canLink_1(int** map,int x1,int y1,int x2,int y2)
{

    Vertex pair;
    pair.first=-1;
    pair.second=-1;

    //if(map[x1][y1]!=map[x2][y2]) return pair;


    if(x1 == x2 || y1 == y2)
        return pair;

    // 测试对角点1
    //pair = qMakePair(x1,y2);
    pair.first=x1;
    pair.second=y2;
    if(map[pair.first][pair.second] == 0) {
       bool Match1 = canLink_0(map,x1,y1, pair.first, pair.second);
       bool Match2 = Match1 ?
             canLink_0(map,x2,y2, pair.first, pair.second) : Match1;

        if (Match1 && Match2) {
            return pair;
        }
    }

    // 测试对角点2
    //pair = qMakePair(x2,y1);
    pair.first=x2;
    pair.second=y1;
    if(map[pair.first][pair.second] == 0) {
       bool Match1 = canLink_0(map,x1,y1, pair.first, pair.second);
       bool Match2 = Match1 ?
             canLink_0(map,x2,y2, pair.first, pair.second) : Match1;

        if (Match1 && Match2) {
            return pair;
        }
    }

    Vertex v;
    v.first=-1;
    v.second=-1;
    return v;

}



//2折连接////////////////////////////////////////////////////////////////////
//输入参数 两点的x，y坐标
//返回Qlist (折点或者-1)

//无法连接 返回(-1,-1)(-1,-1)   判断标志Qpairlist[0].first==-1
//0折连接  返回(0,-1)(-1,-1)    判断标志Qpairlist[0].first==0&&Qpairlist[0].second==-1
//1折连接  返回(x1,y1)(-1,-1)   判断标志Qpairlist[0].second!=-1&&Qpairlist[0].first==-1
//2折连接  返回(x1,y1)(x2,y2)   判断标志Qpairlist[0].second!=-1&&Qpairlist[0].first!=-1
int Map::canLink_2(int** map,int x1,int y1,int x2,int y2,QList<Vertex> pairlist)
{
    //if(map[x1][y1]!=map[x2][y2]) return -1;
    if(x1==x2&&y1==y2) return -1;

//    QPair<int,int> pair1(-1,-1);
//    QPair<int,int> pair2(-1,-1);

    Vertex pair1;
    pair1.first=-1;
    pair1.second=-1;

    Vertex pair2;
    pair2.first=-1;
    pair2.second=-1;
    //QList<QPair<int,int>> pairlist;
    pairlist<<pair1<<pair2;

     // 判断0折连接
     if(canLink_0(map,x1,y1,x2,y2)) {
         Vertex pair;
         pair.first=0;
         pair.second=-1;
         pairlist[1]=pair;
         return 0;
     }

     // 判断1折连接
     pair1 = canLink_1(map,x1,y1,x2,y2);
     if(pair1.first!=-1) {
         pairlist[0]=pair1;
         return 1;
     }

     // 判断2折连接
     int i;
     for(i = y1 + 1; i < maxsize; i++) {
         if(map[x1][i]==0) {
             Vertex p1; //= qMakePair(x1,i);
             p1.first=x1;
             p1.second=i;
             Vertex p2 = canLink_1(map,p1.first,p1.second,x2,y2);
             if(p2.first != -1) {
                pairlist.clear();
                pairlist<<p1<<p2;
               return 2;
             }
         } else break;
     }

     for(i = y1 - 1; i >-1; i--) {

         if(map[x1][i]==0) {
             Vertex p1; //= qMakePair(x1,i);
             p1.first=x1;
             p1.second=i;
             Vertex p2 = canLink_1(map,p1.first,p1.second,x2,y2);
             if(p2.first != -1) {
                pairlist.clear();
                pairlist<<p1<<p2;
               return 2;
             }
         } else break;
     }

     for(i = x1 + 1; i < maxsize; i++) {
         if(map[i][y1] == 0) {
             //QPair<int,int> p1=qMakePair(i,y1);
             Vertex p1;
             p1.first=i;
             p1.second=y1;
             Vertex p2 = canLink_1(map,p1.first,p1.second,x2,y2);
             if(p2.first != -1) {
                pairlist.clear();
                pairlist<<p1<<p2;
               return 2;
             }
         } else break;
     }

     for(i = x1 - 1; i >-1; i--) {
         if(map[i][y1] == 0) {
             //QPair<int,int> p1=qMakePair(i,y1);
             Vertex p1;
             p1.first=i;
             p1.second=y1;
             Vertex p2 = canLink_1(map,p1.first,p1.second,x2,y2);
             if(p2.first != -1) {
                pairlist.clear();
                pairlist<<p1<<p2;
               return 2;
             }
         } else break;
     }

//     pairlist.clear();
//     pairlist<<qMakePair(-1,-1)<<qMakePair(-1,-1);
     return -1;
}

