#include "login_ui.h"
#include "ui_login_ui.h"

#include"register_ui.h"
#include"set_ui.h"
#include"game_ui.h"
#include"mybutton.h"

extern Set_UI *set_ui;

Login_UI::Login_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login_UI)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    set_ui->connectToServer();
    connect(set_ui, &Set_UI::signal_loginSuccessfully, this, &Login_UI::slot_loginSuccessfully);
}

Login_UI::~Login_UI()
{
    delete ui;
}

void Login_UI::slot_loginSuccessfully(){
    set_ui->hasLogin=true;
    Game_UI *gameUI=new Game_UI;
    connect(this, SIGNAL(signal_createEmptyMap()), gameUI, SLOT(createEmptyGameMap()));
    gameUI->show();
    emit signal_createEmptyMap();
    this->close();
}

void Login_UI::on_registerToolButton_clicked()
{
    Register_UI *registerUI=new Register_UI;
    registerUI->show();
    this->close();
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
