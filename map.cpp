#include "map.h"

#include<time.h>

#include"linklist.h"

Map::Map()
{

}

/*
 * �˴���rowSize��columnSizeΪ������ΧһȦ���к�����
 * picNumΪͼ��������
 */
int** Map::creatMap(int rowSize,int columnSize,int level,int picNum){
    LinkList<Vertex> emptyVertexList;   //��ſյĵ������
    this->maxsize=rowSize;
    //����rowSize��columnSize�����鲢��ʼ��ÿһ��Ԫ��Ϊ0
    int** map=(int**) malloc(rowSize*sizeof(int*));
    for(int i=0;i<rowSize;i++){
        map[i]=(int*)malloc(columnSize*sizeof(int));
        for(int j=0;j<columnSize;j++){
            map[i][j]=0;
            if(i!=0&&i!=rowSize-1&&j!=0&&j!=columnSize-1){     //��ʼ���յ������
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

    bool allTraped=true;                                   //�յĵ�λ�Ƿ�ȫ������

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
            int indexOfvertex_1=rand()%emptyVertexList.getLen();   //�ӿ�λ���������һ������
            emptyVertexList.get(indexOfvertex_1,vertex_1);

            if(isTrap(map,rowSize,columnSize,vertex_1)){           //����������ھ�����
                vertex_1.isTraped=true;
                continue;
            }

            map[vertex_1.first][vertex_1.second]=1+i%picNum;       //��ͼƬ��żӵ���������
            emptyVertexList.del(indexOfvertex_1,vertex_1);


            Vertex vertex_2;
            while (true) {
                int indexOfvertex_2=rand()%emptyVertexList.getLen();   //�ӿ�λ���������һ������
                emptyVertexList.get(indexOfvertex_2,vertex_2);
                QList<Vertex> pairlist;
                int numOfTurn=this->canLink_2(map,vertex_1.first,vertex_1.second,vertex_2.first,vertex_2.second,pairlist);
                if(numOfTurn!=-1){
                    map[vertex_2.first][vertex_2.second]=1+i%picNum;       //��ͼƬ��żӵ���������
                    emptyVertexList.del(indexOfvertex_2,vertex_2);
                    i++;//�ŵ��������ͼƬ��ŵĵط�
                    break;
                }

            }

        }else{
            Vertex vertex_1;
            int indexOfvertex_1=rand()%emptyVertexList.getLen();   //�ӿ�λ���������һ������
            emptyVertexList.del(indexOfvertex_1,vertex_1);
            map[vertex_1.first][vertex_1.second]=1+i%picNum;       //��ͼƬ��żӵ���������


            Vertex vertex_2;
            int indexOfvertex_2=rand()%emptyVertexList.getLen();   //�ӿ�λ���������һ������
            emptyVertexList.del(indexOfvertex_2,vertex_2);
            map[vertex_2.first][vertex_2.second]=1+i%picNum;       //��ͼƬ��żӵ���������

            i++;
        }

    }

    return map;
}

bool Map::isTrap(int** map,int rowSize,int columnSize,Vertex vertex_1){
    if(map[vertex_1.first][vertex_1.second+1]
            &&map[vertex_1.first][vertex_1.second-1]
            &&map[vertex_1.first+1][vertex_1.second]
            &&map[vertex_1.first-1][vertex_1.second]){     //����õ��������Ҷ��ж������ž������������
        return true;
    }

    if(vertex_1.first==1){      //����ڵ�һ��
        if(vertex_1.second!=1||vertex_1.second!=columnSize-2){
            if(map[vertex_1.first][vertex_1.second+1]
                    &&map[vertex_1.first][vertex_1.second-1]
                    &&map[vertex_1.first+1][vertex_1.second]){
                return true;
            }
        }
    }

    if(vertex_1.first==rowSize-2){      //��������һ��
        if(vertex_1.second!=1||vertex_1.second!=columnSize-2){
            if(map[vertex_1.first][vertex_1.second+1]
                    &&map[vertex_1.first][vertex_1.second-1]
                    &&map[vertex_1.first-1][vertex_1.second]){
                return true;
            }
        }
    }


    if(vertex_1.second==1){      //����ڵ�һ��
        if(vertex_1.first!=1||vertex_1.first!=rowSize-2){
            if(map[vertex_1.first+1][vertex_1.second]
                    &&map[vertex_1.first-1][vertex_1.second]
                    &&map[vertex_1.first][vertex_1.second+1]){
                return true;
            }
        }
    }

    if(vertex_1.second==columnSize-2){      //��������һ��
        if(vertex_1.first!=1||vertex_1.first!=rowSize-2){
            if(map[vertex_1.first+1][vertex_1.second]
                    &&map[vertex_1.first-1][vertex_1.second]
                    &&map[vertex_1.first][vertex_1.second-1]){
                return true;
            }
        }
    }

    if(vertex_1.first==1&&vertex_1.second==1){                 //��������ϽǶ���
        if(map[vertex_1.first][vertex_1.second+1]
                &&map[vertex_1.first+1][vertex_1.second]){
            return true;
        }
    }

    if(vertex_1.first==1&&vertex_1.second==columnSize-2){                 //��������ϽǶ���
        if(map[vertex_1.first][vertex_1.second-1]
                &&map[vertex_1.first+1][vertex_1.second]){
            return true;
        }
    }

    if(vertex_1.first==rowSize-2&&vertex_1.second==1){                 //��������½Ƕ���
        if(map[vertex_1.first][vertex_1.second+1]
                &&map[vertex_1.first-1][vertex_1.second]){
            return true;
        }
    }

    if(vertex_1.first==rowSize-2&&vertex_1.second==columnSize-2){                 //��������½Ƕ���
        if(map[vertex_1.first][vertex_1.second-1]
                &&map[vertex_1.first-1][vertex_1.second]){
            return true;
        }
    }

    return false;
}


//0������////////////////////////////////////////////////////////////////////
//������� �����x��y����
//����bool (�Ƿ�����0������)
bool Map::canLink_0(int** map,int x1,int y1,int x2,int y2)
{
    //if(map[x1][y1]!=map[x2][y2]) return false;
    // ���������0�������򷵻�false
    if(x1 == x2 && y1 == y2)
        return false;
    if(x1 != x2 && y1 != y2)
        return false;

    int min, max;

    // ��������x������ȣ�����ˮƽ������ɨ��
    if(x1 == x2) {
        min = y1 < y2 ? y1 : y2;
        max = y1 > y2 ? y1 : y2;
        for(int i=min+1; i < max; i++) {
            if(map[x1][i] !=0)
                return false;
        }
    }
    // ��������y������ȣ�������ֱ������ɨ��
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

//1������////////////////////////////////////////////////////////////////////
//������� �����x��y����
//����Qpair (�۵����(-1,-1))
Vertex Map::canLink_1(int** map,int x1,int y1,int x2,int y2)
{

    Vertex pair;
    pair.first=-1;
    pair.second=-1;

    //if(map[x1][y1]!=map[x2][y2]) return pair;


    if(x1 == x2 || y1 == y2)
        return pair;

    // ���ԶԽǵ�1
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

    // ���ԶԽǵ�2
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



//2������////////////////////////////////////////////////////////////////////
//������� �����x��y����
//����Qlist (�۵����-1)

//�޷����� ����(-1,-1)(-1,-1)   �жϱ�־Qpairlist[0].first==-1
//0������  ����(0,-1)(-1,-1)    �жϱ�־Qpairlist[0].first==0&&Qpairlist[0].second==-1
//1������  ����(x1,y1)(-1,-1)   �жϱ�־Qpairlist[0].second!=-1&&Qpairlist[0].first==-1
//2������  ����(x1,y1)(x2,y2)   �жϱ�־Qpairlist[0].second!=-1&&Qpairlist[0].first!=-1
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

    // �ж�0������
    if(canLink_0(map,x1,y1,x2,y2)) {
        Vertex pair;
        pair.first=0;
        pair.second=-1;
        pairlist[1]=pair;
        return 0;
    }

    // �ж�1������
    pair1 = canLink_1(map,x1,y1,x2,y2);
    if(pair1.first!=-1) {
        pairlist[0]=pair1;
        return 1;
    }

    // �ж�2������
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

