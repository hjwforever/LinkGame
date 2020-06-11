#include "set_ui.h"
#include "ui_set_ui.h"
#include"linkgame.h"
#include"chooselevel_ui.h"
#include"QMessageBox"

static int BGM_index;

Set_UI::Set_UI(QWidget *parent) :
    MyMainWindow(parent),
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
    setWindowTitle("Set");
    voiceplayer=new VoicePlayer;


}

Set_UI::~Set_UI()
{
    delete ui;
}

void Set_UI::connectToServer(){
    //创建一个通信套接字，用来和服务器进行通信
    tcpsocket = new QTcpSocket(this);

    //和服务器进行连接
    tcpsocket->connectToHost(serverIP, port);

    //和服务器连接成功能会触发connected信号
    connect(tcpsocket, &QTcpSocket::connected, this, &Set_UI::slotconnectedsuccess);
    //接收到服务器的信息就会触发readyRead信号
    connect(tcpsocket, &QTcpSocket::readyRead, this, &Set_UI::slotreceive);

    connect(tcpsocket, &QTcpSocket::disconnected, this, &Set_UI::slotdisconnected);
}

//连接成功时
void Set_UI::slotconnectedsuccess()
{
    cout<<"connected successfully!"<<endl;
    //tcpsocket->write(msg.toUtf8().data());
}

void Set_UI::slotdisconnected()
{
    cout<<"disconnect form server"<<endl;
    //cout<<"disconnected isOpen: "<<tcpsocket->state()<<endl;
    if(hasLogin){
        hasLogin=false;
        //显示与服务器断开连接

    }
}

void Set_UI::slotreceive()
{
    QByteArray array = tcpsocket->readAll();
    QString msg = array;
    qDebug()<<msg;

    QStringList msgList;
    msgList=msg.split(":");

    //cout<<"split: "<<msgList.at(0).toLocal8Bit().toStdString()<<msgList.at(1).toLocal8Bit().toStdString()<<endl;
    if(msgList.at(0)=="EMILEXIST"){

    }else if(msgList.at(0)=="SIGNINSUCCESSFULLY"){
        emit signal_signInSuccessfully();
    }else if(msgList.at(0)=="FAILTOLOGIN"){

    }else if(msgList.at(0)=="SUCCESSTOLOGIN"){
        this->name=msgList.at(1);
        qDebug()<<"emit signal_loginSuccessfully()";
        emit signal_loginSuccessfully();
    }else if(msgList.at(0)=="ORIGINALPASSWORDINCORRECT"){

    }else if(msgList.at(0)=="PKMAP"){
        ispking=true;
        int rowSize=msgList.at(1).toInt();
        int columnSize=msgList.at(2).toInt();

        int** gameMap=(int**) malloc(rowSize*sizeof(int*));
        for(int i=0;i<rowSize;i++){
            gameMap[i]=(int*)malloc(columnSize*sizeof(int));
            for(int j=0;j<columnSize;j++){
                gameMap[i][j]=msgList.at(i*columnSize+j+3).toInt();
            }
        }
        emit signal_startPK(gameMap);
    }else if(msgList.at(0)=="RANK"){
        QString rankMsg="排名\t昵称\t胜\n";
        for(int i=3;i<msgList.length();i++){
            if(i%2==1){
                rankMsg.append("NO."+QString::number((i-1)/2)+"\t");
            }
            rankMsg.append(msgList.at(i)+"\t");

            if(i%2==0) rankMsg.append("\n");
        }
        rankMsg.append("\n您胜的场数: "+msgList.at(2));
        emit signal_RankMsg(rankMsg);
    }else if(msgList.at(0)=="LOSE"){
        emit signal_ChangeHasPrepared(false);
        ispking=false;
    }else if(msgList.at(0)=="WIN"){
        emit signal_ChangeHasPrepared(true);
        ispking=false;
    }else if(msgList.at(0)=="INCORRECTCAPTCHA"){    //验证码错误
//        MessageDialog* messageDialog = new MessageDialog(this,"验证码错误！请重新获取验证码！");
//        messageDialog->show();
        QMessageBox::information(this, "验证码错误!", tr("<span style='color: blue; font-size: 24px;'> 验证码错误！请重新获取！"));
    }

    msgList.~QStringList();
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

void Set_UI::on_save_set_pushButton_clicked()
{
    this->hide();
}
