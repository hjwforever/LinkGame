#include "register_ui.h"
#include "ui_register_ui.h"

#include"set_ui.h"
#include"login_ui.h"

extern Set_UI *set_ui;

Register_UI::Register_UI(QWidget *parent) :
    MyMainWindow(parent),
    ui(new Ui::Register_UI)
{
    ui->setupUi(this);

    QPixmap pixmap1(":/image/button_icon/redister_ui/get_code.png");
    ui->captchaToolButton->resize(pixmap1.size());
    ui->captchaToolButton->setIcon(pixmap1);
    ui->captchaToolButton->setIconSize(pixmap1.size());
    ui->captchaToolButton->setMask(pixmap1.mask());
    ui->captchaToolButton->setStyleSheet("QToolButton{border:0px;}");

    QPixmap pixmap2(":/image/button_icon/redister_ui/sure.png");
    ui->sureToolButton->resize(pixmap2.size());
    ui->sureToolButton->setIcon(pixmap2);
    ui->sureToolButton->setIconSize(pixmap2.size());
    ui->sureToolButton->setMask(pixmap2.mask());
    ui->sureToolButton->setStyleSheet("QToolButton{border:0px;}");

    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(set_ui, &Set_UI::signal_signInSuccessfully, this, &Register_UI::slot_SignInSuccessfully);
    setWindowTitle("Register");




}

Register_UI::~Register_UI()
{
    delete ui;
}

void Register_UI::closeEvent(QCloseEvent *event){
    Login_UI *loginUI=new Login_UI;
    loginUI->show();
    delete this;
}

void Register_UI::on_sureToolButton_clicked()
{
    QString signMsg="SIGNIN";
    signMsg.append(":"+ui->mailLineEdit->text()+":"+ui->passwordLineEdit->text()+":"+ui->nameLineEdit->text()+":"+ui->captchaLineEdit->text());
    set_ui->tcpsocket->write(signMsg.toUtf8().data());
    ui->captchaToolButton->setEnabled(true);
}

void Register_UI::slot_SignInSuccessfully(){
    set_ui->mail=ui->mailLineEdit->text();
    Login_UI *loginUI=new Login_UI;
    loginUI->show();
    //this->close();
    delete this;
}

void Register_UI::on_captchaToolButton_clicked()
{
    QString msg="GETCAPTCHA:"+ui->mailLineEdit->text();
    set_ui->tcpsocket->write(msg.toUtf8().data());
    ui->captchaToolButton->setEnabled(false);
}

void Register_UI::on_returnButton_clicked()
{
    Login_UI *loginUI=new Login_UI;
    loginUI->show();
    delete this;
}
