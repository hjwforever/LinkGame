#ifndef MAP_H
#define MAP_H

#include<QList>

typedef struct Vertex{
    int first=0;          //真实的行，算上了外围一圈
    int second=0;       //真实的列，算上了外围一圈

    bool isTraped=false;        //是否碰壁
}Vertex;

class Map
{
public:
    Map();
    int** creatMap(int rowSize,int columnSize,int level,int picNum);

    bool isTrap(int** map,int rowSize,int columnSize,Vertex vertex_1);//是否四面碰壁

    bool canLink_0(int** map,int x1,int y1,int x2,int y2);  //判断是否0折连接
    Vertex canLink_1(int** map,int x1,int y1,int x2,int y2);  //判断是否1折连接
    int canLink_2(int** map,int x1,int y1,int x2,int y2,QList<Vertex> pairlist);  //判断是否2折连接

public:
    int maxsize;        //地图最大边长

};

#endif // MAP_H
