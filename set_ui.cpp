#include "set_ui.h"
#include "ui_set_ui.h"

#include"linkgame.h"
#include"chooselevel_ui.h"

Set_UI::Set_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Set_UI)
{
    ui->setupUi(this);
}

Set_UI::~Set_UI()
{
    delete ui;
}

void Set_UI::setParentName(string parentName){
    this->parentName=parentName;
}
string Set_UI::getParentName(){
    return this->parentName;
}

void Set_UI::on_returnButton_clicked()
{
    if(parentName=="linkgame_ui"){
        LinkGame *linkgame_ui=new LinkGame;
        linkgame_ui->show();
    }else if(parentName=="chooseLevel_ui"){
        ChooseLevel_UI *chooseLevel_ui=new ChooseLevel_UI;
        chooseLevel_ui->show();
    }
    this->hide();
}


