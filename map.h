#ifndef MAP_H
#define MAP_H

#include<QList>

typedef struct Vertex{
    int first=0;          //��ʵ���У���������ΧһȦ
    int second=0;       //��ʵ���У���������ΧһȦ

    bool isTraped=false;        //�Ƿ�����
}Vertex;

class Map
{
public:
    Map();
    int** creatMap(int rowSize,int columnSize,int level,int picNum);

    bool isTrap(int** map,int rowSize,int columnSize,Vertex vertex_1);//�Ƿ���������

    bool canLink_0(int** map,int x1,int y1,int x2,int y2);  //�ж��Ƿ�0������
    Vertex canLink_1(int** map,int x1,int y1,int x2,int y2);  //�ж��Ƿ�1������
    int canLink_2(int** map,int x1,int y1,int x2,int y2,QList<Vertex> pairlist);  //�ж��Ƿ�2������

public:
    int maxsize;        //��ͼ���߳�

};

#endif // MAP_H
