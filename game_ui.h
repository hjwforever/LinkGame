#ifndef GAME_UI_H
#define GAME_UI_H

#include <QMainWindow>

#include"map.h"
#include <QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QMediaPlaylist>
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
private slots:
    void on_returnButton_clicked();

    void on_beginButton_clicked();

    void on_myButton_clicked(int row,int y);

    void createGameMap();

private:


    Ui::Game_UI *ui;
    int level=1;
    Map map;
    int** gameMap;
    int rowSize=10;
    int columnSize=10;
    int numOfPic=10;

    int start_x=20;
    int start_y=20;
    int edgeOfButton=60;

    MyButton*** gameButtonMap;
};

#endif // GAME_UI_H
