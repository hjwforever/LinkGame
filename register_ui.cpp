#include "register_ui.h"
#include "ui_register_ui.h"

#include"set_ui.h"
#include"login_ui.h"

extern Set_UI *set_ui;

Register_UI::Register_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register_UI)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    connect(set_ui, &Set_UI::signal_signInSuccessfully, this, &Register_UI::slot_SignInSuccessfully);
}

Register_UI::~Register_UI()
{
    delete ui;
}

void Register_UI::on_sureToolButton_clicked()
{
    QString signMsg="SIGNIN";
    signMsg.append(":"+ui->mailLineEdit->text()+":"+ui->passwordLineEdit->text()+":"+ui->nameLineEdit->text());
    set_ui->tcpsocket->write(signMsg.toUtf8().data());
}

void Register_UI::slot_SignInSuccessfully(){
    Login_UI *loginUI=new Login_UI;
    loginUI->show();
    this->close();
}
