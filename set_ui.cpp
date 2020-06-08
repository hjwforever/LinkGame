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
    QPixmap pixmap1(":/image/button_icon/set_ui/open.png");
    ui->BGM_pushButton->resize(pixmap1.size());
    ui->BGM_pushButton->setIcon(pixmap1);
    ui->BGM_pushButton->setIconSize(pixmap1.size());
    ui->BGM_pushButton->setMask(pixmap1.mask());
    ui->BGM_pushButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap2(":/image/button_icon/set_ui/rule.png");
    ui->method_and_rule_pushButton->resize(pixmap2.size());
    ui->method_and_rule_pushButton->setIcon(pixmap2);
    ui->method_and_rule_pushButton->setIconSize(pixmap2.size());
    ui->method_and_rule_pushButton->setMask(pixmap2.mask());
    ui->method_and_rule_pushButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap3(":/image/button_icon/set_ui/save.png");
    ui->save_set_pushButton->resize(pixmap3.size());
    ui->save_set_pushButton->setIcon(pixmap3);
    ui->save_set_pushButton->setIconSize(pixmap3.size());
    ui->save_set_pushButton->setMask(pixmap3.mask());
    ui->save_set_pushButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap4(":/image/button_icon/return2.png");
    ui->returnButton->resize(pixmap4.size());
    ui->returnButton->setIcon(pixmap4);
    ui->returnButton->setIconSize(pixmap4.size());
    ui->returnButton->setMask(pixmap4.mask());
    ui->returnButton->setStyleSheet("QToolButton{border:0px;}");


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
    if(!isopen)
    {
        voiceplayer->Play_BGM();
        QPixmap pixmap1(":/image/button_icon/set_ui/close.png");
        ui->BGM_pushButton->resize(pixmap1.size());
        ui->BGM_pushButton->setIcon(pixmap1);
        ui->BGM_pushButton->setIconSize(pixmap1.size());
        ui->BGM_pushButton->setMask(pixmap1.mask());
        ui->BGM_pushButton->setStyleSheet("QToolButton{border:0px;}");
        isopen=true;
    }else{
        voiceplayer->Pause_BGM();
        QPixmap pixmap2(":/image/button_icon/set_ui/open.png");
        ui->BGM_pushButton->resize(pixmap2.size());
        ui->BGM_pushButton->setIcon(pixmap2);
        ui->BGM_pushButton->setIconSize(pixmap2.size());
        ui->BGM_pushButton->setMask(pixmap2.mask());
        ui->BGM_pushButton->setStyleSheet("QToolButton{border:0px;}");
        isopen=false;
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
    MessageDialog* messageDialog = new MessageDialog(this,"1.消除卡片：选择一对相同图案的卡片连接起来，连接路径在避开其他图片,并不超过两次转弯。\n"
                                                          "2.操作：任意连续两次点击不同位置的图片，若两次点击的卡片图案相同，且符合消除卡片条件，则消除该对卡片。\n"
                                                          "3.胜利条件：消除全部卡片，按分数排名（相同分数以时间为参考）。\n"
                                                          "4.失败条件：超时。\n"
                                                          "5.连击加分机制：短时间内连续消除越多卡片，则加分越多。");
    messageDialog->show();
}
