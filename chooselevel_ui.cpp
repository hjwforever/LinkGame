#include "chooselevel_ui.h"
#include "ui_chooselevel_ui.h"
#include"game_ui.h"
#include"linkgame.h"
#include"set_ui.h"

extern Set_UI *set_ui;

ChooseLevel_UI::ChooseLevel_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseLevel_UI)
{
    ui->setupUi(this);
}

ChooseLevel_UI::~ChooseLevel_UI()
{
    delete ui;
}
//简单难度按钮
void ChooseLevel_UI::on_easyButton_clicked()
{
    Game_UI *game_ui = new Game_UI;
    game_ui->setLevel(1);
    game_ui->show();
    connect(this, SIGNAL(createMap()),game_ui, SLOT(createGameMap()));
    emit createMap();

    delete this;
}
/*普通难度按钮*/
void ChooseLevel_UI::on_normalButton_clicked()
{
    Game_UI *game_ui = new Game_UI;
    game_ui->setLevel(2);
    game_ui->show();
    connect(this, SIGNAL(createMap()),game_ui, SLOT(createGameMap()));
    emit createMap();

    delete this;
}
/*困难难度按钮*/
void ChooseLevel_UI::on_hardButton_clicked()
{
    Game_UI *game_ui = new Game_UI;
    game_ui->setLevel(3);
    game_ui->show();
    connect(this, SIGNAL(createMap()),game_ui, SLOT(createGameMap()));
    emit createMap();

    delete this;
}

void ChooseLevel_UI::on_returnButton_clicked()
{
    LinkGame *linkGame_ui=new LinkGame;
    linkGame_ui->show();
    delete this;
}

