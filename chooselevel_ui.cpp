#include "chooselevel_ui.h"
#include "ui_chooselevel_ui.h"
#include"game_ui.h"
#include"linkgame.h"
#include"set_ui.h"

extern Set_UI *set_ui;

ChooseLevel_UI::ChooseLevel_UI(QWidget *parent) :
    MyMainWindow(parent),
    ui(new Ui::ChooseLevel_UI)
{
    ui->setupUi(this);
    setWindowTitle("ChooseLevel");
    QPixmap pixmap1(":/image/button_icon/chooselevel_ui/level_easy.png");
    ui->easyButton->resize(pixmap1.size());
    ui->easyButton->setIcon(pixmap1);
    ui->easyButton->setIconSize(pixmap1.size());
    ui->easyButton->setMask(pixmap1.mask());
    ui->easyButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap2(":/image/button_icon/chooselevel_ui/level_common.png");
    ui->normalButton->resize(pixmap2.size());
    ui->normalButton->setIcon(pixmap2);
    ui->normalButton->setIconSize(pixmap2.size());
    ui->normalButton->setMask(pixmap2.mask());
    ui->normalButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap3(":/image/button_icon/chooselevel_ui/level_hard.png");
    ui->hardButton->resize(pixmap3.size());
    ui->hardButton->setIcon(pixmap3);
    ui->hardButton->setIconSize(pixmap3.size());
    ui->hardButton->setMask(pixmap3.mask());
    ui->hardButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap4(":/image/button_icon/chooselevel_ui/return.png");
    ui->returnButton->resize(pixmap4.size());
    ui->returnButton->setIcon(pixmap4);
    ui->returnButton->setIconSize(pixmap4.size());
    ui->returnButton->setMask(pixmap4.mask());
    ui->returnButton->setStyleSheet("QToolButton{border:0px;}");

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

