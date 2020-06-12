#include "login_ui.h"
#include "ui_login_ui.h"

#include"register_ui.h"
#include"set_ui.h"
#include"game_ui.h"
#include"mybutton.h"
#include"linkgame.h"

extern Set_UI *set_ui;

Login_UI::Login_UI(QWidget *parent) :
    MyMainWindow(parent),
    ui(new Ui::Login_UI)
{
    ui->setupUi(this);

    QPixmap pixmap1(":/image/button_icon/login_ui/login.png");
    ui->loginToolButton->resize(pixmap1.size());
    ui->loginToolButton->setIcon(pixmap1);
    ui->loginToolButton->setIconSize(pixmap1.size());
    ui->loginToolButton->setMask(pixmap1.mask());
    ui->loginToolButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap2(":/image/button_icon/login_ui/register.png");
    ui->registerToolButton->resize(pixmap2.size());
    ui->registerToolButton->setIcon(pixmap2);
    ui->registerToolButton->setIconSize(pixmap2.size());
    ui->registerToolButton->setMask(pixmap2.mask());
    ui->registerToolButton->setStyleSheet("QToolButton{border:0px;}");

    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    if(!set_ui->tcpsocket->state()){
        set_ui->connectToServer();
    }

    connect(set_ui, &Set_UI::signal_loginSuccessfully, this, &Login_UI::slot_loginSuccessfully);
    setWindowTitle("Login");

    ui->mailLineEdit->setText(set_ui->mail);
}

Login_UI::~Login_UI()
{
    delete ui;
}

void Login_UI::closeEvent(QCloseEvent *event){
    if(set_ui->tcpsocket->state()){
        set_ui->tcpsocket->disconnectFromHost();
    }

    LinkGame *linkGame_ui=new LinkGame;
    linkGame_ui->show();
    delete this;
}

void Login_UI::slot_loginSuccessfully(){
    set_ui->hasLogin=true;
    Game_UI *gameUI=new Game_UI;
    //qDebug()<<"gameUI";
    connect(this, SIGNAL(signal_createEmptyMap()), gameUI, SLOT(createEmptyGameMap()));
    gameUI->show();
    emit signal_createEmptyMap();
    //this->close();
    delete this;
}

void Login_UI::on_registerToolButton_clicked()
{
    Register_UI *registerUI=new Register_UI;
    registerUI->show();
    //this->hide();
    delete this;
}

void Login_UI::on_loginToolButton_clicked()
{
    if(ui->mailLineEdit->text()!=""&&ui->passwordLineEdit->text()!=""){
        set_ui->mail=ui->mailLineEdit->text();
        QString signMsg="LOGIN";
        signMsg.append(":"+ui->mailLineEdit->text()+":"+ui->passwordLineEdit->text());
        set_ui->tcpsocket->write(signMsg.toUtf8().data());
    }
}

void Login_UI::on_returnButton_clicked()
{
    if(set_ui->tcpsocket->state()){
        set_ui->tcpsocket->disconnectFromHost();
    }

    LinkGame *linkGame_ui=new LinkGame;
    linkGame_ui->show();
    delete this;
}
