#include "set_ui.h"
#include "ui_set_ui.h"
#include"linkgame.h"
#include"chooselevel_ui.h"

static int BGM_index;

Set_UI::Set_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Set_UI)
{
    ui->setupUi(this);
    voiceplayer=new VoicePlayer;
}

Set_UI::~Set_UI()
{
    delete ui;
}

void Set_UI::closeEvent(QCloseEvent *event){
    this->hide();
}

void Set_UI::setParentName(string parentName){
    this->parentName=parentName;
}

string Set_UI::getParentName(){
    return this->parentName;
}

void Set_UI::on_returnButton_clicked()
{
    //    if(parentName=="linkgame_ui"){
    //        LinkGame *linkgame_ui=new LinkGame;
    //        linkgame_ui->show();
    //    }else if(parentName=="chooseLevel_ui"){
    //        ChooseLevel_UI *chooseLevel_ui=new ChooseLevel_UI;
    //        chooseLevel_ui->show();
    //    }
    this->hide();
}

void Set_UI::on_BGM_pushButton_clicked()
{

    QString s;
    s=ui->BGM_pushButton->text();
    if(s=="开")
    {
        voiceplayer->Play_BGM();
        ui->BGM_pushButton->setText("关");
    }else{
        voiceplayer->Pause_BGM();
        ui->BGM_pushButton->setText("开");
    }
}

void Set_UI::on_image_style_comboBox_currentIndexChanged(int index)
{
    this->currentModelNum = index;
}

void Set_UI::on_comboBox_currentIndexChanged(int index)
{
    QString qs;
    qs=ui->BGM_pushButton->text();
    BGM_index=index;
    voiceplayer->Play_Music(BGM_index);
    if(qs=="关")
    {
        voiceplayer->Play_BGM();
    }
}

void Set_UI::on_method_and_rule_pushButton_clicked()
{
    MessageDialog* messageDialog = new MessageDialog(this,"连就完事了，奥利给！！！");
    messageDialog->show();
}
