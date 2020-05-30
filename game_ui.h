#ifndef GAME_UI_H
#define GAME_UI_H

#include <QMainWindow>

#include"map.h"
#include"mybutton.h"
#include"voiceplayer.h"

namespace Ui {
class Game_UI;
}

class Game_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_UI(QWidget *parent = nullptr);
    ~Game_UI();
    void setLevel(int level);
    int getLevel();
    VoicePlayer *voiceplayer;
    bool allCleared();

private slots:
    void on_returnButton_clicked();
    void on_beginButton_clicked();
    void on_myButton_clicked(int row,int y);
    void createGameMap();

private:

    Ui::Game_UI *ui;
    int level=1;                                 //难度等级
    Map map;                                   //游戏地图
    int** gameMap;                         //存储地图中按钮中编号的二维数组
    int rowSize=10;                         //行的大小
    int columnSize=10;                    //列的大小
    int numOfPic=10;                      //图片种类
    int start_x=20;                        //(0，0)按钮的横坐标起始位置，ps：(0，0)按钮不显示
    int start_y=20;                        //(0，0)按钮的纵坐标起始位置
    int edgeOfButton=60;              //按钮边长

    Vertex vertex1,vertex2;
    int count=0;        //解题按钮计数器
    MyButton*** gameButtonMap;//存放按钮地址的二维数组
};

#endif // GAME_UI_H
